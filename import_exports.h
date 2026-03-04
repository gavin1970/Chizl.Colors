// import_exports.h
#pragma once
             
// File Version is based on build Date/Time
// Format: (YEAR-2020).MM.DD.HHmm (UTC)

// The following Date and Time are auto updated during build 
// with update_version.ps1, based on the current UTC date and 
// time, with the year offset from 2020 to keep version 
// numbers manageable.
#define CHIZL_COLORS_FULL_YEAR 2026
#define CHIZL_COLORS_YEAR_OFFSET 6
#define CHIZL_COLORS_MONTH 3
#define CHIZL_COLORS_DAY 4
#define CHIZL_COLORS_UTC_TIME 0543
// This release number is incremented manually for each NuGet 
// release, to distinguish between multiple releases on the 
// same day and must be manually updated.
#define CHIZL_COLORS_NUGET_RELEASE 1

// Stringify helper macros
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// File Version uses date/time components
// Example: "1.4.1.1104" or similar based on build timestamp
#define CHIZL_COLORS_FILE_VERSION \
		TOSTRING(CHIZL_COLORS_YEAR_OFFSET) "." \
		TOSTRING(CHIZL_COLORS_MONTH) "." \
		TOSTRING(CHIZL_COLORS_DAY) "." \
		TOSTRING(CHIZL_COLORS_UTC_TIME)

// NuGet/Product Version (Major.Minor.Patch.Release)
#define CHIZL_COLORS_VERSION \
		TOSTRING(CHIZL_COLORS_YEAR_OFFSET) "." \
		TOSTRING(CHIZL_COLORS_MONTH) "." \
		TOSTRING(CHIZL_COLORS_DAY) "." \
		TOSTRING(CHIZL_COLORS_NUGET_RELEASE)

// Copyright message, with current year based on full year macro
#define CHIZL_COLORS_COPYRIGHT "Copyright (C) " TOSTRING(CHIZL_COLORS_FULL_YEAR) " colors.dev"

// --- "DLL Export" Macro ---
// This tells the compiler that these functions should be made public (exported) from the DLL.
#define CHIZL_COLORS_API CHIZL_COLORS_DLL
                                          
#if defined(_WIN32) || defined(_WIN64)
	#ifdef CHIZL_COLORS_EXPORTS
		#define CHIZL_COLORS_DLL __declspec(dllexport)
	#else
		#define CHIZL_COLORS_DLL __declspec(dllimport)
	#endif
#else
	#define CHIZL_COLORS_DLL __attribute__((visibility("default")))
#endif
