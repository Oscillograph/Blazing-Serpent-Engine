#ifndef BSE_ENTRYPOINT_H
#define BSE_ENTRYPOINT_H

#ifdef BSE_PLATFORM_WINDOWS

#include <Core.h>
// #include <ProtoCore.h>
// #include <log.h>
// #include <BSE_Client.h>

extern BSE::Application* BSE::CreateApplication(); 

int main(int argc, char** args) {
	BSE::print_hello();

	BSE::Log::Init();
	BSE_CORE_WARN("Log System Initialized!");
	BSE_INFO("Log System Initialized!");
	
	// BSE::Application* BSE::Application::s_Instance = nullptr;
	
	auto app = BSE::CreateApplication();
	// BSE::Application::Set(app);
	app->Run();
	delete app;
	BSE::Profiler::Flush();
	return 0;
}

#else
	#error BSE currently only supports Windows.
#endif

#endif
