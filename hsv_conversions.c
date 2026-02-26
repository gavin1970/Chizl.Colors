// hsv_conversions.c
#include "hsv_conversions.h"
#include "common.h"             // For clampDbl
#include <math.h>               // For fmin, fmax, fabs, round, pow

// CIELAB, CIELCh, and CIELUV, and XYZ conversions.

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
