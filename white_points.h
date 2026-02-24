#pragma once

/// <summary>
/// Represents a white point in three-dimensional color space.
/// </summary>
typedef struct { double x, y, z; } WhitePoint;

/// <summary>
/// A constant representing the D65 standard illuminant white point.
/// </summary>
extern const WhitePoint WP_D65;

/// <summary>
/// Represents the D65 standard illuminant white point with full precision.
/// </summary>
extern const WhitePoint WP_D65_FULL;