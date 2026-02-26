// color_conversions.c
#include "color_conversions.h"
#include <objbase.h>            // For free

CHIZL_COLORS_API void ChizlFree(void* p) { free(p); }