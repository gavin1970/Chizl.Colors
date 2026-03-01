// color_support.c
#include "color_support.h"
#include <objbase.h>            // For free

CHIZL_COLORS_API void ChizlFree(void* p) { free(p); }