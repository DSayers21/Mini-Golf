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
		void AddVertices(Vert* Vertices, int VertSize, int* Indices, int IndexSize);
		void AddVertices(Vert* Vertices, int VertSize, int* Indices, int IndexSize, bool calcNormals);

		void Draw();
	private: 
		void CalcNormals(Vert* Vertices, int VertSize, int* Indices, int IndexSize);

		//VBO is a Pointer to the data
		unsigned int m_VBO; //Vertex Buffer Object
		unsigned int m_IBO; //Index Buffer Object
		int m_VertSize;
		int m_IndicesSize;
	};
}