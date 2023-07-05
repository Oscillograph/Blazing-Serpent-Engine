#include <Core.h>
#include <Layer.h>
#include "./ImGuiLayer.h"

#include <vendor/imgui/imgui.h>
#include <systems/gui/ImGuiBuild.h>

namespace BSE {
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
		m_Time = 0.0f;
		m_io = nullptr;
		// m_App = Application::Get();
	}
	
	ImGuiLayer::~ImGuiLayer(){
		BSE_TRACE("Destroy ImGuiLayer");
	}
	
	void ImGuiLayer::OnAttach(){
		m_ImGuiContext = ImGui::CreateContext();
		BSE_TRACE("Dear ImGui Context created");
		ImGui::GetAllocatorFunctions(&m_ImGuiMemAllocFunc, &m_ImGuiMemFreeFunc, &m_ImGuiUserData);
		BSE_TRACE("Dear ImGui memory alloc/free functions stored");
		// ImGui::SetAllocatorFunctions(m_ImGuiMemAllocFunc, m_ImGuiMemFreeFunc, NULL);
		
		m_io = &(ImGui::GetIO());
		
		m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // enable keyboard conrols
		m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // enable gamepad controls
		m_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable; // enable docking
		m_io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // enable viewports; TODO: learn about them
		
		// setup ImGui style
		ImGui::StyleColorsDark();
		// ImGui::StyleColorsLight();
		// ImGui::StyleColorsClassic();
		
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_NavWindowingDimBg].w = 1.0f;
		
		Application* m_App = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(m_App->GetWindow()->GetNativeWindow());
		
		// key bindings
		m_io->BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		m_io->BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		
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
		
		// TODO: fix ё
		m_io->Fonts->AddFontFromFileTTF("./assets/fonts/tahoma.ttf", 14.0f, &font_config, ranges);
		// m_io->Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 14.0f, &font_config, ranges);
		// m_io->Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 14.0f, &font_config, ranges);
		
		// ImGui OpenGL init
		ImGui_ImplOpenGL3_Init("#version 410");
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		BSE_TRACE("ImGuiLayer attached, and Dear ImGui OpenGl/Glfw Implementation initialized.");
	}
	
	void ImGuiLayer::OnDetach(){
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		BSE_TRACE("ImGuiLayer detached, and Dear ImGui OpenGl/Glfw Implementation shut down.");
	}
	
	void ImGuiLayer::Begin(){
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	
	void ImGuiLayer::ImGuiContent(){
		static bool show = true;	
		ImGui::ShowDemoWindow(&show);
	}
	
	void ImGuiLayer::End(){
		if (m_io != nullptr){
			Application* m_App = Application::Get();
			Window* window = m_App->GetWindow();
			float width = (float)(window->GetWidth());
			float height = (float)(window->GetHeight());
			//BSE_CORE_INFO("App's window size: {0}, {1}", width, height);
			m_io->DisplaySize = ImVec2(width, height);
		
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			
			if (m_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable){
				GLFWwindow* window_backup_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(window_backup_context);
			}
		}
	}
	
	void ImGuiLayer::OnImGuiRender(){
		float time = (float)glfwGetTime();
		m_io->DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f );
		m_Time = time;

		ImGuiContent();
	}
	
	/*
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
		
		//BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		return false;
	}
	
	bool ImGuiLayer::OnMouseButtonReleased(MouseButtonReleased& event){
		//BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		m_io->MouseDown[event.GetMouseButtonCode()] = false;
		
		return false;
	}
	
	bool ImGuiLayer::OnMouseMoved(MouseMovedEvent& event){
		//BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		m_io->MousePos = ImVec2(event.GetX(), event.GetY());
		
		return false;
	}
	
	bool ImGuiLayer::OnMouseScrolled(MouseScrolledEvent& event){
		//BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		m_io->MouseWheelH += event.GetXOffset();
		m_io->MouseWheel  += event.GetYOffset();
		
		return false;
	}
	
	bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& event){
		//BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		m_io->KeysDown[event.GetKeyCode()] = true;
		
		m_io->KeyCtrl = m_io->KeysDown[BSE_KEY_LEFT_CONTROL] || m_io->KeysDown[BSE_KEY_RIGHT_CONTROL];
		m_io->KeyShift = m_io->KeysDown[BSE_KEY_LEFT_SHIFT] || m_io->KeysDown[BSE_KEY_RIGHT_SHIFT];
		m_io->KeyAlt = m_io->KeysDown[BSE_KEY_LEFT_ALT] || m_io->KeysDown[BSE_KEY_RIGHT_ALT];
		m_io->KeySuper = m_io->KeysDown[BSE_KEY_LEFT_SUPER] || m_io->KeysDown[BSE_KEY_RIGHT_SUPER];
		
		return false;
	}
	
	bool ImGuiLayer::OnKeyTyped(KeyTypedEvent& event) {
		//BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		int keycode = event.GetKeyCode();
		
		if ((keycode > 0) && (keycode < 0x10000)){
			m_io->AddInputCharacter((unsigned short)keycode);
		}
		
		return false;
	}
	
	bool ImGuiLayer::OnKeyReleased(KeyReleasedEvent& event){
		//BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		m_io->KeysDown[event.GetKeyCode()] = false;
		
		return false;
	}
	
	bool ImGuiLayer::OnWindowResized(WindowResizeEvent& event){
		//BSE_CORE_TRACE("ImGui Layer: {0}", event);
		
		Window* window = m_App->GetWindow();
		m_io->DisplaySize = ImVec2((float)(window->GetWidth()), (float)(window->GetHeight()));
		m_io->DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
		
		return false;
	}
	*/
}
