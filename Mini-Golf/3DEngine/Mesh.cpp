#include "Mesh.h"
#include <vector>
#include <iostream>

namespace D3DEngine
{
	Mesh::Mesh(Vertex* Vertices, unsigned int NumVertices, unsigned int* Indices, unsigned int NumIndices)
	{
		IndexedModel Model;

		for (unsigned int i = 0; i < NumVertices; i++)
		{
			Model.m_Positions.push_back(*Vertices[i].GetPos());
			Model.m_TexCoords.push_back(*Vertices[i].GetTexCoord());
			Model.m_Normals.push_back(*Vertices[i].GetNormal());
		}

		for (unsigned int i = 0; i < NumIndices; i++)
			Model.m_Indices.push_back(Indices[i]);

		InitMesh(Model);
	}

	Mesh::Mesh(const std::string & FileName)
	{
		IndexedModel Model = OBJModel(FileName).ToIndexedModel();
		InitMesh(Model);
	}

	Mesh::~Mesh()
	{
		std::cerr << "DELETE" << std::endl;
		glDeleteVertexArrays(1, &m_VertexArrayObject);
	}

	void Mesh::Draw()
	{
		glBindVertexArray(m_VertexArrayObject);
		glDrawElements(GL_TRIANGLES, m_DrawCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void Mesh::InitMesh(const IndexedModel & Model)
	{
		m_DrawCount = Model.m_Indices.size();

		glGenVertexArrays(1, &m_VertexArrayObject);
		glBindVertexArray(m_VertexArrayObject);

		glGenBuffers(NUM_BUFFERS, m_VertexArrayBuffers);
		///////////////////////////////////////////////////////////////////////////////////////////////////
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffers[POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, Model.m_Positions.size() * sizeof(Model.m_Positions[0]), &Model.m_Positions[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);								//Attrib Array at 0 - Pos
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);		//Treat Attrib as array
		///////////////////////////////////////////////////////////////////////////////////////////////////;
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffers[TEXCOORD_VB]);
		glBufferData(GL_ARRAY_BUFFER, Model.m_Positions.size() * sizeof(Model.m_TexCoords[0]), &Model.m_TexCoords[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);								//Attrib Array at 0 - Pos
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);		//Treat Attrib as array
		///////////////////////////////////////////////////////////////////////////////////////////////////;
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffers[NORMAL_VB]);
		glBufferData(GL_ARRAY_BUFFER, Model.m_Normals.size() * sizeof(Model.m_Normals[0]), &Model.m_Normals[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);								//Attrib Array at 0 - Pos
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);		//Treat Attrib as array
		///////////////////////////////////////////////////////////////////////////////////////////////////
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VertexArrayBuffers[INDEX_VB]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Model.m_Indices.size() * sizeof(Model.m_Indices[0]), &Model.m_Indices[0], GL_STATIC_DRAW);
		///////////////////////////////////////////////////////////////////////////////////////////////////
		glBindVertexArray(0);
	}
}