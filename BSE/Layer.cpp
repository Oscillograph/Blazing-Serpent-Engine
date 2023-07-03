#include <Core.h>
#include "./Layer.h"

namespace BSE {
	Layer::Layer(const std::string& name){
		m_Name = name;
		m_Enabled = true;
	}
	
	Layer::~Layer(){
		
	}
	
	void Layer::OnAttach(){
		
	}
	
	void Layer::OnDetach(){
		
	}
	
	void Layer::OnUpdate(){
		
	}
	
	void Layer::OnEvent(Event& event){
		
	}
	
	bool Layer::IsEnabled(){
		return m_Enabled;
	}
	
	void Layer::Enable(){
		m_Enabled = true;
	}
	
	void Layer::Disable(){
		m_Enabled = false;
	}
	
	void Layer::Begin(){
		
	}
	
	void Layer::OnImGuiRender(){
		
	}
	
	void Layer::End(){
		
	}
}
