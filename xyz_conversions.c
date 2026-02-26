// xyz_conversions.c
#include "xyz_conversions.h"
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
    return XyzToLab_White(xyz, WP_D65_FULL);     // or WP_D65_FULL if you want that default
}