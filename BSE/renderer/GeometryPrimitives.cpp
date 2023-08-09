#include <Core.h>
#include <renderer/GeometryPrimitives.h>

namespace BSE {
	namespace Primitives {
		// Whole Primitives
		Rectangle::Rectangle(const std::string& name){
			Name = name;
			MaxVertices = 4;
			MaxIndices = 6;
			
			Vertices.resize(MaxVertices);
			Vertices[0] = { -0.5f ,	-0.5f ,	0.0f, 1.0f };
			Vertices[1] = {  0.5f , -0.5f ,	0.0f, 1.0f };
			Vertices[2] = {  0.5f ,  0.5f ,	0.0f, 1.0f };
			Vertices[3] = { -0.5f ,	 0.5f ,	0.0f, 1.0f };
			
			Indices.resize(MaxIndices);
			Indices = { 0, 1, 2, 2, 3, 0 };
			
			CenterPoint = {
				Vertices[1].x / 2,
				Vertices[2].y / 2,
				Vertices[3].z,
				1.0f
			};
			
			Id = PrimitivesCounter;
			PrimitivesCounter++;
		}
		
		// Hollow Primitives
		RectangleHollow::RectangleHollow(const std::string& name, const float& lineWidth){
			Name = name;
			LineWidth = lineWidth;
			MaxVertices = 8;
			MaxIndices = 24;
			
			Vertices.resize(MaxVertices);			
			Vertices[0] = { -0.5f		 	    ,	-0.5f				, 	0.0f, 1.0f };
			Vertices[1] = {  0.5f		 	    ,	-0.5f				, 	0.0f, 1.0f };
			Vertices[2] = {  0.5f			    ,	 0.5f				, 	0.0f, 1.0f };
			Vertices[3] = { -0.5f		 	    ,	 0.5f				, 	0.0f, 1.0f };
			Vertices[4] = { -0.5f + lineWidth   ,	-0.5f + lineWidth   , 	0.0f, 1.0f };
			Vertices[5] = {  0.5f - lineWidth   ,	-0.5f + lineWidth   , 	0.0f, 1.0f };
			Vertices[6] = {  0.5f - lineWidth   ,	 0.5f - lineWidth   , 	0.0f, 1.0f };
			Vertices[7] = { -0.5f + lineWidth   ,	 0.5f - lineWidth   , 	0.0f, 1.0f };
			
			Indices.resize(MaxIndices);
			Indices = { 
				0, 1, 5, 5, 4, 0, 
				3, 0, 4, 4, 7, 3, 
				2, 3, 7, 7, 6, 2,
				1, 2, 6, 6, 5, 1 
			};
			
			CenterPoint = {
				(Vertices[0].x - Vertices[2].x) / 2,
				(Vertices[2].y - Vertices[0].y) / 2,
				 Vertices[0].z,
				1.0f
			};
			
			Id = PrimitivesCounter;
			PrimitivesCounter++;
		}
	}
}
