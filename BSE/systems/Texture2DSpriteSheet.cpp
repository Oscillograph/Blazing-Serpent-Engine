#include <systems/Texture2DSpriteSheet.h>

namespace BSE {
	BSE_SpriteSheet CreateSpriteSheet(const std::string& filename){
		// 0. Read spriteSheetText
		// std::string spriteSheetText = FileIO::GetRawText(filename);
		
		// 1. Parse spriteSheetText
		// nlohmann::json spriteSheetJSON = nlohmann::json::parse(std::ifstream(filename));
		// nlohmann::json spriteSheetJSON = nlohmann::json::parse(spriteSheetText);
		
		// 2. Combine to BSE_SpriteSheet
		BSE_SpriteSheet spriteSheet;
		/*
		for (auto kv : spriteSheetJSON.items()) {
			auto key = kv.first();
			auto value = kv.second();
			spriteSheet[key] = value;
		}
		*/
		return spriteSheet;
	}
}
