// rgb_conversions.c
#include "rgb_conversions.h"
#include "common.h"             // clampDbl
#include <string.h>             // For strlen, strcpy_s
#include <math.h>               // For fmin, fmax, fabs, round, pow
#include <stdio.h>              // Required for sprintf
#include <objbase.h>            // For malloc

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

CHIZL_COLORS_API char* RgbToRgbHex(RgbColor clr, unsigned int includeAlpha)
{
    char rgbHex[16] = { 0 };

    if (includeAlpha)
        snprintf(rgbHex, sizeof(rgbHex), "#%08X", (unsigned)RgbToArgbDec(clr));
    else
        snprintf(rgbHex, sizeof(rgbHex), "#%06X", (unsigned)RgbToRgbDec(clr));

    size_t len = strlen(rgbHex) + 1;
    char* buffer = (char*)malloc((size_t)len);
    if (!buffer) return NULL;

#ifdef _WIN32
    strcpy_s(buffer, len, rgbHex);
#else
    memcpy(buffer, rgbHex, len);
#endif

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
