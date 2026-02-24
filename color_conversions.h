// color_conversions.h

#pragma once

#ifndef COLOR_CONVERSIONS_H
#define COLOR_CONVERSIONS_H

// --- Start of "extern C" block ---
#ifdef __cplusplus
extern "C" {
#endif

#include "import_exports.h"
#include "chizl_colors_types.h"
#include "white_points.h"       // For white point definitions used in XYZ to Lab conversions.
#include <stdint.h>             // For uint32_t type

typedef uint32_t chizl_color32;

/// <summary>
/// Enumeration of standard illuminant white point types for color space calculations.
/// </summary>
typedef enum {
    WPID_D65 = 0,
    WPID_D65_FULL = 1
    // later: D50, D55, etc.
} WhitePointType;

/// <summary>
/// Converts an RGB color to its HSV (Hue, Saturation, Value) equivalent.
/// </summary>
/// <param name="rgb">RGB Color</param>
/// <returns>HSV struct</returns>
CHIZL_COLORS_API HsvSpace RgbToHsv(RgbColor rgb);

/// <summary>
/// Convert HSV to RGB Color.  -- NOTICE: There are 16,777,216 colors and only 3,600,000 HSV possible values.
/// This means HSV to RGB will only convert to one of it's possible colors and will not convert to them all.
/// </summary>
/// <param name="hsv">HSV struct</param>
/// <returns>RGB Color</returns>
CHIZL_COLORS_API RgbColor HsvToRgb(HsvSpace hsv);

/// <summary>
/// Converts an RGB color to its HSL (Hue, Saturation, Lightness) equivalent.
/// </summary>
/// <param name="rgb">RGB Color</param>
/// <returns>HSL struct</returns>
CHIZL_COLORS_API HslSpace RgbToHsl(RgbColor rgb);

/// <summary>
/// Converts HSL to RGB Color.  -- NOTICE: There are 16,777,216 colors and only 3,600,000 HSL possible values.  
/// This means HSL to RGB will only convert to one of it's possible colors and will not convert to them all.
/// </summary>
/// <param name="hsv">HSV struct</param>
/// <returns>RGB Color</returns>
CHIZL_COLORS_API RgbColor HslToRgb(HslSpace hsl);

/// <summary>
/// Converts an RGB color to the CIE XYZ color space.
/// </summary>
/// <param name="rgb">The RGB color to convert.</param>
/// <returns>The color represented in the CIE XYZ color space.</returns>
CHIZL_COLORS_API XyzSpace RgbToXyz(RgbColor rgb);
/// <summary>
/// Converts a color from XYZ color space to Lab color space.
/// </summary>
/// <param name="xyz">The color in XYZ color space to convert.</param>
/// <returns>The color converted to Lab color space.</returns>
CHIZL_COLORS_API LabSpace XyzToLab(XyzSpace xyz);
/// <summary>
/// Converts a color from XYZ color space to LAB color space using a specified white point.
/// </summary>
/// <param name="xyz">The color in XYZ color space to convert.</param>
/// <param name="wp">The white point type to use for the conversion.</param>
/// <returns>The color converted to LAB color space.</returns>
CHIZL_COLORS_API LabSpace XyzToLabEx(XyzSpace xyz, WhitePointType wp);

    
CHIZL_COLORS_API char* RgbToRgbHex(RgbColor clr, unsigned int includeAlpha);
//CHIZL_COLORS_API uint32_t RgbToRgbDec(RgbColor clr);
//CHIZL_COLORS_API uint32_t  RgbToArgbDec(RgbColor clr);
CHIZL_COLORS_API chizl_color32 RgbToRgbDec(RgbColor clr);
CHIZL_COLORS_API chizl_color32 RgbToArgbDec(RgbColor rgb);
//CHIZL_COLORS_API void ChizlFree(void* p);

char returnBuffer[256];

    // --- End of "extern C" block ---
#ifdef __cplusplus
}
#endif
#endif