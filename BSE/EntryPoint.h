#ifndef BSE_ENTRYPOINT_H
#define BSE_ENTRYPOINT_H

#ifdef BSE_PLATFORM_WINDOWS

#include <Core.h>
// #include <ProtoCore.h>
// #include <log.h>
// #include <BSE_Client.h>

extern BSE::Application* BSE::CreateApplication(); 

int main(int argc, char** args) {
	BSE_PROFILE_SESSION_START("Startup", "./debug/startup.json");
	BSE::Log::Init();
	BSE_CORE_WARN("Log System Initialized!");
	BSE_INFO("Log System Initialized!");
	auto app = BSE::CreateApplication();
	BSE_PROFILE_SESSION_END();
	
	BSE_PROFILE_SESSION_START("Runtime", "./debug/runtime.json");
	app->Run();
	BSE_PROFILE_SESSION_END();
	
	BSE_PROFILE_SESSION_START("Shutdown", "./debug/shutdown.json");
	delete app;
	BSE::Profiler::Flush();
	BSE_PROFILE_SESSION_END();
	return 0;
}

#else
	#error BSE currently only supports Windows.
#endif

#endif
