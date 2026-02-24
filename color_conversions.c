// color_conversions.c
#include "color_conversions.h"
#include "common.h"
#include <string.h>             // For strlen, strcpy_s
#include <math.h>               // For fmin, fmax, fabs, round, pow
#include <stdio.h>              // Required for sprintf
#include <objbase.h>            // For CoTaskMemAlloc

// CIELAB, CIELCh, and CIELUV, and XYZ conversions.

static double HueToRgb(double p, double q, double t) {
    if (t < 0.0) t += 1.0;
    if (t > 1.0) t -= 1.0;
    if (t < 1.0 / 6.0) return p + (q - p) * 6.0 * t;
    if (t < 1.0 / 2.0) return q;
    if (t < 2.0 / 3.0) return p + (q - p) * (2.0 / 3.0 - t) * 6.0;
    return p;
}

CHIZL_COLORS_API HsvSpace RgbToHsv(RgbColor rgb)
{
    // Convert 0-255 to 0.0-1.0
    double r = clampDbl(rgb.red, 0.0, 255.0) / 255.0;
    double g = clampDbl(rgb.green, 0.0, 255.0) / 255.0;
    double b = clampDbl(rgb.blue, 0.0, 255.0) / 255.0;

    double min = fmin(fmin(r, g), b);
    double max = fmax(fmax(r, g), b);
    double delta = max - min;

    double h = 0.0;
    double s = 0.0;
    double v = max;     // Value is just the max component
    double raw = max;   // raw value, before conversion.  More precise when converting back to RGB.

    if (delta != 0.0)
    {
        s = (max == 0.0) ? 0.0 : (delta / max);

        if (r == max)
            h = (g - b) / delta;
        else if (g == max)
            h = 2.0 + (b - r) / delta;
        else // b == max
            h = 4.0 + (r - g) / delta;

        h *= 60.0; // convert to degrees
        if (h < 0.0)
            h += 360.0;
    }

    HsvSpace hsv = { h, s * 100.0, v * 100.0, raw };
    return hsv;
}

CHIZL_COLORS_API RgbColor HsvToRgb(HsvSpace hsv)
{
    // Whole number
    double h = clampDbl(hsv.hue, 0.0, 360.0);
    // Convert 0-100.0 to 0.0-1.0
    double s = clampDbl(hsv.saturation, 0.0, 100.0) / 100.0;
    double v = clampDbl(hsv.value, 0.0, 100.0) / 100.0;
    double raw = hsv.raw_value;       //untouched
    
    // If raw values exists, they are more precise.
    if (raw > 0.0 && raw <= 1.0 && raw != v)
        v = raw;

    double r = 0.0, g = 0.0, b = 0.0;

    int i = (int)floor(h / 60.0) % 6;
    double f = (h / 60.0) - floor(h / 60.0);
    double p = v * (1.0 - s);
    double q = v * (1.0 - f * s);
    double t = v * (1.0 - (1.0 - f) * s);

    switch (i)
    {
    case 0: r = v; g = t; b = p; break;
    case 1: r = q; g = v; b = p; break;
    case 2: r = p; g = v; b = t; break;
    case 3: r = p; g = q; b = v; break;
    case 4: r = t; g = p; b = v; break;
    case 5: r = v; g = p; b = q; break;
    }

    // Convert 0.0-1.0 back to 0-255
    RgbColor rgb = { 
        (unsigned char)255.0,
        (unsigned char)round(r * 255.0), 
        (unsigned char)round(g * 255.0), 
        (unsigned char)round(b * 255.0) 
    };
    return rgb;
}

CHIZL_COLORS_API HslSpace RgbToHsl(RgbColor rgb)
{
    // Convert 0-255 to 0.0-1.0
    double r = (double)rgb.red / 255.0;
    double g = (double)rgb.green / 255.0;
    double b = (double)rgb.blue / 255.0;

    double min = fmin(fmin(r, g), b);
    double max = fmax(fmax(r, g), b);
    double delta = max - min;

    double h = 0.0;
    double s = 0.0;
    double l = (max + min) / 2.0;
    double raw = l;         // raw value.  More precise when converting back to RGB.

    if (delta != 0.0)
    {
        s = (l <= 0.5) ? (delta / (max + min)) : (delta / (2.0 - max - min));

        if (r == max)
            h = (g - b) / delta;
        else if (g == max)
            h = 2.0 + (b - r) / delta;
        else // b == max
            h = 4.0 + (r - g) / delta;

        h *= 60.0; // convert to degrees
        if (h < 0.0)
            h += 360.0;
    }

    HslSpace hsl = { h, s * 100.0, l * 100.0, raw };
    return hsl;
}

CHIZL_COLORS_API RgbColor HslToRgb(HslSpace hsl)
{
    // Convert 0-100.0 to 0.0-1.0
    double h = hsl.hue / 360.0; // HSL stores 0-360, but math needs 0-1.0
    double s = hsl.saturation / 100.0;
    double l = hsl.lightness / 100.0;
    double raw = hsl.raw_lightness;       //untouched

    // If raw lightness values exists, they are more precise.
    if (raw > 0.0 && raw <= 1.0 && raw != l)
        l = raw;

    double r, g, b;

    if (s == 0.0)
        r = g = b = l; // achromatic (gray)
    else
    {
        // Use lightness to prepair for RGB
        double q = (l < 0.5) ? (l * (1.0 + s)) : (l + s - l * s);
        double p = 2.0 * l - q;
        r = HueToRgb(p, q, h + 1.0 / 3.0);
        g = HueToRgb(p, q, h);
        b = HueToRgb(p, q, h - 1.0 / 3.0);
    }

	// Convert 0.0-1.0 back to 0-255
    RgbColor rgb = {
        (unsigned char)255.0,
        (unsigned char)round(r * 255.0),
        (unsigned char)round(g * 255.0),
        (unsigned char)round(b * 255.0)
    };
    return rgb;
}

CHIZL_COLORS_API char* RgbToRgbHex(RgbColor clr, unsigned int includeAlpha) {
    // Hex form: #RRGGBB
    char rgbHex[16] = { 0 };

    if (includeAlpha)
        snprintf(rgbHex, sizeof(rgbHex), "#%08X", RgbToArgbDec(clr));
    else
        snprintf(rgbHex, sizeof(rgbHex), "#%06X", RgbToRgbDec(clr));

    int len = (int)strlen(rgbHex) + 1;
#ifdef _WIN32
    char* buffer = (char*)CoTaskMemAlloc(len);
#else
    char* buffer = (char*)malloc(len);
#endif
    
    if (buffer == NULL)
        return NULL;

    strcpy_s(buffer, len, rgbHex);
    return buffer;
}


CHIZL_COLORS_API chizl_color32 RgbToRgbDec(RgbColor clr)
{
    // Decimal form: (r, g, b)
    uint32_t rgb = (clr.red << 16) | (clr.green << 8) | clr.blue;
    return rgb;
}

CHIZL_COLORS_API chizl_color32 RgbToArgbDec(RgbColor clr)
{
    // Decimal form: (r, g, b)
    unsigned int rgb = (clr.red << 16) | (clr.green << 8) | clr.blue;
    uint32_t argb = (clr.alpha << 24) | rgb;
    return argb;
}

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

