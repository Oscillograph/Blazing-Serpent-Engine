#include <Core.h>
#include <Layer.h>
#include "./ImGuiLayer.h"

#include "./vendor/imgui/imgui.h"
#include "./platforms/opengl/ImGuiRenderer.h"

// Temporary
#include <glfw/glfw3.h>
#include <Glad/include/glad/glad.h>


namespace BSE {
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
		m_Time = 0.0f;
		m_App = Application::Get();
	}
	
	ImGuiLayer::~ImGuiLayer(){
		
	}
	
	void ImGuiLayer::OnAttach(){
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& ioFlags = ImGui::GetIO();
		
		// key bindings
		ioFlags.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		ioFlags.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		
		ioFlags.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		ioFlags.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		ioFlags.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		ioFlags.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		ioFlags.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		ioFlags.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		ioFlags.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		ioFlags.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		ioFlags.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		ioFlags.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		ioFlags.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		ioFlags.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		ioFlags.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		ioFlags.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		ioFlags.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		ioFlags.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		ioFlags.KeyMap[ImGuiKey_B] = GLFW_KEY_B;
		ioFlags.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		ioFlags.KeyMap[ImGuiKey_D] = GLFW_KEY_D;
		ioFlags.KeyMap[ImGuiKey_E] = GLFW_KEY_E;
		ioFlags.KeyMap[ImGuiKey_F] = GLFW_KEY_F;
		ioFlags.KeyMap[ImGuiKey_G] = GLFW_KEY_G;
		ioFlags.KeyMap[ImGuiKey_H] = GLFW_KEY_H;
		ioFlags.KeyMap[ImGuiKey_I] = GLFW_KEY_I;
		ioFlags.KeyMap[ImGuiKey_J] = GLFW_KEY_J;
		ioFlags.KeyMap[ImGuiKey_K] = GLFW_KEY_K;
		ioFlags.KeyMap[ImGuiKey_L] = GLFW_KEY_L;
		ioFlags.KeyMap[ImGuiKey_M] = GLFW_KEY_M;
		ioFlags.KeyMap[ImGuiKey_N] = GLFW_KEY_N;
		ioFlags.KeyMap[ImGuiKey_O] = GLFW_KEY_O;
		ioFlags.KeyMap[ImGuiKey_P] = GLFW_KEY_P;
		ioFlags.KeyMap[ImGuiKey_Q] = GLFW_KEY_Q;
		ioFlags.KeyMap[ImGuiKey_R] = GLFW_KEY_R;
		ioFlags.KeyMap[ImGuiKey_S] = GLFW_KEY_S;
		ioFlags.KeyMap[ImGuiKey_T] = GLFW_KEY_T;
		ioFlags.KeyMap[ImGuiKey_U] = GLFW_KEY_U;
		ioFlags.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		ioFlags.KeyMap[ImGuiKey_W] = GLFW_KEY_W;
		ioFlags.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		ioFlags.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		ioFlags.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
		
		// cyrillic support
		ImFontConfig font_config;
		font_config.OversampleH = 1; //or 2 is the same
		font_config.OversampleV = 1;
		font_config.PixelSnapH = 1;
		
		static const ImWchar ranges[] = {
			0x0020, 0x00FF, // Basic Latin + Latin Supplement
			0x0400, 0x044F, // Cyrillic
			0,
		};
		
		ioFlags.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 14.0f, &font_config, ranges);
		
		// ImGui OpenGL init
		ImGui_ImplOpenGL3_Init("#version 410");
	}
	
	void ImGuiLayer::OnDetach(){
		
	}
	
	void ImGuiLayer::OnUpdate(){
		ImGuiIO& io = ImGui::GetIO();
		//Application* app = Application::Get();
		Window* window = m_App->GetWindow();
		float width = (float)(window->GetWidth());
		float height = (float)(window->GetHeight());
		//BSE_CORE_INFO("App's window size: {0}, {1}", width, height);
		io.DisplaySize = ImVec2(width, height);
		
		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f );
		m_Time = time;
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		
		static bool show = true;
		static float f = 0.0f;
		static char* buf = u8"One Два !@#";
		static char* text =	u8"На самом деле не так-то и сложно писать на русском в Dear ImGui, \n\
		если суметь правильно настроить работу со шрифтом.";
		
		ImGui::ShowDemoWindow(&show);
		//ImGui::Text("Привет, мир!!!%d", 111);
		//ImGui::Text(text);
		//ImGui::Button(u8"Сохранить");
		//ImGui::InputText(u8"Введите текст", buf, IM_ARRAYSIZE(buf));
		//ImGui::SliderFloat(u8"Какая-то дробь", &f, 0.0f, 1.0f);
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	
	void ImGuiLayer::OnEvent(Event& event){
		
		EventDispatcher dispatcher(event);
		
		dispatcher.Dispatch<MouseButtonPressed>([this](MouseButtonPressed& event){
			return ImGuiLayer::OnMouseButtonPressed(event);
		});
		
		dispatcher.Dispatch<MouseButtonReleased>([this](MouseButtonReleased& event){
			return ImGuiLayer::OnMouseButtonReleased(event);
		});
		
		dispatcher.Dispatch<MouseMovedEvent>([this](MouseMovedEvent& event){
			return ImGuiLayer::OnMouseMoved(event);
		});
		
		dispatcher.Dispatch<MouseScrolledEvent>([this](MouseScrolledEvent& event){
			return ImGuiLayer::OnMouseScrolled(event);
		});
		
		dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& event){
			return ImGuiLayer::OnKeyPressed(event);
		});
		
		dispatcher.Dispatch<KeyReleasedEvent>([this](KeyReleasedEvent& event){
			return ImGuiLayer::OnKeyReleased(event);
		});
		
		dispatcher.Dispatch<KeyTypedEvent>([this](KeyTypedEvent& event){
			return ImGuiLayer::OnKeyTyped(event);
		});
		
		dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& event){
			return ImGuiLayer::OnWindowResized(event);
		});
	}
	
	// events
	bool ImGuiLayer::OnMouseButtonPressed(MouseButtonPressed& event){
		//int MouseButton = event.GetMouseButtonCode();
		
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButtonCode()] = true;

		//ImVec2 mouseXY = ImGui::GetCursorPos();
		
		BSE_CORE_TRACE("ImGui Layer: {0}", event);
		//BSE_CORE_TRACE("Mouse button: {0}", MouseButton);
		//BSE_CORE_TRACE("Mouse position: {0}, {1}", mouseXY.x, mouseXY.y);
		
		return false;
	}
	
	bool ImGuiLayer::OnMouseButtonReleased(MouseButtonReleased& event){
		BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButtonCode()] = false;
		
		return false;
	}
	
	bool ImGuiLayer::OnMouseMoved(MouseMovedEvent& event){
		BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(event.GetX(), event.GetY());
		
		return false;
	}
	
	bool ImGuiLayer::OnMouseScrolled(MouseScrolledEvent& event){
		BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += event.GetXOffset();
		io.MouseWheel  += event.GetYOffset();
		
		return false;
	}
	
	bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& event){
		BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = true;
		
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		
		return false;
	}
	
	bool ImGuiLayer::OnKeyTyped(KeyTypedEvent& event) {
		BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		ImGuiIO& io = ImGui::GetIO();
		int c = event.GetKeyCode();
		
		if ((c > 0) && (c < 0x10000)){
			io.AddInputCharacter((unsigned short)c);
		}
		
		return false;
	}
	
	bool ImGuiLayer::OnKeyReleased(KeyReleasedEvent& event){
		BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = false;
		
		return false;
	}
	
	bool ImGuiLayer::OnWindowResized(WindowResizeEvent& event){
		BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		ImGuiIO& io = ImGui::GetIO();
		Window* window = m_App->GetWindow();
		io.DisplaySize = ImVec2((float)(window->GetWidth()), (float)(window->GetHeight()));
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
		
		return false;
	}
}
