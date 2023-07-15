#ifndef BSE_INPUT_H
#define BSE_INPUT_H

#include <Core.h>

namespace BSE {
	class BSE_API Input {
	public:
		inline static bool IsKeyPressed(int keycode){
			return s_Instance->IsKeyPressedImplementation(keycode);
		}
		
		inline static bool IsMouseButtonPressed(int button){
			return s_Instance->IsMouseButtonPressedImplementation(button);
		}
		
		inline static std::pair<float, float> GetMousePosition(){
			return s_Instance->GetMousePositionImplementation();
		}
		
		inline static float GetMouseX(){
			return s_Instance->GetMouseXImplementation();
		}
		
		inline static float GetMouseY(){
			return s_Instance->GetMouseYImplementation();
		}
		
		static Input* s_Instance;
		
	protected:
		virtual bool IsKeyPressedImplementation (int keycode) = 0;
		
		virtual bool IsMouseButtonPressedImplementation (int button) = 0;
		virtual std::pair<float, float> GetMousePositionImplementation() = 0;
		virtual float GetMouseXImplementation() = 0;
		virtual float GetMouseYImplementation() = 0; 
	};
	
	
}

#endif
