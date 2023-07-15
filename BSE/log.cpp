#include <log.h>

//#include "spdlog/spdlog.h"
//#include "spdlog/sinks/stdout_color_sinks.h"
//#include "spdlog/fmt/ostr.h"

//#include <vendor/spdlog/spdlog.h>
//#include <vendor/spdlog/sinks/stdout_color_sinks.h>
//#include <vendor/spdlog/fmt/ostr.h>

namespace BSE{
	
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger>	Log::s_ClientLogger;
	
	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("BSE");
		s_CoreLogger->set_level(spdlog::level::trace);
		
		s_ClientLogger = spdlog::stdout_color_mt("App");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}
