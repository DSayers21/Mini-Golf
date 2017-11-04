#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

namespace D3DEngine
{
	class Vertex
	{
	public:
		Vertex(const glm::vec3& Pos, const glm::vec2& TexCoord) { this->m_Pos = Pos; this->m_TexCoord = TexCoord; }
	
		glm::vec3 m_Pos;
		glm::vec2 m_TexCoord;//Position on the vector we map
	};

	class Mesh
	{
	public:
		Mesh(){}
		Mesh(Vertex* Vertices, unsigned int NumVertices);
		~Mesh();

		void Draw();

		/*Mesh(const Mesh& Other);
		void operator=(const Mesh& rhs);*/

	private:
		enum
		{
			POSITION_VB,
			TEXCOORD_VB,
			NUM_BUFFERS
		};
		GLuint m_VertexArrayObject;
		GLuint m_VertexArrayBuffers[NUM_BUFFERS];
		unsigned int m_DrawCount;
	};
}