#ifndef BSE_CORE_H
#define BSE_CORE_H

#include <ProtoCore.h>
#include <log.h>
#include <Misc.h>
#include <utils/FileIO.h>
#include <utils/Time.h>
#include <utils/Profiler.h>
// #include <vendor/json.hpp>
// #include <vendor/entt/entt.hpp>

// basic functions
namespace BSE {
	// BSE_API void print_hello(); 
	
	// BSE_API void Callback_dummy(Event& event);
	struct BSE_API BSE_Rect {
		float x;
		float y;
		float w;
		float h;
	};
	
	/*
	struct BSE_API BSE_SubTexture {
		BSE_SubTexture(const glm::vec2& textureSize, BSE_Rect subTexture){
			float x = subTexture->x / subTexture->w; 
			float y = subTexture->y / subTexture->h;
			float sheetWidth = textureSize.x;
			float sheetHeight = textureSize.y;
			float spriteWidth = subTexture->w;
			float spriteHeight = subTexture->h;
			
			float tc0x = x / sheetWidth;
			if (tc0x > 1.0f)
				tc0x = 1.0f;
			if (tc0x < 0.0f)
				tc0x = 0.0f;
			float tc0y = y / sheetHeight;
			if (tc0y > 1.0f)
				tc0y = 1.0f;
			if (tc0y < 0.0f)
				tc0y = 0.0f;
			float tc1x = (x + spriteWidth) / sheetWidth;
			if (tc1x > 1.0f)
				tc1x = 1.0f;
			if (tc1x < 0.0f)
				tc1x = 0.0f;
			float tc1y = (y + spriteHeight) / sheetHeight;
			if (tc1y > 1.0f)
				tc1y = 1.0f;
			if (tc1y < 0.0f)
				tc1y = 0.0f;
			
			textureCoordinates[0] = { tc0x , tc0y };
			textureCoordinates[1] = { tc1x , tc0y };
			textureCoordinates[2] = { tc1x , tc1y };
			textureCoordinates[3] = { tc0x , tc1y };
		}
		
		inline const glm::vec2* GetCoordinates() const { return textureCoordinates; }
		
	private:
		glm::vec2 textureCoordinates[4];
	};
	*/
}

#endif
