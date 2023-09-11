#include "EditorCamera.h"

namespace BSE {
	EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
		: m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip)
	{
		BSE_INFO("Calling Editor Camera constructor");
		UpdateView();
	}
	
	void EditorCamera::UpdateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_ProjectionMatrix = glm::perspective(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
		RecalculateViewMatrix();
	}
	
	void EditorCamera::UpdateView()
	{
		// m_Yaw = m_Pitch = 0.0f; // Lock the camera rotation
		m_Position = CalculatePosition();
		glm::quat orientation = GetOrientation();
		m_Rotation = glm::eulerAngles(orientation);
		m_ViewMatrix = glm::translate(OneMat4, m_Position) * glm::toMat4(orientation);
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
		RecalculateViewMatrix();
	}
	
	std::pair<float, float> EditorCamera::PanSpeed()
	{
		float x = std::min(m_ViewportWidth / 1000.0f, 2.4f);
		float xFactor = 0.0366f * (x * x) + 0.1778f * x + 0.3021f;
		
		float y = std::min(m_ViewportWidth / 1000.0f, 2.4f);
		float yFactor = 0.0366f * (y * y) + 0.1778f * y + 0.3021f;
		
		return {xFactor, yFactor};
	}
	
	float EditorCamera::RotationSpeed()
	{
		return 0.8f;
	}
	
	float EditorCamera::ZoomSpeed()
	{
		float distance = m_Distance * 0.2f;
		distance = std::max(distance, 0.0f);
		float speed = distance * distance;
		speed = std::min(speed, 100.0f);
		return speed;
	}
	
	void EditorCamera::OnUpdate(float t)
	{
		if (Input::IsKeyPressed(KeyCode::LeftControl))
		{
			BSE_CORE_INFO("LeftControl pressed");
			const glm::vec2& mouse{ Input::GetMouseX(), Input::GetMouseY() };
			glm::vec2 delta = (mouse - m_InitialMousePosition) * 0.003f;
			m_InitialMousePosition = mouse;
			
			if (Input::IsMouseButtonPressed((int)KeyCode::MouseButtonMiddle))
				MousePan(delta);
			if (Input::IsMouseButtonPressed((int)KeyCode::MouseButtonLeft))
				MouseRotate(delta);
			if (Input::IsMouseButtonPressed((int)KeyCode::MouseButtonRight))
				MouseZoom(delta.y);
		}
		
		if (Input::IsKeyPressed(BSE_KEY_W)){
			m_Position.y += 5.0f * t;
		}
		if (Input::IsKeyPressed(BSE_KEY_A)){
			m_Position.x -= 5.0f * t;
		}
		if (Input::IsKeyPressed(BSE_KEY_S)){
			m_Position.y -= 5.0f * t;
		}
		if (Input::IsKeyPressed(BSE_KEY_D)){
			m_Position.x += 5.0f * t;
		}
		
		UpdateView();
	}
	
	void EditorCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>([this](MouseScrolledEvent& event){
			return OnMouseScroll(event);
		});
	}
	
	bool EditorCamera::OnMouseScroll(MouseScrolledEvent& e)
	{
		float delta = e.GetYOffset() * 0.1f;
		MouseZoom(delta);
		UpdateView();
		return false;
	}
	
	void EditorCamera::MousePan(const glm::vec2 delta)
	{
		BSE_CORE_INFO("Mouse Pan");
		auto [xSpeed, ySpeed] = PanSpeed();
		m_FocalPoint += GetRightDirection() * delta.x * xSpeed * m_Distance;
		m_FocalPoint += GetUpDirection() * delta.y * ySpeed * m_Distance;
	}
	
	void EditorCamera::MouseRotate(const glm::vec2 delta)
	{
		BSE_CORE_INFO("Mouse Rotate");
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		m_Yaw += yawSign * delta.x * RotationSpeed();
		m_Pitch += delta.y * RotationSpeed();
	}
	
	void EditorCamera::MouseZoom(float delta)
	{
		BSE_CORE_INFO("Mouse Zoom");
		m_Distance -= delta * ZoomSpeed();
		
		// limit the zoom distance
		if (m_Distance < 1.0f)
		{
			m_FocalPoint += GetForwardDirection();
			m_Distance = 1.0f;
		}
	}
	
	glm::vec3 EditorCamera::GetUpDirection()
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	
	glm::vec3 EditorCamera::GetRightDirection()
	{
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	
	glm::vec3 EditorCamera::GetForwardDirection()
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	
	
	glm::quat EditorCamera::GetOrientation()
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}
	
	glm::vec3 EditorCamera::CalculatePosition()
	{
		m_FocalPoint = GetForwardDirection() * m_Distance;
		m_Position = m_FocalPoint;
		return m_FocalPoint;
	}
	
}
