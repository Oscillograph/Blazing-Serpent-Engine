#include <renderer/OrthographicCamera.h>

namespace BSE {
	OrthographicCamera::OrthographicCamera(){
		m_ProjectionMatrix = glm::ortho(-1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f);
		m_ViewMatrix = glm::mat4(1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	
	OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom){
		//m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top);
		m_ViewMatrix = glm::mat4(1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	
	OrthographicCamera::~OrthographicCamera(){
		BSE_CORE_TRACE("Destroy main camera");
	}
	
	void OrthographicCamera::SetProjection(float left, float right, float top, float bottom){
		//m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	
	void OrthographicCamera::RecalculateViewMatrix(){
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
