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
			} else {
				BSE_CORE_ERROR("Couldn't open file: {0}", filename);
			}
		}
		
		return output;
	}
	
	std::string FileIO::GetName(std::string filepath){
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = (lastSlash == std::string::npos) ? (0) : (lastSlash+1);
		
		auto lastDot = filepath.find_last_of(".");
		auto symbols = (lastDot == std::string::npos) ? (filepath.size() - lastSlash) : (lastDot - lastSlash);
		return filepath.substr(lastSlash, symbols);
	}
}
