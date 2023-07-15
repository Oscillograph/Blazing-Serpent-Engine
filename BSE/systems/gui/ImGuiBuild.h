#ifndef BSE_IMGUIBUILD_H
#define BSE_IMGUIBUILD_H

#include <Core.h>

#ifndef IMGUI_IMPL_OPENGL_LOADER_CUSTOM
	#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include <Glad/include/glad/glad.h>
	
//#include <vendor/imgui/backends/imgui_impl_opengl3.h>
//#include <vendor/imgui/backends/imgui_impl_glfw.h>

#include <imgui/backends/imgui_impl_opengl3.cpp>
#include <imgui/backends/imgui_impl_glfw.cpp>
//#endif

#endif
