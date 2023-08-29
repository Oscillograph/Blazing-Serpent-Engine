#ifndef BSE_PLATFORMUTILS_H
#define BSE_PLATFORMUTILS_H

#include <Core.h>

namespace BSE {
	class BSE_API FileDialogs {
	public:
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};
}

#endif
