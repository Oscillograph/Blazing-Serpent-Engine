#include <utils/Profiler.h>
#include <Cherno/Instrumentor.h>

namespace BSE {
	// std::vector<TimerResult> Profiler::m_ProfileResults = {};
	std::unordered_map<std::string, float> Profiler::m_ProfileResults;
	ProfilerSession* Profiler::m_CurrentSession = nullptr;
	std::string Profiler::m_Filepath = "";
	std::ofstream Profiler::m_OutputStream;
	int Profiler::m_ProfileCount = 0;
	
	void Profiler::Push(TimerResult result){
		m_ProfileResults[result.Name] = result.Time;
	}
	
	void Profiler::Flush(){
		m_ProfileResults.clear();
	}
}
