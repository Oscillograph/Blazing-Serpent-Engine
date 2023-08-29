#ifndef BSE_CLIENT_H
#define BSE_CLIENT_H

// important BSE libraries
//#include <ProtoCore.h>
//#include <log.h>
#include <Core.h>
#include <Application.h>
#include <KeyCodes.h>

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
#include <renderer/Renderer2D.h>
#include <renderer/RendererAPI.h>
#include <renderer/RenderCommand.h>

#include <renderer/Buffer.h>
#include <renderer/Shader.h>
#include <renderer/FrameBuffer.h>

#include <renderer/VertexArray.h>
#include <renderer/Texture.h>
#include <systems/Texture2DSpriteSheet.h>

#include <renderer/OrthographicCamera.h>
#include <systems/OrthographicCameraController.h>

#include <renderer/GeometryPrimitives.h>

#include <renderer/Material.h>

// entry point
// #include <EntryPoint.h> // need to be included in Client main file

#include <systems/scene/Scene.h>
#include <systems/scene/SceneSerializer.h>
#include <systems/ecs/Entity.h>
#include <systems/ecs/Components.h>

// - utils
// #include <utils/FileIO.h> // already in Core.h
#include <utils/Profiler.h>

#include <GameData.h> // must be included last

#endif
