#include <Application.h>

//#include "./systems/events/AppEvent.h"
//#include "./log.h"

namespace BSE{
	// TODO: Figure out how to allow this instance through static library
	// Current answer: no-how.
	// The static library has its own memory zone where it stores its objects,
	// so it's a bad idea to rely on its global variables or static pointers.
	Application* Application::s_Instance = nullptr;
	
	Application::Application(){
		// This experiment has shown that the adresses with a DLL are the same, 
		// but also different if with a static .a-library
		
		// BSE_CORE_TRACE("Core Singleton address: {0}", (void*)&s_Instance);
		s_Instance = this;
		// BSE_TRACE("Singleton address: {0}", (void*)&s_Instance);
		
		BSE_CORE_ASSERT((s_Instance == nullptr), "Application already exists.");
		
		//BSE_CORE_ASSERT((s_Instance == nullptr), "Application already exists.");
		
		BSE_TRACE("Trying to create an app window");
		m_Window = Window::Create(*(new WindowProperties()));
		BSE_TRACE("Window created and stored in m_Window");
		
		m_Window->SetEventCallback([this](Event& event){
			OnEvent(event);
		});
		
		// test purposes
		// unsigned int id;
		// glGenVertexArrays(1, &id);
		
		BSE_TRACE("OnEvent callback bind successful");
		
		m_ImGuiLayerEnabled = true;
		
		// ------------------------------------------------
		// OpenGL drawing a simple triangle
		
		// Vertex array
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
		BSE_TRACE("Vertex array generated and bound");
		
		// some data to draw
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f, // one vercie, three-component vector X,Y,Z clipping -1...1
			0.5f, -0.5f, 0.0f,
			0.25f, 0.25f, 0.0f
		};
		BSE_TRACE("Vertices defined");
		
		// The app crashed here when i used glCreateBuffers (OpenGL 4.5+) instead of glGenBuffers (can work on my videocard)
		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		// m_VertexBuffer->Bind();
		BSE_TRACE("Vertex buffer bind successful");

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);
		
		// Index buffer
		uint32_t indices[3] = {
			0,
			1,
			2
		};
		
		m_IndexBuffer = IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t)));
		// m_IndexBuffer->Bind();
		BSE_TRACE("Index buffer bind successful");
		
		// Shader
		// to be done next lesson
		std::string vertexShaderSource = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main(){
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";
		std::string fragmentShaderSource = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main(){
				// color = vec4(0.8, 0.3, 0.3, 1.0);
				color = vec4(0.5*(1 - v_Position), 1.0);
			}
		)";

		m_Shader = new ShaderExample(vertexShaderSource, fragmentShaderSource);
	}
	
	Application::~Application(){
		if (m_ImGuiLayerEnabled && (m_ImGuiLayer != nullptr)){
			PopOverlay(m_ImGuiLayer);
			delete m_ImGuiLayer;
			m_ImGuiLayer = nullptr;
		}
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
			// --------------------------------------------------
			// RENDER
			glClearColor(0.2f, 0.2f, 0.4f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			// OpenGL raw draw section
			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetSize(), GL_UNSIGNED_INT, nullptr);
			
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
		}
		return true;
	}
}
