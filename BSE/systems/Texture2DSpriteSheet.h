#ifndef BSE_TEXTURE2DSPRITESHEET_H
#define BSE_TEXTURE2DSPRITESHEET_H

#include <Core.h>
#include <renderer/Texture.h>

namespace BSE {
	class BSE_API Texture2DSprite {
	public:
		Texture2DSprite(Texture2D* texture, BSE_Rect& subTexture) {
			m_Texture = texture;
			
			float spriteWidth = subTexture.w;
			float spriteHeight = subTexture.h;
			
			float sheetWidth = (float)(m_Texture->GetWidth());
			float sheetHeight = (float)(m_Texture->GetHeight());
			
			float spriteX = subTexture.x; 
			float spriteY = subTexture.y;
			
			float tc0x = spriteX / sheetWidth;
			if (tc0x > 1.0f)
				tc0x = 1.0f;
			if (tc0x < 0.0f)
				tc0x = 0.0f;
			float tc0y = spriteY / sheetHeight;
			if (tc0y > 1.0f)
				tc0y = 1.0f;
			if (tc0y < 0.0f)
				tc0y = 0.0f;
			float tc1x = (spriteX + spriteWidth) / sheetWidth;
			if (tc1x > 1.0f)
				tc1x = 1.0f;
			if (tc1x < 0.0f)
				tc1x = 0.0f;
			float tc1y = (spriteY + spriteHeight) / sheetHeight;
			if (tc1y > 1.0f)
				tc1y = 1.0f;
			if (tc1y < 0.0f)
				tc1y = 0.0f;
			
			textureCoordinates[0] = { tc0x , tc0y };
			textureCoordinates[1] = { tc1x , tc0y };
			textureCoordinates[2] = { tc1x , tc1y };
			textureCoordinates[3] = { tc0x , tc1y };
		}
		
		glm::vec2* GetCoordinates() { 
			return textureCoordinates; 
		}
		
		Texture2D* GetSpriteSheet() {
			return m_Texture;
		}
		
		void FlipHorizontally(){
			std::swap(textureCoordinates[0], textureCoordinates[1]);
			std::swap(textureCoordinates[3], textureCoordinates[2]);
		}
		
		void FlipVertically(){
			std::swap(textureCoordinates[0], textureCoordinates[3]);
			std::swap(textureCoordinates[1], textureCoordinates[2]);
		}
		
	private:
		glm::vec2 textureCoordinates[4];
		Texture2D* m_Texture;
	};
	
	// =====================================
	typedef std::unordered_map<std::string, Texture2DSprite*> BSE_SpritePack; // sprites of one type or one object 
	typedef std::unordered_map<uint32_t, BSE_SpritePack*> BSE_SpriteSheet; // sprites collections
	typedef std::pair<uint32_t, std::string> BSE_Tile; // tiles combine into a tile map
	
	BSE_API BSE_SpriteSheet CreateSpriteSheet(const std::string& filename);
}

#endif
