#include <Application.h>
// #include <renderer/Renderer.h>

// TODO: share framebuffers of layers through GameData and|or AssetManager structures,
// otherwise I can't use OnImGuiRender() to view a scene, as the method resides in ImGuiLayers.
// ImGuiLayers are separated from Layers and can't read their data directly - need an API.
// Trying to use OnImGuiLayer method from a Layer crashes app as DLL does't share memory with EXE.

namespace BSE{
	// DONE: Figure out how to allow this instance through static library
	// Current answer: no-how.
	// The static library has its own memory zone where it stores its objects,
	// so it's a bad idea to rely on its global variables or static pointers.
	Application* Application::s_Instance = nullptr;
	
	Application::Application() {
		BSE_PROFILE_FUNCTION();
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
		
		Renderer::Init();
	}
	
	Application::~Application(){
		// Renderer2D::Shutdown();
		Renderer::Shutdown();
		
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
		
		dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& event){
			return OnWindowResize(event);
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
		BSE_PROFILE_FUNCTION();
		BSE_TRACE("Enter Application Run routine");
		
		if (GetImGuiLayer() == nullptr){
			SetImGuiLayer(new ImGuiLayer()); 
			PushOverlay(GetImGuiLayer());
			BSE_TRACE("ImGui layer pushed into m_LayerStack");
		}
		
		// This is an implementation of GAME CYCLE pattern.
		// EVENTS are processed via handlers implemented through the use of 
		// an event dispatcher and lambdas to corresponding layer/window methods.
		// USER INPUT is processed through events.
		// The task of a cycle is to organize calls to update state of a layer/window and renderer.
		// RENDERING is configured individually for a layer inside its .cpp-file of the game app.
		int updatesCounter = 0;
		while(m_Running){
			// --------------------------------------------------
			// 						TIME
			// --------------------------------------------------
			float currentTime = m_Window->GetTime();
			float deltaTime = currentTime - m_LastFrameTime;
			m_FrameTime += deltaTime;
			m_LastFrameTime = currentTime;
			// Profiler::Flush();
			
			// --------------------------------------------------
			// 					   UPDATE
			// --------------------------------------------------
			updatesCounter = 0;
			
			if (!m_Minimized){
				if (m_FrameTime >= GameData::FPS_deltaTime){
					// general framebuffer clear
					Renderer2D::Clear(GameData::RendererClearColor);
					
					// Layers
					for (Layer* layer : m_LayerStack){
						// BSE_TRACE("Layer {0} selected", layer->GetName());
						updatesCounter += layer->OnUpdate(m_FrameTime);
					}
					
					// Overlays
					if (m_ImGuiLayerEnabled && (m_ImGuiLayer != nullptr)){
						m_ImGuiLayer->Begin();
						for (Layer* layer : m_LayerStack){
							layer->OnImGuiRender(m_FrameTime);
						}
						m_ImGuiLayer->End();
					}
					
					m_FrameTime = 0.0f;
				}
			}
			
			// Window
			// BSE_INFO("Changes since last frame: {0}", updatesCounter);
			m_Window->OnUpdate(updatesCounter);
		}
	}
	
	// ------------------------------------
	// Events
	
	bool Application::OnWindowClose(WindowCloseEvent& e){
		m_Running = false;
		return true;
	}
	
	bool Application::OnWindowResize(WindowResizeEvent& e){
		uint32_t width = e.GetWidth();
		uint32_t height = e.GetHeight();
		if ((width == 0) || (height == 0)){
			m_Minimized = true;
			return false;
		}
		
		m_Minimized = false;
		
		// 1. Tell RendererAPI that the window has been resized
		Renderer::OnWindowResize(width, height);
		return false;
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
