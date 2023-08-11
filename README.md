# ! WORK IN PROGRESS ! #

# BLAZING SERPENT ENGINE #
A C++ game engine based on "Game Engine Series" by The Cherno.

The engine is designed to be used as a DLL, but the consequences are:
- Dear ImGui requires a client app to reset the context:
```
#define FixImGuiContext(m_Context) \
	if (m_Context != nullptr){									\
		if (m_Context != ImGui::GetCurrentContext()){ 			\
			BSE_TRACE("SandboxGui: Current Context is different!"); \
			ImGui::SetCurrentContext(m_Context);				\
			BSE_TRACE("SandboxGui: Current Context is set again!"); \
		} \
	}
```
- Layers and ImGuiLayers don't share data between them, and Layer can't utilize OnImGuiRenderer method as it crashes the app with 0x000000c5 error;
- Due to the above there's a dire need of Asset Manager and Game Data Manager to provide API through which Layers, client App and the DLL could communicate.

## Build notes ##
### DLL ###
The DLL is built using TDM-GCC via Red Panda C++ IDE.
C++ Custom Compiler options:
```
-D BSE_PLATFORM_WINDOWS -D BSE_DLL -D BSE_BUILD_DLL -D SPDLOG_COMPILED_LIB
```
Linker options:
```
-lopengl32_@@_libglfw3dll.a_@@_libGlad.a_@@_libDear_ImGui.a_@@_libspdlog.a
```
(Obviously, there should be compiled static libraries for glfw3, Glad, Dear ImGui, spdlog)

Includes directories should contain:
- Blazing Serpent Engine
- Blazing Serpent Engine/BSE
- Blazing Serpent Engine/BSE/vendor
- Blazing Serpent Engine/BSE/vendor/imgui
- Blazing Serpent Engine/BSE/vendor/imgui/backends

A precompiled header can dramatically reduce compile time:
Blazing Serpent Engine/BSE/common.h

### Client app ###
The client app is built almost the same way as the DLL except that Compiler options are:
```
-D BSE_PLATFORM_WINDOWS -D BSE_DLL -D BSE_ENABLE_ASSERTS -D SPDLOG_COMPILED_LIB
```
Linker options:
```
libBlazing_Serpent_Engine.a_@@_libspdlog.a_@@_libDear_ImGui.a_@@_libglfw3dll.a_@@_libGlad.a
```
And Libraries directories should contain the folder where libBlazingSerpentEngine.a and libBlazingSerpentEngine.dll are.