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
static inline double normalize01_to_0max(double v, double max) { return (v > 0.0 && v < 1.0) ? (v * max) : v; }
static inline unsigned char clampIntToUChr(int v)
{
	v = clampInt(v, 0, 255);
	return (unsigned char)v;
}
static inline double makeWholeClamp(double v, double min, double max)
{
	if (v > 0.0 && v < 1.0)
		v *= max;

	return clampDbl(v, min, max);
}
static inline double chkDbleClamp(double v, double min, double max, double div)
{
	v = makeWholeClamp(v, min, max);

	if (div != 0.0)
		v /= div;

	return clampDbl(v, min, max);
}

#endif