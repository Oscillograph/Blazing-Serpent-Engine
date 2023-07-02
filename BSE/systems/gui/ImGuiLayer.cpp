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
		BSE_TRACE("Destroy ImGuiLayer");
	}
	
	void ImGuiLayer::OnAttach(){
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		
		m_io = &(ImGui::GetIO());
		
		// key bindings
		m_io->BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		m_io->BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		
		m_io->KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		m_io->KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		m_io->KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		m_io->KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		m_io->KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		m_io->KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		m_io->KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		m_io->KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		m_io->KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		m_io->KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		m_io->KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		m_io->KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		m_io->KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		m_io->KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		m_io->KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		m_io->KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		m_io->KeyMap[ImGuiKey_B] = GLFW_KEY_B;
		m_io->KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		m_io->KeyMap[ImGuiKey_D] = GLFW_KEY_D;
		m_io->KeyMap[ImGuiKey_E] = GLFW_KEY_E;
		m_io->KeyMap[ImGuiKey_F] = GLFW_KEY_F;
		m_io->KeyMap[ImGuiKey_G] = GLFW_KEY_G;
		m_io->KeyMap[ImGuiKey_H] = GLFW_KEY_H;
		m_io->KeyMap[ImGuiKey_I] = GLFW_KEY_I;
		m_io->KeyMap[ImGuiKey_J] = GLFW_KEY_J;
		m_io->KeyMap[ImGuiKey_K] = GLFW_KEY_K;
		m_io->KeyMap[ImGuiKey_L] = GLFW_KEY_L;
		m_io->KeyMap[ImGuiKey_M] = GLFW_KEY_M;
		m_io->KeyMap[ImGuiKey_N] = GLFW_KEY_N;
		m_io->KeyMap[ImGuiKey_O] = GLFW_KEY_O;
		m_io->KeyMap[ImGuiKey_P] = GLFW_KEY_P;
		m_io->KeyMap[ImGuiKey_Q] = GLFW_KEY_Q;
		m_io->KeyMap[ImGuiKey_R] = GLFW_KEY_R;
		m_io->KeyMap[ImGuiKey_S] = GLFW_KEY_S;
		m_io->KeyMap[ImGuiKey_T] = GLFW_KEY_T;
		m_io->KeyMap[ImGuiKey_U] = GLFW_KEY_U;
		m_io->KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		m_io->KeyMap[ImGuiKey_W] = GLFW_KEY_W;
		m_io->KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		m_io->KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		m_io->KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
		
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
		
		m_io->Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 14.0f, &font_config, ranges);
		// m_io->Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 14.0f, &font_config, ranges);
		
		// ImGui OpenGL init
		ImGui_ImplOpenGL3_Init("#version 410");
	}
	
	void ImGuiLayer::OnDetach(){
		
	}
	
	void ImGuiLayer::OnUpdate(){
		if (m_io != nullptr){
			Window* window = m_App->GetWindow();
			float width = (float)(window->GetWidth());
			float height = (float)(window->GetHeight());
			//BSE_CORE_INFO("App's window size: {0}, {1}", width, height);
			m_io->DisplaySize = ImVec2(width, height);
			
			float time = (float)glfwGetTime();
			m_io->DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f );
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
	}
	
	void ImGuiLayer::OnEvent(Event& event){
		if (m_io != nullptr){
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
	}
	
	// --------------------------------------------------------------------------------
	// Events
	bool ImGuiLayer::OnMouseButtonPressed(MouseButtonPressed& event){
		m_io->MouseDown[event.GetMouseButtonCode()] = true;
		
		BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		return false;
	}
	
	bool ImGuiLayer::OnMouseButtonReleased(MouseButtonReleased& event){
		BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		m_io->MouseDown[event.GetMouseButtonCode()] = false;
		
		return false;
	}
	
	bool ImGuiLayer::OnMouseMoved(MouseMovedEvent& event){
		BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		m_io->MousePos = ImVec2(event.GetX(), event.GetY());
		
		return false;
	}
	
	bool ImGuiLayer::OnMouseScrolled(MouseScrolledEvent& event){
		BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		m_io->MouseWheelH += event.GetXOffset();
		m_io->MouseWheel  += event.GetYOffset();
		
		return false;
	}
	
	bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& event){
		BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		m_io->KeysDown[event.GetKeyCode()] = true;
		
		m_io->KeyCtrl = m_io->KeysDown[GLFW_KEY_LEFT_CONTROL] || m_io->KeysDown[GLFW_KEY_RIGHT_CONTROL];
		m_io->KeyShift = m_io->KeysDown[GLFW_KEY_LEFT_SHIFT] || m_io->KeysDown[GLFW_KEY_RIGHT_SHIFT];
		m_io->KeyAlt = m_io->KeysDown[GLFW_KEY_LEFT_ALT] || m_io->KeysDown[GLFW_KEY_RIGHT_ALT];
		m_io->KeySuper = m_io->KeysDown[GLFW_KEY_LEFT_SUPER] || m_io->KeysDown[GLFW_KEY_RIGHT_SUPER];
		
		return false;
	}
	
	bool ImGuiLayer::OnKeyTyped(KeyTypedEvent& event) {
		BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		int keycode = event.GetKeyCode();
		
		if ((keycode > 0) && (keycode < 0x10000)){
			m_io->AddInputCharacter((unsigned short)keycode);
		}
		
		return false;
	}
	
	bool ImGuiLayer::OnKeyReleased(KeyReleasedEvent& event){
		BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		m_io->KeysDown[event.GetKeyCode()] = false;
		
		return false;
	}
	
	bool ImGuiLayer::OnWindowResized(WindowResizeEvent& event){
		BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		Window* window = m_App->GetWindow();
		m_io->DisplaySize = ImVec2((float)(window->GetWidth()), (float)(window->GetHeight()));
		m_io->DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
		
		return false;
	}
}
