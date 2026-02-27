// hsv_conversions.h

#pragma once

#ifndef HSV_CONVERSIONS_H
#define HSV_CONVERSIONS_H

// --- Start of "extern C" block ---
#ifdef __cplusplus
extern "C" {
#endif

#include "import_exports.h"
#include "chizl_colors_types.h"

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

// --- End of "extern C" block ---
#ifdef __cplusplus
}
#endif
#endif