#pragma once

/*
	This file contains data about the platform we're running the app on,
	the configuration settings we are using, and potentialy the API(s) we are using
*/

#if defined(_WIN32)
	#if defined(_WIN64)
		#define PR_WINDOWS_64
	#else
		#error "Only 64 bit Windows is supported!"
	#endif
#elif defined(unix) || defined(_unix) || defined(_unix_)
	#error "Linux is not supported!"
#elif defined(__APPLE__) || defined(__MACH__)
	#error "Mac OS is currently not supported!" 
#elif defined(__ANDROID__)
	#define PR_ANDROID
	//#error "Android is currently not supported!"
#else
	#error "This OS is currently not supported!"
#endif

#if defined(PR_DEBUG)
	#define PR_ENABLE_DEBUGGING
	#define PR_VK_ENABLE_VALIDATION_LAYERS
#else
	#define PR_DISABLE_DEBUGGING
	#define PR_VK_DISABLE_VALIDATION_LAYERS
#endif