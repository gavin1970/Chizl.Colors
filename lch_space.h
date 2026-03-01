// lch_conversions.h

#pragma once

#ifndef LCH_CONVERSIONS_H
#define LCH_CONVERSIONS_H

// --- Start of "extern C" block ---
#ifdef __cplusplus
extern "C" {
#endif

#include "import_exports.h"
#include "chizl_colors_types.h"

CHIZL_COLORS_API LchSpace LabToLch(LabSpace lab);

// --- End of "extern C" block ---
#ifdef __cplusplus
}
#endif
#endif