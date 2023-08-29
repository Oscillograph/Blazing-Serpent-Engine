#ifndef BSE_FILEIO_H
#define BSE_FILEIO_H

#include <Core.h>

namespace BSE {
	class BSE_API FileIO {
	public:
		//static void ConstructFileSystem();
		
		static std::string GetRawText(std::string filename);
		
		static bool WriteRawText(const std::string& filename, const char* text);
		
		static std::string GetName(std::string filepath);
	};
}

#endif
