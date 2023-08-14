#ifndef BSE_WINDOWSINPUT_H
#define BSE_WINDOWSINPUT_H

#include <Core.h>
#include <Input.h>

namespace BSE {
	/*
	class BSE_API WindowsInput : public Input {
	protected:
		bool IsKeyPressedImplementation (int keycode) override;
		
		bool IsMouseButtonPressedImplementation (int button) override;
		std::pair<float, float> GetMousePositionImplementation() override;
		float GetMouseXImplementation() override;
		float GetMouseYImplementation() override;
	};
	*/
	
	class BSE_API Input {
	public:
		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}

#endif
