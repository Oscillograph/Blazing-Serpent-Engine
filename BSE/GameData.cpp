#include <GameData.h>

namespace BSE {
	// these should be copied from Application
	Window* GameData::m_Window = nullptr;
	LayerStack* GameData::m_LayerStack = nullptr;
	Layer* GameData::m_ImGuiLayer = nullptr;
	FrameBuffer* GameData::m_FrameBuffer = nullptr;
	bool GameData::m_ImGuiLayerEnabled = true;
	float GameData::FPS_deltaTime = BSE_FPS60;
	glm::vec4 GameData::RendererClearColor = {0.2f, 0.2f, 0.4f, 1.0f};
	glm::vec4 GameData::CustomColor = {0.2f, 0.7f, 0.3f, 1.0f};
	GeneralCameraController* GameData::m_CameraController = nullptr;
	bool GameData::EditorCameraOn = false;
}
