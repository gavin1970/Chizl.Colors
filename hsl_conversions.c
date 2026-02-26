// hsl_conversions.c
#include "hsl_conversions.h"
#include <string.h>             // For strlen, strcpy_s
#include <math.h>               // For fmin, fmax, fabs, round, pow

static double HueToRgb(double p, double q, double t) {
    if (t < 0.0) t += 1.0;
    if (t > 1.0) t -= 1.0;
    if (t < 1.0 / 6.0) return p + (q - p) * 6.0 * t;
    if (t < 1.0 / 2.0) return q;
    if (t < 2.0 / 3.0) return p + (q - p) * (2.0 / 3.0 - t) * 6.0;
    return p;
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

