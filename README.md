# ! WORK IN PROGRESS ! #
The goal is to make the 2D game engine while "Game Engine Series" by The Cherno is being watched.
As the first third of the series passed I realized that my vision of what I would like to get is quite different from what the author did choose, but the way Cherno explains things and demonstrates really intrigues me and motivates to replicate and rethink the experience shared by the author of Hazel.
# BLAZING SERPENT ENGINE #
A C++ game engine based on "Game Engine Series" by The Cherno.

The engine is designed to be used as a DLL, but the consequences are:
- Dear ImGui requires a client app to reset the context at the start of OnImGuiRender method of the client ImGuiLayer:
```
if (m_Context != nullptr){
	if (m_Context != ImGui::GetCurrentContext()){
		BSE_TRACE("SandboxGui: Current Context is different!"); 
		ImGui::SetCurrentContext(m_Context);
		BSE_TRACE("SandboxGui: Current Context is set again!");
	}
}
```
- Layers and ImGuiLayers don't share data between them, and Layer can't utilize OnImGuiRenderer method of its own as it crashes the app with 0x000000c5 error;
- Due to the above there's a dire need of Asset Manager and Game Data Manager to provide API through which Layers, client App and the DLL could communicate.

## Build notes ##
### DLL ###
The DLL is built using TDM-GCC via Red Panda C++ IDE.
C++ Custom Compiler options:
```
-D BSE_PLATFORM_WINDOWS -D BSE_DLL -D BSE_BUILD_DLL -D SPDLOG_COMPILED_LIB -D YAML_CPP_STATIC_DEFINE -D USE_IMGUI_API
```
Linker options:
```
-lopengl32_@@_libglfw3dll.a_@@_libGlad.a_@@_libDear_ImGui.a_@@_libspdlog.a_@@_libYaml_cpp.a
```
(Obviously, there should be compiled static libraries for glfw3, Glad, Dear ImGui, spdlog)

Includes directories should contain:
- Blazing Serpent Engine
- Blazing Serpent Engine/BSE
- Blazing Serpent Engine/BSE/vendor
- Blazing Serpent Engine/BSE/vendor/imgui
- Blazing Serpent Engine/BSE/vendor/imgui/backends
- Blazing Serpent Engine/BSE/vendor/yaml_cpp/include
- Blazing Serpent Engine/BSE/vendor/Cherno/ImGuizmo

A precompiled header can dramatically reduce compile time:
Blazing Serpent Engine/BSE/common.h

### Client app ###
The client app is built almost the same way as the DLL except that Compiler options are:
```
-D BSE_PLATFORM_WINDOWS -D BSE_DLL -D BSE_ENABLE_ASSERTS -D SPDLOG_COMPILED_LIB -D YAML_CPP_STATIC_DEFINE -D USE_IMGUI_API
```
Linker options:
```
libBlazing_Serpent_Engine.a_@@_libspdlog.a_@@_libDear_ImGui.a_@@_libglfw3dll.a_@@_libGlad.a_@@_libYaml_cpp.a
```
And Libraries directories should contain the folder where libBlazingSerpentEngine.a and libBlazingSerpentEngine.dll are.

## Tech Stack ##
+ **C++17** (almost everything)
+ **spdlog** (logging library)
+ **GLM** (math library)
+ **OpenGL 3.3-4.1 (GLFW, GLAD)** (windowing and rendering)
+ **GLSL** (shaders in text files)
+ **Dear ImGui** (OpenGL GUI library)
+ **stb_image** (image loading)
+ **EnTT** (ECS support)
+ **YaML** (objects serialization and deserialization)
