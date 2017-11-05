#pragma once

#include <GL/glew.h>
#include "Vert.h"

namespace D3DEngine
{
	class Mesh
	{
	public:
		Mesh();
		~Mesh();
		void AddVertices(Vert Vertices[], unsigned int Size);

		void Draw();
	private: 
		//VBO is a Pointer to the data
		unsigned int m_VBO;
		int m_Size;
	};
}