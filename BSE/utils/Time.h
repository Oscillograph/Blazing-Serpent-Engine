#ifndef BSE_TIME_H
#define BSE_TIME_H

#include <Core.h>

namespace BSE {
	class BSE_API Timestep {
	public:
		Timestep(float time = 0.0f){
			m_Time = time;
		}
		
		operator float() const { return m_Time; }
		
		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time = 0.0f; // time in seconds
	};
	
	/*
	class SystemTimer {
	public:
		inline static std::chrono::duration<float> GetTimeStep() {
			m_Now = std::chrono::system_clock::now();
			m_Result = m_Now - m_Last;
			m_Last = m_Now;
			return m_Result.count();
		};
		
	private:
		std::chrono::time_point m_Last;
		std::chrono::time_point m_Now;
		std::chrono::duration<float> m_Result;
	};
	*/
}

#endif
