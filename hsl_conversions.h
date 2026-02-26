// hsl_conversions.h

#pragma once

#ifndef HSL_CONVERSIONS_H
#define HSL_CONVERSIONS_H

// --- Start of "extern C" block ---
#ifdef __cplusplus
extern "C" {
#endif

#include "import_exports.h"
#include "chizl_colors_types.h"

/// <summary>
/// Converts HSL to RGB Color.  -- NOTICE: There are 16,777,216 colors and only 3,600,000 HSL possible values.  
/// This means HSL to RGB will only convert to one of it's possible colors and will not convert to them all.
/// </summary>
/// <param name="hsv">HSV struct</param>
/// <returns>RGB Color</returns>
CHIZL_COLORS_API RgbColor HslToRgb(HslSpace hsl);


// --- End of "extern C" block ---
#ifdef __cplusplus
}
#endif
#endif