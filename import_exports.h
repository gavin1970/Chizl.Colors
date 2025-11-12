// import_exports.h
#pragma once

// --- "DLL Export" Macro ---
// This tells the compiler that these functions should be made public (exported) from the DLL.

#define CHIZL_COLORS_VERSION "1.1.0"
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

