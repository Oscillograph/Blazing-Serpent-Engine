#ifndef BSE_FILEIO_H
#define BSE_FILEIO_H

#include <Core.h>

namespace BSE {
	class FileIO {
	public:
		static std::string GetRawText(std::string filename);
		//static void ConstructFileSystem();
	};
}

#endif
