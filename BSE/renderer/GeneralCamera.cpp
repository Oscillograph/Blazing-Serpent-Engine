#include <renderer/GeneralCamera.h>

namespace BSE {
	GeneralCamera::GeneralCamera(){
		m_ProjectionMatrix = glm::ortho(-1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f);
		m_ViewMatrix = OneMat4;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	
	GeneralCamera::GeneralCamera(const glm::mat4& projection){
		m_ProjectionMatrix = projection;
		m_ViewMatrix = OneMat4;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	
	GeneralCamera::GeneralCamera(float left, float right, float top, float bottom, float znear, float zfar){
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, znear, zfar);
		m_ViewMatrix = OneMat4;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	
	GeneralCamera::~GeneralCamera(){
		
	}
	
	void GeneralCamera::RecalculateViewMatrix(){
		glm::mat4 transform = 
			glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationX), glm::vec3(1.0f, 0.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationY), glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationZ), glm::vec3(0.0f, 0.0f, 1.0f));
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		
		m_RotationX = m_Rotation.x;
		m_RotationY = m_Rotation.y;
		m_RotationZ = m_Rotation.z;
	} 
}
