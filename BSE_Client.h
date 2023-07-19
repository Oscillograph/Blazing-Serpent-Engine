#ifndef BSE_CLIENT_H
#define BSE_CLIENT_H

// important BSE libraries
//#include <ProtoCore.h>
//#include <log.h>
#include <Core.h>
#include <Application.h>

// BSE systems
// - events system
#include <systems/events/Event.h>
#include <systems/events/AppEvent.h>
#include <systems/events/KeyEvent.h>
#include <systems/events/MouseEvent.h>

// - layers
// #include "Layer.h" // already in LayerStack.h included in Application.h

// - log system
// #include "log.h" // already in Core.h

// - Input system
// #include "Input.h" // already in Application.h

// - Gui
// #include <systems/gui/ImGuiLayer.h> // already in Application.h

// - Renderer
#include <renderer/Renderer.h>
#include <renderer/RendererAPI.h>
#include <renderer/RenderCommand.h>

#include <renderer/Buffer.h>
#include <renderer/Shader.h>

#include <renderer/VertexArray.h>
#include <renderer/Texture.h>
#include <renderer/OrthographicCamera.h>

#include <renderer/Material.h>

// entry point
#include <EntryPoint.h>

// - utils
// #include <utils/FileIO.h> // already in Core.h

#endif
