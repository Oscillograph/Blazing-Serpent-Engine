#ifndef BSE_APPLICATION_H
#define BSE_APPLICATION_H

#include <Core.h>
#include <Window.h>
#include <Input.h>
#include <KeyCodes.h>
#include <systems/events/AppEvent.h>
#include <systems/events/KeyEvent.h>
#include <systems/events/MouseEvent.h>
#include <LayerStack.h>
#include <systems/gui/ImGuiLayer.h>

#ifdef BSE_PLATFORM_WINDOWS
	#include <platforms/windows/WindowsWindow.h>
	#include <platforms/windows/WindowsInput.h>
#endif

#include <renderer/ShaderExample.h>
#include <renderer/Buffer.h>
#include <renderer/VertexArray.h>
#include <renderer/Renderer.h>

namespace BSE {
	class BSE_API Application {
	public:
		Application();
		virtual ~Application();
		
		void OnEvent(Event& e);
		
		void Run();
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		
		inline Window* GetWindow() { return m_Window; }
		inline static Application* Get() { return s_Instance; }
		inline static void Set(Application* App) { delete s_Instance; s_Instance = App; }
		inline void SetImGuiLayer(Layer* layer){ m_ImGuiLayer = layer; }
		inline Layer* GetImGuiLayer(){ return m_ImGuiLayer; }
		
	protected:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
		
		Window* m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		Layer* m_ImGuiLayer = nullptr;
		bool m_ImGuiLayerEnabled = true;
		
		static Application* s_Instance;
		
		// triangle things
		VertexArray* m_VertexArray;
		ShaderExample* m_Shader;
		
		// square things
		VertexArray* m_SquareVA;
		ShaderExample* m_BlueShader;
	};
	
	// to be defined in client app
	Application* CreateApplication();
}

#endif
