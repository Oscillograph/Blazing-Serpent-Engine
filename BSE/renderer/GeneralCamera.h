#ifndef BSE_GENERALCAMERA_H
#define BSE_GENERALCAMERA_H

#include <Core.h>

namespace BSE {
	class BSE_API GeneralCamera {
	public:
		GeneralCamera();
		GeneralCamera(const glm::mat4& projection);
		GeneralCamera(float left, float right, float top, float bottom, float znear = -1.0f, float zfar = 1.0f);
		~GeneralCamera();
		
		inline void SetProjection(float left, float right, float top, float bottom){
			m_ProjectionMatrix = glm::ortho(left, right, bottom, top);
			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}
		
		inline void SetPosition(const glm::vec3 position) { m_Position = position; RecalculateViewMatrix(); }
		inline void SetRotation(float rotation) { m_Rotation.z = rotation; RecalculateViewMatrix(); }
		inline void SetRotation(const glm::vec3 rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
		
		inline const glm::vec3 GetPosition() const { return m_Position; }
		inline float GetRotationX() const { return m_RotationX; }
		inline float GetRotationY() const { return m_RotationY; }
		inline float GetRotationZ() const { return m_RotationZ; }
		inline glm::vec3 GetRotation() const { return m_Rotation; }
		
		inline const glm::mat4 GetProjectionMatrix() { return m_ProjectionMatrix; }
		inline const glm::mat4 GetViewMatrix() { return m_ViewMatrix; }
		inline const glm::mat4 GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }
	private:
		// called everytime when we set position or rotation
		void RecalculateViewMatrix();
		
		glm::mat4 m_ProjectionMatrix = OneMat4;
		glm::mat4 m_ViewMatrix = OneMat4;
		glm::mat4 m_ViewProjectionMatrix = OneMat4; // View x Projection cache
		
		glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
		glm::vec3 m_Rotation = {0.0f, 0.0f, 0.0f};
		
		float m_RotationX = 0.0f; // on X axis
		float m_RotationY = 0.0f; // on Y axis
		float m_RotationZ = 0.0f; // on Z axis
	};
}

#endif
