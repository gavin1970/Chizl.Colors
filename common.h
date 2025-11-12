// common.h
#pragma once

#ifndef COMMON_H
#define COMMON_H

//#define TRUE 1
//#define FALSE 0
//#define BOOL int

static inline unsigned char clampUChr(unsigned char v, unsigned char min, unsigned char max) { return v < min ? min : (v > max ? max : v); }
static inline int clampInt(int v, int min, int max) { return v < min ? min : (v > max ? max : v); }
static inline double clampDbl(double v, double min, double max) { return v < min ? min : (v > max ? max : v); }
static inline double makeWholeClamp(double v, double min, double max)
{
	if (v > 0.0 && v < 1.0)
		v *= max;

	return clampDbl(v, min, max);
}
static inline double chkDbleClamp(double v, double min, double max, double div)
{
	v = makeWholeClamp(v, min, max);

	if (v > 0.0 && div > 1.0)
		v /= div;

	return clampDbl(v, min, max);
}

#endif