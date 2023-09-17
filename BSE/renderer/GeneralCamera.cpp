#include <renderer/GeneralCamera.h>

namespace BSE {
	GeneralCamera::GeneralCamera(){
		m_ProjectionMatrix = glm::ortho(-1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f);
		RecalculateViewMatrix();
	}
	
	GeneralCamera::GeneralCamera(const glm::mat4& projection){
		m_ProjectionMatrix = projection;
		RecalculateViewMatrix();
	}
	
	GeneralCamera::GeneralCamera(float left, float right, float top, float bottom, float znear, float zfar){
		BSE_INFO("Calling General Camera orthographic constructor");
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, znear, zfar);
		RecalculateViewMatrix();
	}
	
	GeneralCamera::GeneralCamera(float fov, float aspectRatio, float nearClip, float farClip){
		BSE_INFO("Calling General Camera perspective constructor");
		perspective = true;
		m_ProjectionMatrix = glm::perspective(fov, aspectRatio, nearClip, farClip);
		RecalculateViewMatrix();
	}
	
	// direction is towards the camera -- not the opposite!
	GeneralCamera::GeneralCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up){
		m_Position = position;
		m_Target =  target;
		m_Up = up;
		RecalculateViewMatrix();
	}
	
	GeneralCamera::~GeneralCamera(){
		
	}
	
	void GeneralCamera::Update(){
		RecalculateViewMatrix();
	}
	
	void GeneralCamera::RecalculateViewMatrix(){
		if (perspective){
			// m_ViewMatrix = glm::lookAt(m_Position, m_Target - m_Position, m_Up);
			m_ViewMatrix = 
				glm::translate(OneMat4, m_Position) * 
				glm::rotate(OneMat4, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
				glm::rotate(OneMat4, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::rotate(OneMat4, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		} else {
			m_ViewMatrix = 
				glm::translate(OneMat4, m_Position) * 
				glm::rotate(OneMat4, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
				glm::rotate(OneMat4, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::rotate(OneMat4, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		}
		m_ViewProjectionMatrix = m_ProjectionMatrix * glm::inverse(m_ViewMatrix);
	} 
}
