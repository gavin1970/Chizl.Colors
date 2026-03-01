// xyz_space.c
#include "xyz_space.h"
#include "common.h"
#include <string.h>             // For strlen, strcpy_s
#include <math.h>               // For fmin, fmax, fabs, round, pow
#include <stdio.h>              // Required for sprintf
#include <objbase.h>            // For CoTaskMemAlloc

// CIELAB, CIELCh, and CIELUV, and XYZ conversions.

static inline double lab_f(double t)
{
    if (t < 0.0) t = 0.0;

    const double delta = 6.0 / 29.0;
    const double delta2 = delta * delta;
    const double delta3 = delta2 * delta;

    if (t >= delta3)
        return cbrt(t);

    const double inv_3delta2 = 1.0 / (3.0 * delta2);
    return (t * inv_3delta2) + (4.0 / 29.0);
}

static inline LabSpace XyzToLab_White(XyzSpace xyz, WhitePoint wp)
{
    // Normalize XYZ by reference white (XYZ expected 0..100 scale)
    const double x = xyz.x / wp.x;
    const double y = xyz.y / wp.y;
    const double z = xyz.z / wp.z;

    const double fx = lab_f(x);
    const double fy = lab_f(y);
    const double fz = lab_f(z);

    LabSpace lab = {
        (116.0 * fy) - 16.0,
        500.0 * (fx - fy),
        200.0 * (fy - fz)
    };

    return lab;
}

CHIZL_COLORS_API XyzSpace RgbToXyz(RgbColor rgb)
{
    // Normalize R, G, B to the range [0, 1]
    double r = rgb.red / 255.0;
    double g = rgb.green / 255.0;
    double b = rgb.blue / 255.0;

    // Apply gamma correction (sRGB to linear RGB)
    r = (r > 0.04045) ? pow((r + 0.055) / 1.055, 2.4) : r / 12.92;
    g = (g > 0.04045) ? pow((g + 0.055) / 1.055, 2.4) : g / 12.92;
    b = (b > 0.04045) ? pow((b + 0.055) / 1.055, 2.4) : b / 12.92;

    // Convert linear RGB to XYZ using sRGB-specific transformation matrix
    // These coefficients are for sRGB with D65 illuminant
    double x = r * 0.4124564 + g * 0.3575761 + b * 0.1804375;
    double y = r * 0.2126729 + g * 0.7151522 + b * 0.0721750;
    double z = r * 0.0193339 + g * 0.1191920 + b * 0.9503041;

    // Scale XYZ to 0-100 range for consistency with common representations
    // If Y is expected to be 100 for white, then X and Z should be scaled accordingly.
    // The coefficients already produce values in a range where Y for white is ~1.0,
    // so multiplying by 100 makes Y for white = 100.
    XyzSpace xyz = {
        x * 100.0,
        y * 100.0,
        z * 100.0
    };
    return xyz;
}

CHIZL_COLORS_API LabSpace XyzToLabEx(XyzSpace xyz, WhitePointType wp)
{
    switch (wp)
    {
    case WPID_D65_FULL:
        return XyzToLab_White(xyz, WP_D65_FULL);
    case WPID_D65:
    default:
        return XyzToLab_White(xyz, WP_D65);
    }
}

CHIZL_COLORS_API LabSpace XyzToLab(XyzSpace xyz)
{
    return XyzToLab_White(xyz, WP_D65_FULL);     // WP_D65_FULL - default, WP_D65 is the other options
}

CHIZL_COLORS_API LuvSpace XyzToLuvEx(XyzSpace xyz, WhitePointType wp)
{
	double wpX, wpY, wpZ = 0.0;

    switch (wp)
    {
    case WPID_D65_FULL:
        wpX = WP_D65_FULL.x;
        wpY = WP_D65_FULL.y;
        wpZ = WP_D65_FULL.z;
        break;
    case WPID_D65:
    default:
        wpX = WP_D65.x;
        wpY = WP_D65.y;
        wpZ = WP_D65.z;
        break;
    }

    //// Calculate reference white point chromaticity coordinates (u'n, v'n)
    double un_prime = (4 * wpX) / (wpX + (15 * wpY) + (3 * wpZ));
    double vn_prime = (9 * wpY) / (wpX + (15 * wpY) + (3 * wpZ));

    //// Calculate sample chromaticity coordinates (u', v')
    double divisor = (xyz.x + (15 * xyz.y) + (3 * xyz.z));
    double u_prime = (divisor == 0) ? 0 : (4 * xyz.x) / divisor;
    double v_prime = (divisor == 0) ? 0 : (9 * xyz.y) / divisor;

    //// Calculate L*
    const double delta = 6.0 / 29.0;
    const double deltaCubed = (delta * delta * delta); // (6/29)^3

	double l, u, v = 0.0;
    if ((xyz.y / wpY) > deltaCubed)
        l = 116 * pow(xyz.y / wpY, 1.0 / 3.0) - 16;
    else
        l = (29.0 / 6.0) * (29.0 / 6.0) * (29.0 / 6.0) * (xyz.y / wpY);

    //// Calculate u* and v*
    u = 13 * l * (u_prime - un_prime);
    v = 13 * l * (v_prime - vn_prime);

    LuvSpace luv = { l, u, v };
    return luv;
}

CHIZL_COLORS_API LuvSpace XyzToLuv(XyzSpace xyz)
{
	return XyzToLuvEx(xyz, WPID_D65_FULL);      // Default: WP_D65_FULL, WPID_D65 is the other option
}