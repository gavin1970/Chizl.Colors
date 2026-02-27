// rgb_conversions.c
#include "rgb_conversions.h"
#include "common.h"             // clampDbl
#include <string.h>             // For strlen, strcpy_s
#include <math.h>               // For fmin, fmax, fabs, round, pow
#include <stdio.h>              // Required for sprintf
#include <objbase.h>            // For malloc

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

