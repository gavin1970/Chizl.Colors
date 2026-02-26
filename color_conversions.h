// color_conversions.h

#pragma once

#ifndef COLOR_CONVERSIONS_H
#define COLOR_CONVERSIONS_H

// --- Start of "extern C" block ---
#ifdef __cplusplus
extern "C" {
#endif

#include "import_exports.h"

/// <summary>
/// Frees memory that was previously allocated.
/// </summary>
/// <param name="p">Pointer to the memory block to free.</param>
/// <returns>This function does not return a value.</returns>
CHIZL_COLORS_API void ChizlFree(void* p);

// --- End of "extern C" block ---
#ifdef __cplusplus
}
#endif
#endif