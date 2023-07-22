#ifndef BSE_FILEIO_H
#define BSE_FILEIO_H

#include <Core.h>

namespace BSE {
	class BSE_API FileIO {
	public:
		static std::string GetRawText(std::string filename);
		//static void ConstructFileSystem();
		static std::string GetName(std::string filepath);
	};
}

#endif
