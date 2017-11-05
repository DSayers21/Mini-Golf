#include "Mesh.h"

namespace D3DEngine
{
	Mesh::Mesh()
	{
		glGenBuffers(1, &m_VBO);
		m_Size = 0;
	}

	Mesh::~Mesh()
	{
		if (m_VBO) glDeleteBuffers(1, &m_VBO);
	}

	void Mesh::AddVertices(Vert Vertices[], unsigned int Size)
	{
		m_Size = Size;
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, m_Size * sizeof(Vert), Vertices, GL_STATIC_DRAW);
	}

	void Mesh::Draw()
	{
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, Vert::SIZE * 4, 0);
		glDrawArrays(GL_TRIANGLES, 0, m_Size);

		glDisableVertexAttribArray(0);
	}
}