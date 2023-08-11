#include <GameData.h>

namespace BSE {
	// these should be copied from Application
	Window* GameData::m_Window = nullptr;
	LayerStack* GameData::m_LayerStack = nullptr;
	Layer* GameData::m_ImGuiLayer = nullptr;
	FrameBuffer* GameData::m_FrameBuffer = nullptr;
	bool GameData::m_ImGuiLayerEnabled = true;
}
