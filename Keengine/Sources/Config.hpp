#ifndef KE_CONFIG_HPP
#define KE_CONFIG_HPP

#include <SFML/Config.hpp>

#ifndef SFML_STATIC
	#ifdef SFML_SYSTEM_WINDOWS
		// Windows compilers need specific (and different) keywords for export and import
		#ifdef KEENGINE_EXPORTS
			#define KEENGINE_API __declspec(dllexport)
		#else
			#define KEENGINE_API __declspec(dllimport)
		#endif
	#else // Linux, FreeBSD, Mac OS X
		// GCC 4 has special keywords for showing/hidding symbols
		#if __GNUC__ >= 4
			#define KEENGINE_API __attribute__((__visibility__("default")))
		#else
			#define KEENGINE_API
		#endif
	#endif
#else
	// Static build doesn't need import/export macros
	#define KEENGINE_API
#endif

#ifdef SFML_SYSTEM_ANDROID
#define KEENGINE_ANDROID
#else
#define KEENGINE_DESKTOP
#endif

#define KEENGINE_VERSION_MAJOR 0
#define KEENGINE_VERSION_MINOR 1

#endif // KE_CONFIG_HPP
