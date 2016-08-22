#ifndef KE_CONFIG_HPP
#define KE_CONFIG_HPP

#include <SFML/Config.hpp>

#ifndef SFML_STATIC
	#ifdef SFML_SYSTEM_WINDOWS
		#ifdef KEENGINE_EXPORTS // Windows compilers need specific (and different) keywords for export and import
			#define KEENGINE_API __declspec(dllexport)
		#else
			#define KEENGINE_API __declspec(dllimport)
		#endif
	#else // Linux, FreeBSD, Mac OS X
		#if __GNUC__ >= 4 // GCC 4 has special keywords for showing/hidding symbols
			#define KEENGINE_API __attribute__((__visibility__("default")))
		#else
			#define KEENGINE_API
		#endif
	#endif
#else
	#define KEENGINE_API
#endif

#if SFML_SYSTEM_ANDROID || SFML_SYSTEM_IOS
	#define KEENGINE_MOBILE
	#ifdef SFML_SYSTEM_ANDROID
		#define KEENGINE_ANDROID
	#else
		#define KEENGINE_IOS
	#endif
#else
	#define KEENGINE_DESKTOP
	#ifdef SFML_SYSTEM_WINDOWS
		#define KEENGINE_WINDOWS
	#elif SFML_SYSTEM_MACOS
		#define KEENGINE_MACOS
	#elif SFML_SYSTEM_LINUX
		#define KEENGINE_LINUX
	#elif SFML_SYSTEM_FREEBSD
		#define KEENGINE_FREEBSD
	#endif
#endif

#define KEENGINE_VERSION_MAJOR 0
#define KEENGINE_VERSION_MINOR 1

namespace ke
{
	inline bool isMobile()
	{
		#ifdef KEENGINE_MOBILE
		return true;
		#else
		return false;
		#endif
	}

	inline bool isAndroid()
	{
		#ifdef KEENGINE_ANDROID
		return true;
		#else
		return false;
		#endif		
	}

	inline bool isIOS()
	{
		#ifdef KEENGINE_IOS
		return true;
		#else
		return false;
		#endif		
	}

	inline bool isDesktop()
	{
		#ifdef KEENGINE_DESKTOP
		return true;
		#else
		return false;
		#endif
	}

	inline bool isWindows()
	{
		#ifdef KEENGINE_WINDOWS
		return true;
		#else
		return false;
		#endif	
	}

	inline bool isMacOS()
	{
		#ifdef KEENGINE_MACOS
		return true;
		#else
		return false;
		#endif	
	}

	inline bool isLinux()
	{
		#ifdef KEENGINE_LINUX
		return true;
		#else
		return false;
		#endif	
	}

	inline bool isFreeBSD()
	{
		#ifdef KEENGINE_FREEBSD
		return true;
		#else
		return false;
		#endif	
	}

}

#endif // KE_CONFIG_HPP
