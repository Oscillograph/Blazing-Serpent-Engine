#ifndef BSE_LAYER_H
#define BSE_LAYER_H

#include <Core.h>
#include <systems/events/Event.h>

namespace BSE {
	class BSE_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();
		
		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnEvent(Event& event);
		bool IsEnabled();
		void Enable();
		void Disable();
		
		virtual void Begin();
		virtual void OnImGuiRender(); // for imgui rendering only
		virtual void End();
		
		inline const std::string GetName() const { return m_Name; }
		
	protected:
		std::string m_Name;
		bool m_Enabled;
	};
}

#endif
