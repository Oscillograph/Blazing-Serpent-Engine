#ifndef BSE_LOG_H
#define BSE_LOG_H

#include <ProtoCore.h>

// #include <memory> // already in common.h included in Core.h
//#include <spdlog/spdlog.h>
// #include "./vendor/spdlog/spdlog.h"

//#include "spdlog/spdlog.h"
//#include "spdlog/sinks/stdout_color_sinks.h"
//#include "spdlog/fmt/ostr.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>

namespace BSE{
	class BSE_API Log {
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger(){
			return s_CoreLogger;
		};
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger(){
			return s_ClientLogger;
		};
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// BSE core log macros
#define BSE_CORE_TRACE(...)		::BSE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BSE_CORE_INFO(...)		::BSE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BSE_CORE_WARN(...)		::BSE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BSE_CORE_ERROR(...)		::BSE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BSE_CORE_CRITICAL(...)	::BSE::Log::GetCoreLogger()->critical(__VA_ARGS__)

// App log macros
#define BSE_TRACE(...)		::BSE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BSE_INFO(...)		::BSE::Log::GetClientLogger()->info(__VA_ARGS__)
#define BSE_WARN(...)		::BSE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BSE_ERROR(...)		::BSE::Log::GetClientLogger()->error(__VA_ARGS__)
#define BSE_CRITICAL(...)	::BSE::Log::GetClientLogger()->critical(__VA_ARGS__)

#endif
