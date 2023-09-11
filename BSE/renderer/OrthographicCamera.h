#ifndef BSE_ORTHOGRAPHICCAMERA_H
#define BSE_ORTHOGRAPHICCAMERA_H

#include <Core.h>
// #include <glm/glm.hpp>

namespace BSE {
	class BSE_API OrthographicCamera {
	public:
		OrthographicCamera();
		OrthographicCamera(const OrthographicCamera& camera) = default;
		OrthographicCamera(float left, float right, float top, float bottom, float znear = -1.0f, float zfar = 1.0f);
		virtual ~OrthographicCamera();
		
		virtual void SetProjection(float left, float right, float top, float bottom, float znear = -1.0f, float zfar = 1.0f);
		virtual void SetProjection(glm::mat4 projection);
		
		virtual inline void SetPosition(const glm::vec3 position) { m_Position = position; RecalculateViewMatrix(); }
		virtual inline void SetRotation(float rotation) { m_Rotation.z = rotation; RecalculateViewMatrix(); }
		virtual inline void SetRotation(const glm::vec3 rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
		
		virtual inline const glm::vec3& GetPosition() const { return m_Position; }
		virtual inline float GetRotationX() const { return m_RotationX; }
		virtual inline float GetRotationY() const { return m_RotationY; }
		virtual inline float GetRotationZ() const { return m_RotationZ; }
		virtual inline glm::vec3 GetRotation() const { return m_Rotation; }
		
		virtual inline const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		virtual inline const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		virtual inline const glm::mat4& GetViewProjectionMatrix() { BSE_CORE_INFO("BSECamera. Is this the stop point?"); return m_ViewProjectionMatrix; }
		
	private:
		virtual void RecalculateViewMatrix(); // called everytime when we set position or rotation
		
	private:
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewProjectionMatrix = glm::mat4(1.0f); // View x Projection cache
		
		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Rotation = {0.0f, 0.0f, 0.0f};
		
		float m_RotationX = 0.0f; // on X axis
		float m_RotationY = 0.0f; // on Y axis
		float m_RotationZ = 0.0f; // on Z axis
	};
}

#endif
