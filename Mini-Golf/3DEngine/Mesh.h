#pragma once

#include "Vecmath.h"
#include <GL/glew.h>

namespace D3DEngine
{
	class Vertex
	{
	public:
		Vertex(const vec3& Pos){ this->m_Pos = Pos; }
	protected:

	private:
		vec3 m_Pos;
	};

	class Mesh
	{
	public:
		Mesh(Vertex* Vertices, unsigned int NumVertices);
		~Mesh();

		void Draw();

		Mesh(const Mesh& Other);
		void operator=(const Mesh& rhs);

	private:
		enum
		{
			POSITION_VB,
			NUM_BUFFERS
		};
		GLuint m_VertexArrayObject;
		GLuint m_VertexArrayBuffers[NUM_BUFFERS];
		unsigned int m_DrawCount;

	};
}