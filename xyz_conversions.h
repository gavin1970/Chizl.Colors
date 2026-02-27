// xyz_conversions.h

#pragma once

#ifndef XYZ_CONVERSIONS_H
#define XYZ_CONVERSIONS_H

// --- Start of "extern C" block ---
#ifdef __cplusplus
extern "C" {
#endif

#include "import_exports.h"
#include "chizl_colors_types.h"
#include "white_points.h"       // For white point definitions used in XYZ to Lab conversions.
#include <stdint.h>             // For uint32_t type

/// <summary>
/// Enumeration of standard illuminant white point types for color space calculations.
/// </summary>
typedef enum {
    WPID_D65 = 0,
    WPID_D65_FULL = 1
    // later: D50, D55, etc.
} WhitePointType;

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


// --- End of "extern C" block ---
#ifdef __cplusplus
}
#endif
#endif