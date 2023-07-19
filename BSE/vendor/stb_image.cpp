#include <Core.h>

#ifdef BSE_PLATFORM_WINDOWS
	// for stb_image.h : Unicode filenames on Windows
	#define STBI_WINDOWS_UTF8
#endif
#define STB_IMAGE_IMPLEMENTATION
#include <vendor/stb_image.h> // to work with images file formats