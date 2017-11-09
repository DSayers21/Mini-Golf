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
		AddVertices(Vertices, VertSize, Indices, IndexSize, true);
	}

	void Mesh::AddVertices(Vert* Vertices, int VertSize, int* Indices, int IndexSize, bool calcNormals)
	{
		if (calcNormals)
			CalcNormals(Vertices, VertSize, Indices, IndexSize);

		m_VertSize = VertSize;
		m_IndicesSize = IndexSize;
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, m_VertSize * sizeof(Vert), Vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndicesSize * sizeof(int), Indices, GL_STATIC_DRAW);
	}

	void Mesh::Draw()
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vert::SIZE * 4, 0);						   //Vert
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, Vert::SIZE * 4, (GLvoid*)sizeof(Vector3f));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, Vert::SIZE * 4, (GLvoid*)(sizeof(Vector3f) + sizeof(Vector2f))); //Normals

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glDrawElements(GL_TRIANGLES, m_IndicesSize, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
	//Private
	void Mesh::CalcNormals(Vert* Vertices, int VertSize, int* Indices, int IndexSize)
	{
		std::vector<Vert> test;
		for (int i = 0; i < IndexSize; i += 3)
		{
			int i0 = Indices[i];
			int i1 = Indices[i + 1];
			int i2 = Indices[i + 2];

			Vector3f Vertex1 = Vertices[i1].GetPos() - Vertices[i0].GetPos();
			Vector3f Vertex2 = Vertices[i2].GetPos() - Vertices[i0].GetPos();
			//Calc Normal
			Vector3f Normal = Vertex1.CrossProduct(Vertex2);
			Normal = Normal.Normalise();
			Vertices[i0].SetNormal(Vertices[i0].GetNormal() + Normal);
			Vertices[i1].SetNormal(Vertices[i1].GetNormal() + Normal);
			Vertices[i2].SetNormal(Vertices[i2].GetNormal() + Normal);
		}

		for (int i = 0; i < VertSize; i += 1)
		{
			Vector3f New = Vertices[i].GetNormal();
			Vector3f NewN = New.Normalise();
			Vertices[i].SetNormal(New);
			test.push_back(Vertices[i]);
		}
	}
}