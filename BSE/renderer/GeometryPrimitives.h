#ifndef BSE_GEOMETRYPRIMITIVES_H
#define BSE_GEOMETRYPRIMITIVES_H

#include <Core.h>

namespace BSE {
	namespace Primitives {
		static uint32_t PrimitivesCounter = 0;
		
		// General primitive
		struct BSE_API GeometryPrimitive {
			glm::vec4 CenterPoint;
			std::vector<glm::vec4> Vertices;
			std::vector<uint32_t> Indices;
			std::string Name;
			uint32_t Id;
			
			uint32_t MaxVertices;
			uint32_t MaxIndices;
			
			virtual void Resize(const glm::vec2& size) = 0;
		};
		
		// Descendants
		
		// Whole Primitives
		struct BSE_API Circle : GeometryPrimitive {
			float Radius;
		};
		
		struct BSE_API Rectangle : GeometryPrimitive {
			Rectangle(const std::string& name);
			
			glm::vec2 Size;
			glm::vec3 PointA;
		};
		
		struct BSE_API Triangle : GeometryPrimitive {
			
		};
		
		struct BSE_API Ellipse : GeometryPrimitive {
			float RadiusA;
			float RadiusB;
		};
		
		struct BSE_API Polygon : GeometryPrimitive {
			
		};
		
		// Hollow Primitives
		struct BSE_API RectangleHollow : GeometryPrimitive {
			RectangleHollow(const std::string& name, const float& lineWidth = 0.1f);
			
			float LineWidth;
			glm::vec2 Size;
			glm::vec3 PointA;
		};
	}
}

#endif
