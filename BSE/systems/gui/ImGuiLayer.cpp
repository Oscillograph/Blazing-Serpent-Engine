#include <Core.h>
#include <Layer.h>
#include "./ImGuiLayer.h"

#include "./vendor/imgui/imgui.h"
#include "./platforms/opengl/ImGuiRenderer.h"
#include <glfw/glfw3.h>


namespace BSE {
	ImGuiLayer::ImGuiLayer(Application* app)
		: Layer("ImGuiLayer")
	{
		m_Time = 0.0f;
		m_App = app;
	}
	
	ImGuiLayer::~ImGuiLayer(){
		
	}
	
	void ImGuiLayer::OnAttach(){
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO ioFlags = ImGui::GetIO();
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
		
		ImGui_ImplOpenGL3_Init("#version 410");
	}
	
	void ImGuiLayer::OnDetach(){
		
	}
	
	void ImGuiLayer::OnUpdate(){
		ImGuiIO& io = ImGui::GetIO();
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
		static char* buf = "One Два !@#";
		//ImGui::ShowDemoWindow(&show);
		//ImGui::ShowDemoWindow();
		ImGui::Text("Hello, world %d", 123);
		ImGui::Button("Save");
		ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	
	void ImGuiLayer::OnEvent(Event& event){
		
	}
	
}
