// rgb_conversions.h

#pragma once

#ifndef RGB_CONVERSIONS_H
#define RGB_CONVERSIONS_H

// --- Start of "extern C" block ---
#ifdef __cplusplus
extern "C" {
#endif

#include "import_exports.h"
#include "chizl_colors_types.h"
#include <stdint.h>             // For uint32_t type

typedef uint32_t chizl_color32;

/// <summary>
/// Converts an RGB color to its HSL (Hue, Saturation, Lightness) equivalent.
/// </summary>
/// <param name="rgb">RGB Color</param>
/// <returns>HSL struct</returns>
CHIZL_COLORS_API HslSpace RgbToHsl(RgbColor rgb);

/// <summary>
/// Converts an RGB color to its HSV (Hue, Saturation, Value) equivalent.
/// </summary>
/// <param name="rgb">RGB Color</param>
/// <returns>HSV struct</returns>
CHIZL_COLORS_API HsvSpace RgbToHsv(RgbColor rgb);

/// <summary>
/// Converts an RGB color to its hexadecimal string representation.
/// </summary>
/// <param name="clr">The RGB color to convert.</param>
/// <param name="includeAlpha">Flag indicating whether to include the alpha channel in the output (non-zero to include, zero to exclude).</param>
/// <returns>A pointer to a null-terminated string containing the hexadecimal representation of the RGB color. The caller is responsible for managing the memory of the returned string.</returns>
CHIZL_COLORS_API char* RgbToRgbHex(RgbColor clr, unsigned int includeAlpha);

/// <summary>
/// Converts an RGB color to a 32-bit RGBA color value in decimal format.
/// </summary>
/// <param name="clr">The RGB color to convert.</param>
/// <returns>A 32-bit RGBA color value representing the input RGB color.</returns>
CHIZL_COLORS_API chizl_color32 RgbToRgbDec(RgbColor clr);

/// <summary>
/// Converts an RGB color to a 32-bit ARGB color with full opacity.
/// </summary>
/// <param name="rgb">The RGB color to convert.</param>
/// <returns>A 32-bit ARGB color value with the alpha channel set to fully opaque.</returns>
CHIZL_COLORS_API chizl_color32 RgbToArgbDec(RgbColor rgb);

/// <summary>
/// Converts an RGB color to the CIE XYZ color space.
/// </summary>
/// <param name="rgb">The RGB color to convert.</param>
/// <returns>The color represented in the CIE XYZ color space.</returns>
CHIZL_COLORS_API XyzSpace RgbToXyz(RgbColor rgb);


// --- End of "extern C" block ---
#ifdef __cplusplus
}
#endif
#endif