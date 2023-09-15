#ifndef BSE_GENERALCAMERA_H
#define BSE_GENERALCAMERA_H

#include <Core.h>

namespace BSE {
	class BSE_API GeneralCamera {
	public:
		// orthographic projection constructors
		GeneralCamera();
		GeneralCamera(float left, float right, float top, float bottom, float znear, float zfar);
		
		// perspective projection constructors
		GeneralCamera(float fov, float aspectRatio, float nearClip, float farClip);
		GeneralCamera(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up);
		
		// custom projection constructor
		GeneralCamera(const glm::mat4& projection);
		
		virtual ~GeneralCamera();
		
		// set projection matrix
		virtual inline void SetProjection(float left, float right, float top, float bottom){
			m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f); 
			RecalculateViewMatrix(); 
		}
		virtual inline void SetProjection(const glm::mat4& projection) { 
			m_ProjectionMatrix = projection; 
			RecalculateViewMatrix(); 
		}
		
		// set view matrix relative data
		virtual inline void SetPosition(const glm::vec3 position) { m_Position = position; }
		virtual inline const glm::vec3 GetPosition() const { return m_Position; }
		
		virtual inline void SetTarget(const glm::vec3 target) { m_Target = target; }
		virtual inline const glm::vec3 GetTarget() const { return m_Target; }
		
		virtual inline void SetRotation(const glm::vec3 rotation) { m_Rotation = rotation; }
		virtual inline glm::vec3 GetRotation() const { return m_Rotation; }

		virtual inline void SetPitch(float pitch) { m_Rotation.x = pitch; }
		virtual inline float GetPitch() { return m_Rotation.x; }
		
		virtual inline void SetYaw(float yaw) { m_Rotation.y = yaw; }
		virtual inline float GetYaw() { return m_Rotation.y; }
		
		virtual inline void SetRoll(float roll) { m_Rotation.z = roll; }
		virtual inline float GetRoll() { return m_Rotation.z; }
		
		inline void SetDistance(float d){ distance = d; }
		inline float GetDistance() { return distance; }
		
		// camera interface
		virtual inline const glm::mat4 GetProjectionMatrix() { return m_ProjectionMatrix; }
		virtual inline const glm::mat4 GetViewMatrix() { return m_ViewMatrix; }
		virtual inline const glm::mat4 GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }
		
		virtual void Update();
		
		// public data
		float fov = 0.0f; // in degrees
		float aspectRatio = 0.0f;
		float nearClip = 0.1f;
		float farClip = 1000.0f;
		float distance = 3.0f;
		bool perspective = false;
		
	private:
		virtual void RecalculateViewMatrix();
		
		glm::mat4 m_ProjectionMatrix = OneMat4;
		glm::mat4 m_ViewMatrix = OneMat4;
		glm::mat4 m_ViewProjectionMatrix = OneMat4; // View x Projection cache
		
		glm::vec3 m_Position = {0.0f, 0.0f, 3.0f};
		glm::vec3 m_Target = {0.0f, 0.0f, 0.0f};
		glm::vec3 m_Rotation = {0.0f, 0.0f, 0.0f}; // in degrees
		glm::vec3 m_Up = = {0.0f, 1.0f, 0.0f};
	};
}

#endif
