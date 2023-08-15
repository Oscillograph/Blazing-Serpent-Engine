#ifndef BSE_COMPONENTS_H
#define BSE_COMPONENTS_H

#include <Core.h>

namespace BSE {
	struct TransformComponent {
		glm::mat4 Transform = glm::mat4(1.0f);
		
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform) {};
	};
	
	struct SpriteComponent {
		glm::vec4 Color = {1.0f, 1.0f, 1.0f, 1.0f};
		
		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;
		SpriteComponent(const glm::vec4& color)
			: Color(color) {};
	};
	
	
}

#endif
