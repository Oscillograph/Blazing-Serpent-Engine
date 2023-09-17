#ifndef BSE_GENERALCAMERA_H
#define BSE_GENERALCAMERA_H

#include <Core.h>

namespace BSE {
	struct BSE_API CameraControllerData {
		// general controller settings
		bool allowTranslation = true;
		bool allowRotation = true;
		bool allowZoom = true;
		bool constantAspectRatio = false;
		bool editorCamera = false; // is it set to be a special app camera (as in an editor)
		
		// general controller settings
		float m_CameraRotationSpeed = 10.0f;
		float m_CameraMovementSpeed = 5.0f;
		
		// general camera settings
		float m_ViewportWidth = 0.0f;
		float m_ViewportHeight = 0.0f;
		float m_ZoomLevel = 0.0f; // is equivalent to size of orthographic projection, and is the equivalent of the distance between camera and the target
	};
	
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
		virtual inline void SetProjection(float left, float right, float top, float bottom, float znear, float zfar){
			m_ProjectionMatrix = glm::ortho(left, right, bottom, top, znear, zfar); 
			RecalculateViewMatrix();
		}
		
		virtual inline void SetProjection(float left, float right, float top, float bottom){
			m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f); 
			RecalculateViewMatrix(); 
		}
		virtual inline void SetProjection(const glm::mat4& projection) { 
			m_ProjectionMatrix = projection; 
			RecalculateViewMatrix(); 
		}
		
		// set view matrix relative data
		virtual inline void SetPosition(const glm::vec3& position) { m_Position = position; }
		virtual inline void Move(const glm::vec3& translation) {
			if (m_Rotated){
				if ((m_Rotation.x == 90) || (m_Rotation.x == -90)) {
					m_PositionFactor.x = 0;
				} else {
					m_PositionFactor.x = 1/cosf(glm::radians(m_Rotation.x));
				}
				
				if ((m_Rotation.y == 90) || (m_Rotation.y == -90)) {
					m_PositionFactor.y = 0;
				} else {
					m_PositionFactor.y = 1/cosf(glm::radians(m_Rotation.y));
				}
				
				if ((m_Rotation.z == 90) || (m_Rotation.z == -90)) {
					m_PositionFactor.z = 0;
				} else {
					m_PositionFactor.z = 1/cosf(glm::radians(m_Rotation.z));
				}
				
				m_Rotated = false;
			}
			
			m_Position.x += translation.x * cosf(glm::radians(m_Rotation.y)) * sinf(glm::radians(m_Rotation.z));
			m_Position.y += translation.y * cosf(glm::radians(m_Rotation.z)) * sinf(glm::radians(m_Rotation.x));
			m_Position.z += translation.z * cosf(glm::radians(m_Rotation.x)) * sinf(glm::radians(m_Rotation.y));
		}
		virtual inline const glm::vec3 GetPosition() const { return m_Position; }
		
		virtual inline void SetTarget(const glm::vec3& target) { m_Target = target; }
		virtual inline const glm::vec3 GetTarget() const { return m_Target; }
		
		virtual inline void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; m_Rotated = true; }
		virtual inline glm::vec3 GetRotation() const { return m_Rotation; }

		virtual inline void SetPitch(float pitch) { m_Rotation.x = pitch; m_Rotated = true; }
		virtual inline float GetPitch() { return m_Rotation.x; }
		
		virtual inline void SetYaw(float yaw) { m_Rotation.y = yaw; m_Rotated = true; }
		virtual inline float GetYaw() { return m_Rotation.y; }
		
		virtual inline void SetRoll(float roll) { m_Rotation.z = roll; m_Rotated = true; }
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
		
		CameraControllerData cameraControllerData;
		
	private:
		virtual void RecalculateViewMatrix();
		
		bool m_Rotated = true;
		
		glm::mat4 m_ProjectionMatrix = OneMat4;
		glm::mat4 m_ViewMatrix = OneMat4;
		glm::mat4 m_ViewProjectionMatrix = OneMat4; // View x Projection cache
		
		glm::vec3 m_Position = {0.0f, 0.0f, 3.0f};
		glm::vec3 m_PositionFactor = {1.0f, 1.0f, 1.0f}; // changes when the camera is rotated
		glm::vec3 m_Target = {0.0f, 0.0f, 0.0f};
		glm::vec3 m_Rotation = {0.0f, 0.0f, 0.0f}; // in degrees
		glm::vec3 m_Up = {0.0f, 1.0f, 0.0f};
	};
}

#endif
