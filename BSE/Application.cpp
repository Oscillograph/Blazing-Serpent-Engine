#include <Application.h>

//#include "./systems/events/AppEvent.h"
//#include "./log.h"

namespace BSE{
	// DONE: Figure out how to allow this instance through static library
	// Current answer: no-how.
	// The static library has its own memory zone where it stores its objects,
	// so it's a bad idea to rely on its global variables or static pointers.
	Application* Application::s_Instance = nullptr;
	
	static const GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::Float: 	return GL_FLOAT; break;
			case ShaderDataType::Float2: 	return GL_FLOAT; break;
			case ShaderDataType::Float3: 	return GL_FLOAT; break;
			case ShaderDataType::Float4: 	return GL_FLOAT; break;
			case ShaderDataType::Int: 		return GL_INT; break;
			case ShaderDataType::Int2: 		return GL_INT; break;
			case ShaderDataType::Int3: 		return GL_INT; break;
			case ShaderDataType::Int4: 		return GL_INT; break;
			case ShaderDataType::Mat3: 		return GL_FLOAT_MAT3; break;
			case ShaderDataType::Mat4: 		return GL_FLOAT_MAT4; break;
			case ShaderDataType::Bool: 		return GL_BOOL; break;
		}
		BSE_CORE_ASSERT(false, "Unknown ShaderDataType");
		return GL_NONE;
	}
	
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
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
		BSE_TRACE("Vertex array generated and bound");
		
		// some data to draw
		
		float vertices[3 * 7] = {
			// one vertice, three-component vector X,Y,Z clipping -1...1
			// and, also, 4 numbers for color ov vertices
			-0.5f, -0.5f,  0.0f,  0.8f, 0.2f, 0.8f, 1.0f,  
			 0.5f, -0.5f,  0.0f,  0.2f, 0.8f, 0.8f, 1.0f,
			 0.25f, 0.25f, 0.0f,  0.8f, 0.8f, 0.2f, 1.0f
		};
		
		/*
		float vertices[3 * 3] = {
			// one vertice, three-component vector X,Y,Z clipping -1...1
			// and, also, 4 numbers for color ov vertices
			-0.5f, -0.5f,  0.0f,  
			0.5f, -0.5f,  0.0f,
			0.25f, 0.25f, 0.0f,
		};
		*/
		BSE_TRACE("Vertices defined");
		
		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		
		{ // just a scope to make layout destroyed after it's set in m_VertexBuffer
			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"}
			};
			
			m_VertexBuffer->SetLayout(layout);
		}
		
		
		uint32_t index = 0;
		auto layout = m_VertexBuffer->GetLayout();
		for (auto element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
				element.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(element.Type), 
				element.Normalized ? GL_TRUE : GL_FALSE, 
				layout.GetStride(), 
				(const void*)element.Offset);
			
			BSE_TRACE("{1} - Element component count: {0}", element.GetComponentCount(), index);
			BSE_TRACE("{1} - Element normalized: {0}", element.Normalized ? GL_TRUE : GL_FALSE, index);
			BSE_TRACE("{1} - Element offset: {0}", element.Offset, index);
			BSE_TRACE("{1} - Layout m_Stride: {0}", layout.GetStride(), index);
			index++;
		}
		/*
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 
			3, 
			GL_FLOAT, 
			GL_FALSE, 
			3*sizeof(float), 
			nullptr);
		*/
		BSE_TRACE("Vertex buffer layout construction successful");
		
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
		
		// TODO: find out why's the crash after Buffer Layers were implemented
		while(m_Running){
			// --------------------------------------------------
			// RENDER
			glClearColor(0.2f, 0.2f, 0.4f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			//BSE_TRACE("Refresh screen");
			
			// OpenGL raw draw section
			m_Shader->Bind();
			
			//BSE_TRACE("Bind Shaders");
			
			glBindVertexArray(m_VertexArray);
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
		}
		return true;
	}
}
