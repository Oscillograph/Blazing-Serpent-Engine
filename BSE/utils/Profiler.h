#ifndef BSE_PROFILER_H
#define BSE_PROFILER_H

#include <utils/Time.h>
#include <thread>

// Most of this Profiler's code has been taken from Instrumentor.h file from:
// https://gist.github.com/TheCherno/31f135eea6ee729ab5f26a6908eb3a5e/raw/55619bb8dd4349895f7d5f2520cc35a0e6d38c09/Instrumentor.h
//
// High-level usage: include this header file somewhere in your code (eg. precompiled header), and then use like:
//
// Profiler::BeginSession("Session Name", "filepath");        // Begin session 
// {
//     ProfilerTimer timer("Profiled Scope Name");   // Place code like this in scopes you'd like to include in profiling
//     // Code
// }
// Profiler::EndSession();                        // End Session
//
// You will probably want to macro-fy this, to switch on/off easily and use things like __FUNCSIG__ for the profile name.

// profiling to files in json format
#define BSE_PROFILER_SESSION_START(name, filepath) 	Profiler::BeginSession(name, filepath); {
#define BSE_PROFILER_SCOPE(name)						ProfilerTimer timer##__LINE__(name);
#define BSE_PROFILER_SESSION_END() 					} Profiler::EndSession();

// a simpler version: moment profiling
#define BSE_CORE_PROFILER(name)	Timer timer##__LINE__(name, [&](BSE::TimerResult result){ BSE::Profiler::Push(result); });
#define BSE_PROFILER(name)	Timer timer##__LINE__(name, [&](BSE::TimerResult result){ BSE::Profiler::Push(result); });

namespace BSE {
	struct ProfileResult {
		std::string Name;
		long long Start; 
		long long End;
		uint32_t ThreadID;
	};
	
	struct ProfilerSession {
		std::string Name;
	};
	
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
		inline static ProfilerSession* GetSession(){ 
			return m_CurrentSession; 
		}
		inline static void BeginSession(std::string name, std::string filepath = "./debug/runtime.json"){ 
			if (!m_OutputStream.is_open()){
				m_OutputStream.open(filepath);
				m_Filepath = filepath;
			} else {
				BSE_CORE_ERROR("Profiler: file {0} is open!", filepath);
			}
			WriteHeader();
			m_CurrentSession = new ProfilerSession{name};
		}
		
		inline static void EndSession() {
			WriteFooter();
			if (m_OutputStream.is_open()){
				m_OutputStream.close();
			} else {
				BSE_CORE_ERROR("Profiler: file {0} is closed!", m_Filepath);
			}
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
			m_ProfileCount = 0;
		}
		
		inline static void WriteHeader(){
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
			m_OutputStream.flush();
		}
		
		inline static void WriteProfile(const ProfileResult& result)
		{
			if (m_ProfileCount++ > 0)
				m_OutputStream << ",";
			
			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');
			
			m_OutputStream << "{";
			m_OutputStream << "\"cat\":\"function\",";
			m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
			m_OutputStream << "\"name\":\"" << name << "\",";
			m_OutputStream << "\"ph\":\"X\",";
			m_OutputStream << "\"pid\":0,";
			m_OutputStream << "\"tid\":" << result.ThreadID << ",";
			m_OutputStream << "\"ts\":" << result.Start;
			m_OutputStream << "}";
			
			m_OutputStream.flush();
		}
		
		inline static void WriteFooter() {
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}
		
	private:
		static std::unordered_map<std::string, float> m_ProfileResults;
		// std::unordered_map<std::string, float> m_ProfileResults;
		// std::vector<TimerResult> m_ProfileResults;
		static ProfilerSession* m_CurrentSession;
		static std::string m_Filepath;
		static std::ofstream m_OutputStream;
		static int m_ProfileCount;
	}; 
	
	// Special Profiler's version of timer
	class BSE_API ProfilerTimer {
	public:
		ProfilerTimer(std::string name)
		: m_Name(name), m_Stopped(false)
		{
			m_StartTimePoint = std::chrono::high_resolution_clock::now();
		}
		
		~ProfilerTimer(){
			if (!m_Stopped){
				Stop();
			}
		}
		
		void Stop(){
			auto endTimePoint = std::chrono::high_resolution_clock::now();
			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
			m_Stopped = true;
			
			float duration = (end - start) * 0.001f;
			
			// BSE_CORE_INFO("{1} operation took: {0} ms", duration, m_Name);
			// return new TimerResult(m_Name, duration);
			
			uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Profiler::WriteProfile({ m_Name, start, end, threadID });
		}
		
	private:
		std::string m_Name;
		std::chrono::high_resolution_clock::time_point m_StartTimePoint;
		bool m_Stopped;
	};
}
#endif
