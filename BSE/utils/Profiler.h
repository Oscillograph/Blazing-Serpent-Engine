#ifndef BSE_PROFILER_H
#define BSE_PROFILER_H

#include <utils/Time.h>

// #define BSE_CORE_PROFILER(name)	Timer timer##__LINE__(name, [&](TimerResult result){ Profiler::Push(result); });
// #define BSE_PROFILER(name)	BSE::Timer timer##__LINE__(name, [&](BSE::TimerResult result){ BSE::Profiler::Push(result); });
#define BSE_CORE_PROFILER(name)	Timer timer##__LINE__(name, [&](BSE::TimerResult result){ BSE::Profiler::Push(result); });
#define BSE_PROFILER(name)	Timer timer##__LINE__(name, [&](BSE::TimerResult result){ BSE::Profiler::Push(result); });
//#define BSE_PROFILER(name)	Timer timer##__LINE__(name, [&](TimerResult result){ Profiler::Push(result); });


namespace BSE {
	// Usage example:
	// SOMEWHERE:
	//	BSE_PROFILER(u8"my_operation::step");
	//
	// SOMEWHERE-IN-GUI-MANAGEMENT:
	// 	auto profileResults = Profiler::Read();
	// 	for (auto kv : profileResults){
	//		std::string name = kv.first;
	// 		float time = kv.second;
	//		MY_SHOW_RESULTS_FUNCTION(name, time);
	// 	}
	
	class BSE_API Profiler {
	public:
		static void Push(TimerResult result);
		inline static std::unordered_map<std::string, float> Read(){
			return m_ProfileResults;
		}
		static void Flush();
	private:
		static std::unordered_map<std::string, float> m_ProfileResults;
		// std::unordered_map<std::string, float> m_ProfileResults;
		// std::vector<TimerResult> m_ProfileResults;
	}; 
	
}
#endif
