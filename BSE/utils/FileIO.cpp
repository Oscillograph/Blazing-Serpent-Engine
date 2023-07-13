#include <utils/FileIO.h>

namespace BSE {
	std::string FileIO::GetRawText(std::string filename){
		std::ifstream iFile; // input file descriptor
		std::string lineRead; // buffer for strings
		std::string output = "";
		const char delimLine = '\n'; // delimeter between lines
		
		if (!iFile.is_open()){
			iFile.open(filename.c_str());
			if(iFile.is_open()){
				int i = 0;
				while (std::getline(iFile, lineRead, delimLine)){
					output += (lineRead + "\n");
				}
			}
		}
		
		return output;
	}
}
