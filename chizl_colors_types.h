#pragma once

#ifndef CHIZL_COLORS_TYPES_H
#define CHIZL_COLORS_TYPES_H

// This file defines the public data structures
// for the Chizl Colors library.

/// <summary>
/// Color struct definition without alpha.
/// </summary>
typedef struct {
    unsigned char alpha;    // 0 - 255, Transparncy: 0 = invisible, 255 = solid
    unsigned char red;      // 0 - 255, Dark = 0, Bright Red = 255
    unsigned char green;    // 0 - 255, Dark = 0, Bright Green = 255
    unsigned char blue;     // 0 - 255, Dark = 0, Bright Blue = 255
} RgbColor;

/// <summary>
/// The HSV (Hue, Saturation, Value) aka HSB (Hue, Saturation, Brightness)
/// HSV is also sometimes referred to as HSB, where B stands for Brightness instead of Value, but the meaning and value is the same.
/// This color model is a way of representing colors that is more intuitive for human perception than the RGB (Red, Green, Blue) model.
/// HSV divides color into three components:
/// Hue, which represents the color's base, like red, green, or blue.  The value represented the angle or degree on a RGB color wheel, ranging from 0.00 to 360.00 degrees.
/// Saturation, which indicates the of purity or intensity percentage (%) of the color.  A fully saturated color will be a pure, vibrant shade, while a lower saturation will make the color appear muted or grayscale.
/// Value aka Brightness, represents the brightness percentage (%) of the color, ranging from black(0%) to white(100%).
/// HSV is often represented as a cylinder or cone, with:
/// </summary>
typedef struct {
    double hue;             // Around the circular base of the RGB (0.0-360.0°) color wheel.
    double saturation;      // Radius from center to edge of the RGB (0.0-1.0)% color wheel and checks raw value, aka "black".  Unlike HSL satruaction that checks white.
    double value;           // Height from bottom (black) to top (brightest color) (0.0-100.0%).
    double raw_value;       // This is the RAW (0.0-1.0) version of value, instead of auto multiplying 100.  Raw value provides better accuracy when converting to RGB.
} HsvSpace;

/// <summary>
/// Defines a color using the HSL (Hue, Saturation, Lightness) color model.  
/// HSL is a cylindrical-coordinate representation of the RGB color space designed to be more intuitive for human perception than RGB.  
/// * Components:  
/// - Hue (H): The type of color (e.g., red, green) on a 0-360° wheel.  
/// - Saturation (S): The "purity" or intensity of the color (0-100%).  
/// - Lightness (L): The "brightness" or "luminance" of the color (0-100%).  
/// * Interpretation:  
/// HSL's primary advantage is its symmetrical Lightness scale, which aligns with the artistic concepts of tints (adding white) and shades (adding black).  
/// - Lightness = 0%: Always results in black.  
/// - Lightness = 50%: Represents the "purest," most saturated version of the hue.  
/// - Lightness = 100%: Always results in white.  
/// - Saturation = 0%: Results in a shade of gray (from black to white, determined by Lightness).  
/// * This model is ideal for creating color palettes by adjusting Lightness to generate predictable tints and shades, or by adjusting Saturation to create tones.
/// </summary>
typedef struct {
    double hue;             // Hue (H): The type of color (e.g., red, green) on a 0-360° wheel.  
    double saturation;      // The "purity" or intensity of the color (0-100%) and checks raw lightness, aka "white".  Unlink HSV saturaction that checks black.
    double lightness;       // The "brightness" or "luminance" of the color (0-100%).
    double raw_lightness;   // This is the RAW version of lightness, instead of auto multiplying 100.  Raw lightness values provides better accuracy when converting to RGB.
} HslSpace;


/// <summary>
/// The CIE XYZ color space is one of the earliest mathematical representation of all colors visible to the human eye, serving as a standard reference for other color spaces. 
/// It's defined by three imaginary primary colors (X, Y, and Z), where Y represents luminance (brightness), and X and Z represent chromaticity (color). 
/// This space is device-independent, meaning it can be used to describe colors without being tied to a specific display or printing technology. 
/// The XYZ color space serves as a fundamental reference for many other color spaces, but distances in this space do not directly reflect perceived color differences as accurately as LAB or LUV. 
/// The XYZ color space is often used as a reference to convert from one color space to another, making it a crucial tool in color management.
/// </summary>
typedef struct {
    double x;               // 0.0 - 100.0
    double y;               // 0.0 - 100.0
    double z;               // 0.0 - 100.0
} XyzSpace;

#endif // CHIZL_COLORS_TYPES_H