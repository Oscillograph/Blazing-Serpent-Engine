#include <Core.h>
#include <platforms/windows/WindowsInput.h>

#include <Application.h>
#include <glfw/glfw3.h>

#include <Input.h>

namespace BSE {
	Input* Input::s_Instance = new WindowsInput();
	
	bool WindowsInput::IsKeyPressedImplementation(int keycode){
		auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return (state == GLFW_PRESS) || (state == GLFW_REPEAT);  
	}
	
	bool WindowsInput::IsMouseButtonPressedImplementation (int button) {
		auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return (state == GLFW_PRESS);
	}
	
	std::pair<float, float> WindowsInput::GetMousePositionImplementation() {
		auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return {(float)xpos, (float)ypos};
	}
	
	float WindowsInput::GetMouseXImplementation(){
		auto[x, y] = GetMousePositionImplementation();
		return x;
	}
	
	float WindowsInput::GetMouseYImplementation(){
		auto[x, y] = GetMousePositionImplementation();
		return y;
	}
}
