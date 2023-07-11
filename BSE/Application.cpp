#include <Application.h>

//#include "./systems/events/AppEvent.h"
//#include "./log.h"

namespace BSE{
	// DONE: Figure out how to allow this instance through static library
	// Current answer: no-how.
	// The static library has its own memory zone where it stores its objects,
	// so it's a bad idea to rely on its global variables or static pointers.
	Application* Application::s_Instance = nullptr;
	
	Application::Application(){
		s_Instance = this;
		
		BSE_CORE_ASSERT((s_Instance == nullptr), "Application already exists.");
		
		BSE_TRACE("Trying to create an app window");
		m_Window = Window::Create(*(new WindowProperties()));
		BSE_TRACE("Window created and stored in m_Window");
		
		m_Window->SetEventCallback([this](Event& event){
			OnEvent(event);
		});
		
		BSE_TRACE("OnEvent callback bind successful");
		
		m_ImGuiLayerEnabled = true;
		
		// ------------------------------------------------
		// OpenGL drawing a simple triangle
		
		// Vertex array
		m_VertexArray = VertexArray::Create();
		
		// some data to draw
		
		float vertices[3 * 7] = {
			// one vertice, three-component vector X,Y,Z clipping -1...1
			// and, also, 4 numbers for color ov vertices
			-0.5f, -0.5f,  0.0f,  0.8f, 0.2f, 0.8f, 1.0f,  
			 0.5f, -0.5f,  0.0f,  0.2f, 0.8f, 0.8f, 1.0f,
			 0.25f, 0.25f, 0.0f,  0.8f, 0.8f, 0.2f, 1.0f
		};
		
		BSE_TRACE("Vertices defined");
		
		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
		};	
			
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		BSE_TRACE("Vertex buffer layout construction successful");
		
		// Index buffer
		uint32_t indices[3] = {
			0,
			1,
			2
		};
		
		m_IndexBuffer = IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
		BSE_TRACE("Index buffer bind successful");
		
		// ------------
		// Square Vertex Array for test purposes
		// ------------
		m_SquareVA = VertexArray::Create();
		float squareVertices[3 * 4] = {
			// one vertice, three-component vector X,Y,Z clipping -1...1
			// and, also, 4 numbers for color ov vertices
			-0.5f, -0.5f,  0.0f,  
			 0.5f, -0.5f,  0.0f,
			 0.5f,  0.5f,  0.0f,
			-0.5f,  0.5f,  0.0f,
		};
		BSE_TRACE("Vertices defined");
		m_SquareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));	
		
		m_SquareVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
		});
		m_SquareVA->AddVertexBuffer(m_SquareVB);
		BSE_TRACE("Vertex buffer layout construction successful");
		
		// Index buffer
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		
		m_SquareIB = IndexBuffer::Create(squareIndices, (sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(m_SquareIB);
		BSE_TRACE("Index buffer bind successful");
		// ============
		
		// Shader
		// TODO: make shaders in a module and/or load from a text file as they are raw strings
		std::string vertexShaderSource = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec3 v_Position;
			out vec4 v_Color;
			
			void main(){
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";
		std::string fragmentShaderSource = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main(){
				// color = vec4(0.8, 0.3, 0.3, 1.0);
				color = vec4(0.5*(1 - v_Position), 1.0);
				color = v_Color;
			}
		)";

		// Square test purposes only
		std::string BlueShaderVertexShaderSource = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			
			void main(){
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";
		std::string BlueShaderFragmentShaderSource = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main(){
				// color = vec4(0.8, 0.3, 0.3, 1.0);
				color = vec4(0.2f, 0.3f, 0.7f, 1.0);
			}
		)";

		m_Shader = new ShaderExample(vertexShaderSource, fragmentShaderSource);
		m_BlueShader = new ShaderExample(BlueShaderVertexShaderSource, BlueShaderFragmentShaderSource);
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
		
		// TODO: find out why's the crash after Buffer Layers were implemented
		while(m_Running){
			// --------------------------------------------------
			// RENDER
			glClearColor(0.2f, 0.2f, 0.4f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			// OpenGL raw draw section
			m_BlueShader->Bind();
			m_SquareVA->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetSize(), GL_UNSIGNED_INT, nullptr);
			
			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetSize(), GL_UNSIGNED_INT, nullptr);
			
			//BSE_TRACE("Bind and draw vertices with corresponding index buffers");
			
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
		}
		return true;
	}
}
