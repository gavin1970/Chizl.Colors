// import_exports.h
#pragma once
             
// --- "DLL Export" Macro ---
// This tells the compiler that these functions should be made public (exported) from the DLL.

// Version components (updated by update_version.ps1 during pre-build)
#define CHIZL_COLORS_FULL_YEAR 2026
#define CHIZL_COLORS_YEAR_OFFSET 6
#define CHIZL_COLORS_MONTH 3
#define CHIZL_COLORS_DAY 1
#define CHIZL_COLORS_UTC_TIME 0251
#define CHIZL_COLORS_NUGET_RELEASE 1

// Stringify helper macros
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// Version strings
#define CHIZL_COLORS_FILE_VERSION TOSTRING(CHIZL_COLORS_YEAR_OFFSET) "." TOSTRING(CHIZL_COLORS_MONTH) "." TOSTRING(CHIZL_COLORS_DAY) "." TOSTRING(CHIZL_COLORS_UTC_TIME)
#define CHIZL_COLORS_VERSION TOSTRING(CHIZL_COLORS_YEAR_OFFSET) "." TOSTRING(CHIZL_COLORS_MONTH) "." TOSTRING(CHIZL_COLORS_DAY) "." TOSTRING(CHIZL_COLORS_NUGET_RELEASE)
#define CHIZL_COLORS_COPYRIGHT "Copyright (C) " TOSTRING(CHIZL_COLORS_FULL_YEAR) " colors.dev"

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
