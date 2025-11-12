// main.h
#pragma once

// We include this here so that any .c file that includes main.h
// automatically gets the DLL functions, too. Good!
#include "ansi_printing.h"
#include "color_conversions.h"

// --- DECLARATIONS ---
// We "declare" the variables with 'extern'.
// This tells the compiler these variables *exist*, but doesn't
// create them. This is just a "bookmark."
extern const RgbColor rgbRed;
extern const RgbColor rgbBlue;
extern const RgbColor rgbYellow;
extern const RgbColor rgbCyan;
