// lch_conversions.c
#include "lch_space.h"
#include "common.h"             // For clampInt, clampDbl
#include <string.h>             // For strlen, strcpy_s
#include <math.h>               // For fmin, fmax, fabs, round, pow

CHIZL_COLORS_API LchSpace LabToLch(LabSpace lab)
{
    double sH = atan2(lab.b, lab.a);

    // convert from radians to degrees
    if (sH > 0)
        sH = (sH / CHIZL_PI) * 180.0;
    else
        sH = 360 - (fabs(sH) / CHIZL_PI) * 180.0;

    if (sH < 0)
        sH += 360.0;
    else if (sH >= 360)
        sH -= 360.0;

    LchSpace lch = {
        lab.l,
        sqrt(lab.a * lab.a + lab.b * lab.b),
        sH
    };

    return lch;
}

