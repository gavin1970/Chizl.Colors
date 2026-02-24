[![Version](https://img.shields.io/badge/version-1.1.0-blue.svg)](https://github.com/gavin1970/Chizl.Colors)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-lightgrey.svg)](https://github.com/gavin1970/Chizl.Colors)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/gavin1970/Chizl.Colors/blob/master/LICENSE.md)<br/>
[![Target Frameworks](https://img.shields.io/badge/target%20frameworks-c%20%7C%20cplusplus%20%7C%20.net-purple)](https://dotnet.microsoft.com/)

A lightweight, cross-platform C/C++ library with .NET interop for color manipulation and console color rendering with 24-bit true color support.


## Features

- **Color Space Conversions**: Convert between RGB, HSV, and HSL color spaces
- **Console Color Support**: Set 24-bit true colors for foreground and background in console applications
- **ANSI Escape Sequences**: Automatic ANSI color code generation for terminal rendering
- **Cross-Language Support**: Native C/C++ library with .NET interop examples
- **High Precision**: Raw value storage for lossless round-trip conversions
- **Hex & Decimal Export**: Convert RGB colors to hex strings and decimal integers

## Table of Contents

- [Installation](#installation)
- [Quick Start](#quick-start)
- [API Reference](#api-reference)
  - [Color Conversions](#color-conversions)
  - [Console Colors](#console-colors)
  - [Format Conversions](#format-conversions)
- [Usage Examples](#usage-examples)
  - [C/C++ Example](#cc-example)
  - [C# .NET Example](#c-net-example)
- [Building](#building)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## Installation

### Prerequisites

- **Windows**: Visual Studio 2022 (Platform Toolset v143)
- **C++ Standard**: C++14 or higher
- **.NET SDK**: .NET 8.0 (for C# demos)

### Building the Library

1. Clone the repository:
2. Open `Chizl.Colors.sln` in Visual Studio 2022
3. Build the solution (F7)
4. The DLL will be output to the `bin` directory

## Quick Start

### C/C++ Usage
```C
#include "chizl_colors.h"
int main() { 
	// Create an RGB color 
	RgbColor cyan = { 255, 0, 255, 255 }; // alpha, red, green, blue
	// Convert to HSV
	HsvSpace hsv = RgbToHsv(cyan);
	printf("HSV: H:%.2f, S:%.2f, V:%.2f\n", hsv.hue, hsv.saturation, hsv.value);

	// Set console foreground color
	SetFgColorEx(cyan);
	printf("This text is cyan!\n");
	// Reset to default console colors
	ResetColor();
	// Clear the console buffer
	ClearBuffer();
	return 0;
}
```

### C# .NET Usage

```C#
using static ColorApi;
...
var cyan = new RgbColor { alpha = 255, red = 0, green = 255, blue = 255 };

// Convert to HSL 
var hsl = RgbToHsl(cyan); 
Console.WriteLine($"HSL: H:{hsl.hue:0.00}, S:{hsl.saturation:0.00}, L:{hsl.lightness:0.00}");

// Set console colors 
SetColorsEx(cyan, new RgbColor { alpha = 255, red = 0, green = 0, blue = 0 }); 
Console.WriteLine("Cyan text on black background!"); 
// Reset to default console colors
ResetColor();
// Clear the console buffer
ClearBuffer();
```

## API Reference

### Color Conversions

* `HsvSpace RgbToHsv(RgbColor rgb)`
	* Converts RGB (0-255) to HSV color space.
	* **Returns**: `HsvSpace` with hue (0-360&deg;), saturation (0-100%), value (0-100%), and raw_value

* `RgbColor HsvToRgb(HsvSpace hsv)`
	* Converts HSV to RGB. Uses raw_value if available for precision.
	* **Note**: Only ~3.6M HSV combinations exist for 16.7M RGB colors

* `HslSpace RgbToHsl(RgbColor rgb)`
	* Converts RGB to HSL (Hue, Saturation, Lightness) color space.
	* **Returns**: `HslSpace` with hue (0-360�), saturation (0-100%), lightness (0-100%), and raw_lightness

* `RgbColor HslToRgb(HslSpace hsl)`
	* Converts HSL to RGB. Uses raw_lightness if available for precision.

### Console Colors

* `void SetColorsEx(RgbColor bg, RgbColor fg)`
	* Sets both background and foreground console colors using 24-bit RGB.

* `void SetFgColorEx(RgbColor fg)`
	* Sets foreground (text) color only.

* `void SetBgColorEx(RgbColor bg)`
	* Sets background color only.

* `void SetFgColor(unsigned char red, unsigned char green, unsigned char blue)`
	* Sets foreground color using individual RGB components.

* `void SetBgColor(unsigned char red, unsigned char green, unsigned char blue)`
	* Sets background color using individual RGB components.

* `void ResetColor(void)`
	* Resets foreground and background to console defaults.

* `void ClearBuffer(void)`
	* Clears the console buffer and resets cursor position.

### Format Conversions

* `char* RgbToRgbHex(RgbColor clr, unsigned int includeAlpha)`
	* Converts RGB to hex string format.
	*  **includeAlpha = 0**: Returns `#RRGGBB`
	*  **includeAlpha = 1**: Returns `#AARRGGBB`
	*  **Note**: Caller must free returned string with `CoTaskMemFree()` (C#) or appropriate method

* `int RgbToRgbDec(RgbColor clr)`
	* Converts RGB to decimal integer (0x00RRGGBB).

* `int RgbToArgbDec(RgbColor clr)`
	* Converts RGB to decimal integer with alpha (0xAARRGGBB).

## Usage Examples

### C/C++ Example

See the full C console demo in [`DemoConsole/main.c`](https://github.com/gavin1970/Chizl.Colors/blob/master/DemoConsole/main.c):
```C
#include "chizl_colors.h"
const RgbColor rgbCyan = { 255, 0, 255, 255 }; 
const RgbColor rgbBlack = { 255, 0, 0, 0 };

// Convert and display color info 
HsvSpace hsv = RgbToHsv(rgbCyan); 
HslSpace hsl = RgbToHsl(rgbCyan);
char* hex = RgbToRgbHex(rgbCyan, 0); printf("Hex: %s\n", hex);

// Round-trip test 
RgbColor hsv_rt = HsvToRgb(hsv); 
printf("HSV Roundtrip: R:%u, G:%u, B:%u\n", hsv_rt.red, hsv_rt.green, hsv_rt.blue);

// Set console colors 
SetColorsEx(rgbCyan, rgbBlack); 
printf("Colored text!\n"); 

// Reset to default console colors
ResetColor();
// Clear the console buffer
ClearBuffer();
```

### C# .NET Example

See the full .NET demo in [`demos/CSharpConsole/Program.cs`](https://github.com/gavin1970/Chizl.Colors/blob/master/demos/CSharpConsole/Program.cs):

```C#
static readonly RgbColor rgbCyan = new RgbColor { alpha = 255, red = 0, green = 255, blue = 255 }; 
static readonly RgbColor rgbBlack = new RgbColor { alpha = 255, red = 0, green = 0, blue = 0 };
var hsv = ColorApi.RgbToHsv(rgbCyan); 
var hsl = ColorApi.RgbToHsl(rgbCyan);
var hex = ColorApi.RgbToRgbHex(rgbCyan, false); 
Console.WriteLine($"Hex: {hex}");
var dec = ColorApi.RgbToArgbDec(rgbCyan); 
Console.WriteLine($"Decimal: {dec}");

// Round-trip conversions 
var hsv_rev = ColorApi.HsvToRgb(hsv); 
var hsl_rev = ColorApi.HslToRgb(hsl);

// Set console colors 
ColorApi.SetColorsEx(rgbCyan, rgbBlack); 
Console.WriteLine("Colored text!"); 

// Reset to default console colors
ColorApi.ResetColor();
// Clear the console buffer
ColorApi.ClearBuffer();
```

## Building

### Visual Studio 2022

1. Open `Chizl.Colors.sln`
2. Select desired configuration (Debug/Release)
3. Build Solution (Ctrl+Shift+B)

### Build Output

- **Library**: `Chizl.Colors.dll` and `Chizl.Colors.lib`
- **C Demo**: `DemoConsole.exe`
- **C# Demo**: `CSharpConsole.exe`

## Project Structure

## Color Space Information

### RGB (Red, Green, Blue)
- **Range**: 0-255 per channel
- **Total Colors**: 16,777,216 (2^24)
- **Use Case**: Display, web, image formats

### HSV (Hue, Saturation, Value)
- **Hue**: 0-360� (color wheel)
- **Saturation**: 0-100% (color intensity)
- **Value**: 0-100% (brightness)
- **Total Combinations**: ~3,600,000
- **Use Case**: Color picking, adjusting brightness

### HSL (Hue, Saturation, Lightness)
- **Hue**: 0-360� (color wheel)
- **Saturation**: 0-100% (color purity)
- **Lightness**: 0-100% (light/dark balance)
- **Total Combinations**: ~3,600,000
- **Use Case**: Color adjustments, tinting

> **Note**: HSV/HSL have fewer combinations than RGB, so conversions may not be perfectly reversible. This library stores `raw_value`/`raw_lightness` to improve round-trip accuracy.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/gavin1970/Chizl.Colors/blob/master/LICENSE.md) file for details.

## Acknowledgments

- ANSI escape sequence support for cross-platform terminal colors
- Inspired by the need for true-color console applications
- Built with C++14 for broad compatibility

## Version History

- **1.1.0** - Current release
  - Color space conversions (RGB, HSV, HSL)
  - Console color manipulation
  - Hex and decimal format conversions
  - C and C# demo applications

---

**Repository**: [https://github.com/gavin1970/Chizl.Colors](https://github.com/gavin1970/Chizl.Colors)

**Issues**: [Report a bug or request a feature](https://github.com/gavin1970/Chizl.Colors/issues)

