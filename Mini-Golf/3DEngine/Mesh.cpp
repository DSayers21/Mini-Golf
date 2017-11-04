#include "Mesh.h"

namespace D3DEngine
{
	Mesh::Mesh(Vertex* Vertices, unsigned int NumVertices)
	{
		m_DrawCount = NumVertices;
		glGenVertexArrays(1, &m_VertexArrayObject);
		glBindVertexArray(m_VertexArrayObject);

		glGenBuffers(NUM_BUFFERS, m_VertexArrayBuffers);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffers[POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, NumVertices*sizeof(Vertices[0]), Vertices, GL_STATIC_DRAW);

		//Attrib Array at 0 - Pos
		glEnableVertexAttribArray(0);
		//Treat Attrib as array
		glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, 0);

		glBindVertexArray(0);
	}

	Mesh::~Mesh()
	{
		glDeleteVertexArrays(1, &m_VertexArrayObject);
	}

	void Mesh::Draw()
	{
		glBindVertexArray(m_VertexArrayObject);

		glDrawArrays(GL_TRIANGLES, 0, m_DrawCount);

		glBindVertexArray(0);
	}

	Mesh::Mesh(const Mesh & Other)
	{

	}

	void Mesh::operator=(const Mesh & rhs)
	{
		
	}
}