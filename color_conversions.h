// color_conversions.h

#pragma once

#ifndef COLOR_CONVERSIONS_H
#define COLOR_CONVERSIONS_H

#include "import_exports.h"
#include "chizl_colors_types.h"

// --- Start of "extern C" block ---
#ifdef __cplusplus
extern "C" {
#endif

#pragma region HSV
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
#pragma endregion

#pragma region HSL
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
#pragma endregion

#pragma region HSL
    /// <summary>
    /// Converts an RGB color to the CIE XYZ color space.
    /// </summary>
    /// <param name="rgb">The RGB color to convert.</param>
    /// <returns>The color represented in the CIE XYZ color space.</returns>
    CHIZL_COLORS_API XyzSpace RgbToXyz(RgbColor rgb);
#pragma endregion

#pragma region Other
    
    /*
    [DllImport("Chizl.Colors.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    public static extern string GetPersistentString();
    */

    CHIZL_COLORS_API char* RgbToRgbHex(RgbColor clr, unsigned int includeAlpha);
    CHIZL_COLORS_API int RgbToRgbDec(RgbColor clr);
    CHIZL_COLORS_API int RgbToArgbDec(RgbColor clr);
    
    static char returnBuffer[256];

#pragma endregion

    // --- End of "extern C" block ---
#ifdef __cplusplus
}
#endif
#endif