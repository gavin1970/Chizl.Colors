// cmyk_conversions.h

#pragma once

#ifndef CMYK_CONVERSIONS_H
#define CMYK_CONVERSIONS_H

// --- Start of "extern C" block ---
#ifdef __cplusplus
extern "C" {
#endif

#include "import_exports.h"
#include "chizl_colors_types.h"

/// <summary>
/// Converts an RGB color to CMYK color space.
/// </summary>
/// <param name="clr">The RGB color to convert.</param>
/// <returns>The color represented in CMYK color space.</returns>
CHIZL_COLORS_API CmykSpace RgbToCmyk(RgbColor clr);

/// <summary>
/// Converts a CMYK color to an RGB color.
/// </summary>
/// <param name="cmyk">The CMYK color to convert.</param>
/// <returns>The converted RGB color.</returns>
CHIZL_COLORS_API RgbColor CmykToRgb(CmykSpace cmyk);

// --- End of "extern C" block ---
#ifdef __cplusplus
}
#endif
#endif