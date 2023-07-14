#include <Application.h>

namespace BSE{
	// DONE: Figure out how to allow this instance through static library
	// Current answer: no-how.
	// The static library has its own memory zone where it stores its objects,
	// so it's a bad idea to rely on its global variables or static pointers.
	Application* Application::s_Instance = nullptr;
	
	Application::Application() {
		s_Instance = this;
		
		// TODO: figure out how to fix crash if s_Instance != nullptr
		// (happens when -D BSE_ENABLE_ASSERTS)
		BSE_CORE_ASSERT((s_Instance == nullptr), "Application already exists.");
		
		// Create an App window and set callbacks
		BSE_TRACE("Trying to create an app window");
		m_Window = Window::Create(*(new WindowProperties()));
		BSE_TRACE("Window created and stored in m_Window");
		
		m_Window->SetEventCallback([this](Event& event){
			OnEvent(event);
		});
		
		BSE_TRACE("OnEvent callback bind successfully");
		
		// ImGui Overlay Enable/Disable
		m_ImGuiLayerEnabled = true;
		
		// Set Renderer API
		RenderCommand::SetAPI(RendererAPI::API::OpenGL);
		BSE_CORE_TRACE("Render API set to OpenGL");
	}
	
	Application::~Application(){
		if (m_ImGuiLayerEnabled && (m_ImGuiLayer != nullptr)){
			PopOverlay(m_ImGuiLayer);
			delete m_ImGuiLayer;
			m_ImGuiLayer = nullptr;
		}
		BSE_CORE_INFO("Main App destroyed");
	}
	
	void Application::PushLayer(Layer* layer){
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	
	void Application::PopLayer(Layer* layer){
		m_LayerStack.PopLayer(layer);
		layer->OnDetach();
	}
	
	void Application::PushOverlay(Layer* overlay){
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
	
	void Application::PopOverlay(Layer* overlay){
		m_LayerStack.PopOverlay(overlay);
		overlay->OnDetach();
	}
	
	void Application::OnEvent(Event& e){
		EventDispatcher dispatcher(e);
		
		dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& event){
			// TODO: Stack events using a special method
			// stacked events are to be processed in the game loop by a special routine which calls OnWindowClose, etc.
			return OnWindowClose(event);
		});
		
		dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& event){
			return OnKeyPressed(event);
		});
		
		// BSE_INFO("{0}", e);
		
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ){
			(*--it)->OnEvent(e);
			if (e.IsHandled()){
				break;
			}
		}
	}
	
	void Application::Run(){
		BSE_TRACE("Enter Application Run routine");
		
		if (GetImGuiLayer() == nullptr){
			SetImGuiLayer(new ImGuiLayer()); 
			PushOverlay(GetImGuiLayer());
			BSE_TRACE("ImGui layer pushed into m_LayerStack");
		}
		
		while(m_Running){
			// Layers
			for (Layer* layer : m_LayerStack){
				layer->OnUpdate();
			}
			
			// Overlays
			if (m_ImGuiLayerEnabled && (m_ImGuiLayer != nullptr)){
				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack){
					layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}
			
			// --------------------------------------------------
			// UPDATE
			m_Window->OnUpdate();
		}
	}
	
	// ------------------------------------
	// Events
	
	bool Application::OnWindowClose(WindowCloseEvent& e){
		m_Running = false;
		return true;
	}
	
	bool Application::OnKeyPressed(KeyPressedEvent& e){
		// toggle ImGuiLayer on/off
		if (e.GetKeyCode() == BSE_KEY_F2){
			m_ImGuiLayerEnabled = !m_ImGuiLayerEnabled;
			/*
			// !!! Problem !!!
			// after OnDetach the ImGui Context is destroyed which means
			// that it should be restored in main program after OnAttach AGAIN!
			if (m_ImGuiLayerEnabled && (m_ImGuiLayer != nullptr)) { // turn imgui on
				m_LayerStack.PushOverlay(m_ImGuiLayer);
				m_ImGuiLayer->OnAttach();
			}
			if (!m_ImGuiLayerEnabled && (m_ImGuiLayer != nullptr)) { // turn imgui off
				m_LayerStack.PopOverlay(m_ImGuiLayer);
				m_ImGuiLayer->OnDetach();
			}
			*/
			return true;
		}
		return false;
	}
}
