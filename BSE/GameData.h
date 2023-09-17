#ifndef BSE_GAMEDATA_H
#define BSE_GAMEDATA_H

// =================================================================================================
// GameData is a global static class to provide API for BSE and Client App systems to 
// communicate with each other despite architecture restrictions.
// It is a sort of a backdoor for circumstances where "You can't, but you you can if you want".
//
// To be able to store any object this class should be defined after everything else.
// Sadly, it can't store Application stuff, but that is to be defined in a client descendant anyway.
// =================================================================================================

#include <Core.h>

#include <Window.h>
// #include <Input.h>
// #include <KeyCodes.h>
// #include <systems/events/AppEvent.h>
// #include <systems/events/KeyEvent.h>
// #include <systems/events/MouseEvent.h>
#include <LayerStack.h>
#include <systems/gui/ImGuiLayer.h>

#ifdef BSE_PLATFORM_WINDOWS
//	#include <platforms/windows/WindowsWindow.h>
//	#include <platforms/windows/WindowsInput.h>
#endif

#include <renderer/FrameBuffer.h>
// #include <renderer/Shader.h>
// #include <renderer/Buffer.h>
// #include <renderer/VertexArray.h>
// #include <renderer/Texture.h>
// #include <systems/Texture2DSpriteSheet.h>

// #include <renderer/Renderer.h>
// #include <renderer/Renderer2D.h>
#include <renderer/OrthographicCamera.h>
#include <systems/GeneralCameraController.h>
#include <renderer/GeneralCamera.h>
#include <systems/CameraController.h>

namespace BSE {
	class BSE_API GameData {
	public:
		// these should be copied from Application
		static Window* m_Window;
		static LayerStack* m_LayerStack;
		static Layer* m_ImGuiLayer;
		static FrameBuffer* m_FrameBuffer;
		static bool m_ImGuiLayerEnabled;
		static float FPS_deltaTime;
		static glm::vec4 RendererClearColor;
		static glm::vec4 CustomColor;
		static GeneralCameraController* m_GeneralCameraController;
		static CameraController* m_CameraController;
		static bool EditorCameraOn;
	};
}

#endif
