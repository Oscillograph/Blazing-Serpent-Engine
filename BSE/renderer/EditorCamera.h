#ifndef BSE_EDITOR_EDITORCAMERA_H
#define BSE_EDITOR_EDITORCAMERA_H

#include <Core.h>
#include <renderer/OrthographicCamera.h>
#include <Input.h>
#include <systems/events/Event.h>
#include <systems/events/MouseEvent.h>
#include <systems/events/KeyEvent.h>
#include <systems/events/AppEvent.h>

namespace BSE {
	// This is basically The Cherno's Editor Camera class from:
	// https://www.youtube.com/watch?v=8zVtRpBTwe0
	
	// this has to have its own CameraController built into it
	class BSE_API EditorCamera : public OrthographicCamera {
	public:
		EditorCamera() = default;
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);
		
		void OnUpdate(float t);
		void OnEvent(Event& e);
		
		inline void SetDistance(float distance){ m_Distance = distance; UpdateView(); }
		inline float GetDistance() { return m_Distance; }
		
		inline void SetNearClip(float nearclip) { m_NearClip = nearclip; UpdateProjection(); }
		inline float GetNearClip() { return m_NearClip; }
		
		inline void SetFarClip(float farclip) { m_FarClip = farclip; UpdateProjection(); }
		inline float GetFarClip() { return m_FarClip; }
		
		inline void SetFOV(float fov) { m_FOV = glm::radians(fov); UpdateProjection(); }
		inline float GetFOV() { return m_FOV; }
		
		inline void SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; UpdateProjection(); }
		inline float GetAspectRatio() { return m_AspectRatio; }
		
		inline glm::vec3 GetTarget() { return m_Target; }
		inline void SetTarget(const glm::vec3& target) { m_Target = target; UpdateView(); }
		
		inline void SetViewportSize(float width, float height){
			m_ViewportWidth = width;
			m_ViewportHeight = height;
			UpdateProjection();
		}
		
		virtual inline void SetRotation(const glm::vec3 rotation) override { m_Rotation = rotation; UpdateView(); }
		
		inline void SetProjection(glm::mat4 projection) { m_ProjectionMatrix = projection; RecalculateViewProjectionMatrix(); }
		inline void SetView(glm::mat4 view) { m_ViewMatrix = view; RecalculateViewProjectionMatrix(); }
		// virtual inline const glm::mat4& GetViewProjectionMatrix() override { return m_ViewProjectionMatrix; }
		
		// these two provided by OrthographicCamera class
		// const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		// glm::mat4 GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		
		glm::vec3 GetUpDirection();
		glm::vec3 GetRightDirection();
		glm::vec3 GetForwardDirection();
		// this one provided by OrthographicCamera class
		// const glm::vec3& GetPosition() const {return m_Position; }
		glm::quat GetOrientation();
		
		inline float GetPitch(){ return m_Pitch; }
		inline void SetPitch(float pitch) { m_Pitch = pitch; m_Rotation.x = m_Pitch; m_RotationX = m_Rotation.x; UpdateView(); }
		
		inline float GetYaw(){ return m_Yaw; }
		inline void SetYaw(float yaw) { m_Yaw = yaw; m_Rotation.y = m_Yaw; m_RotationY = m_Rotation.y; UpdateView(); }
		
		inline float GetRoll(){ return m_Roll; }
		inline void SetRoll(float roll) { m_Roll = roll; m_Rotation.z = m_Roll; m_RotationZ = m_Rotation.z; UpdateView(); }
		
		inline std::pair<float, float> GetViewPort() { return {m_ViewportWidth, m_ViewportHeight}; }
		inline void SetViewPort(float width, float height) { m_ViewportWidth = width; m_ViewportHeight = height; UpdateProjection(); }
		
		void UpdateProjection();
		void UpdateView();
		void RecalculateViewProjectionMatrix();
		
	private:
		bool OnMouseScroll(MouseScrolledEvent& e);
		
		void MousePan(const glm::vec2 delta);
		void MouseRotate(const glm::vec2 delta);
		void MouseZoom(float delta);
		
		glm::vec3 CalculatePosition();
		
		std::pair<float, float> PanSpeed();
		float RotationSpeed();
		float ZoomSpeed();
		
		// --------------------------------------
		float m_FOV = glm::radians(45.0f);
		float m_AspectRatio = 1.778f;
		float m_NearClip = 0.1f;
		float m_FarClip = 1000.0f;
		float m_Distance = 0.0f;
		
		
		glm::mat4 m_ViewMatrix = OneMat4;
		glm::mat4 m_ProjectionMatrix = OneMat4;
		glm::mat4 m_ViewProjectionMatrix = OneMat4;
		
		glm::vec3 m_Position = {0.0f, 0.0f, -10.0f};
		glm::vec3 m_Target = {0.0f, 0.0f, -10.0f};
		glm::vec3 m_FocalPoint = {0.0f, 0.0f, 0.0f};
		
		glm::vec3 m_Rotation = {0.0f, 0.0f, 0.0f};
		float m_RotationX = 0.0f; // on X axis
		float m_RotationY = 0.0f; // on Y axis
		float m_RotationZ = 0.0f; // on Z axis
		
		glm::vec2 m_InitialMousePosition;
		
		float m_Pitch = 0.0f; // rotation on X axis
		float m_Yaw = 0.0f; // rotation on Y axis
		float m_Roll = 0.0f; // rotation on Z axis
		float m_ViewportWidth = 1280.0f;
		float m_ViewportHeight = 768.0f;
	};
}

#endif
