#include "Mesh.h"

namespace D3DEngine
{
	Mesh::Mesh()
	{
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_IBO);
		m_VertSize = 0;
		m_IndicesSize = 0;
	}

	Mesh::~Mesh()
	{
		if (m_VBO) glDeleteBuffers(1, &m_VBO);
		if (m_IBO) glDeleteBuffers(1, &m_IBO);
	}

	void Mesh::AddVertices(Vert* Vertices, int VertSize, int* Indices, int IndexSize)
	{
		m_VertSize = VertSize;
		m_IndicesSize = IndexSize;
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, m_VertSize * sizeof(Vert), Vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndicesSize * sizeof(unsigned int), Indices, GL_STATIC_DRAW);
	}

	void Mesh::Draw()
	{
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, Vert::SIZE * 4, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glDrawElements(GL_TRIANGLES, m_IndicesSize, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
	}
}