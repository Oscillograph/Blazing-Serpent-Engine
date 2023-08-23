#ifndef BSE_IMGUILAYER_H
#define BSE_IMGUILAYER_H

#include <Core.h>
// #include <Application.h>
#include <Layer.h>
#include <systems/events/Event.h>
#include <systems/events/AppEvent.h>
#include <systems/events/MouseEvent.h>
#include <systems/events/KeyEvent.h>
#include <imgui/imgui.h>

// #include <vendor/imgui/imgui.h> // made it into common.h
// #include <glfw/glfw3.h>
/*
#ifndef IMGUI_IMPL_OPENGL_LOADER_CUSTOM
	#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
	#include <Glad/include/glad/glad.h>
	
	#include <vendor/imgui/backends/imgui_impl_opengl3.h>
	#include <vendor/imgui/backends/imgui_impl_glfw.h>
#endif
*/
namespace BSE {
	class BSE_API ImGuiLayer : public Layer {
	public:
		//ImGuiLayer(Application* app);
		ImGuiLayer();
		virtual ~ImGuiLayer();
		
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		// void OnUpdate() override;
		virtual void OnImGuiRender(float time) override;
		
		virtual void Begin() override;
		void ImGuiContent();
		virtual void End() override;
		
		void FixImGuiContext();
		inline ImGuiContext* GetImGuiContext(){ return m_ImGuiContext; }
		//void OnEvent(Event& event) override;
		
		// event callbacks
		//bool OnMouseButtonPressed(MouseButtonPressed& event);
		//bool OnMouseButtonReleased(MouseButtonReleased& event);
		//bool OnMouseMoved(MouseMovedEvent& event);
		//bool OnMouseScrolled(MouseScrolledEvent& event);
		//bool OnKeyPressed(KeyPressedEvent& event);
		//bool OnKeyTyped(KeyTypedEvent& event);
		//bool OnKeyReleased(KeyReleasedEvent& event);
		//bool OnWindowResized(WindowResizeEvent& event);
		
		// ImFontConfig font_config; // for cyrillic support
		ImFontConfig* font_config = nullptr; // for cyrillic support
	protected:
		ImGuiIO* m_io = nullptr;
		ImGuiContext* m_ImGuiContext = nullptr;
		
		ImGuiMemAllocFunc m_ImGuiMemAllocFunc;
		ImGuiMemFreeFunc m_ImGuiMemFreeFunc;
		void* m_ImGuiUserData = NULL;
		
		float m_Time;
		// Application* m_App;
	};
}

#endif
