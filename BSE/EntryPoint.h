#ifndef BSE_ENTRYPOINT_H
#define BSE_ENTRYPOINT_H

#ifdef BSE_PLATFORM_WINDOWS

extern BSE::Application* BSE::CreateApplication(); 

int main(int argc, char** args) {
	BSE::print_hello();
	
	BSE::Log::Init();
	BSE_CORE_WARN("Log System Initialized!");
	BSE_INFO("Log System Initialized!");
	
	auto app = BSE::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#else
	#error BSE currently only supports Windows.
#endif

#endif
