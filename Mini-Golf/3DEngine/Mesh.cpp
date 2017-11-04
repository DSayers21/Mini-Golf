#include "Mesh.h"
#include <vector>

namespace D3DEngine
{
	Mesh::Mesh(Vertex* Vertices, unsigned int NumVertices)
	{
		m_DrawCount = NumVertices;
		glGenVertexArrays(1, &m_VertexArrayObject);
		glBindVertexArray(m_VertexArrayObject);

		std::vector<vec3> Positions;
		std::vector<vec2> TexCoords;
		Positions.reserve(NumVertices);
		TexCoords.reserve(NumVertices);

		for (unsigned int i = 0; i < NumVertices; i++)
		{
			Positions.push_back(Vertices[i].m_Pos);
			TexCoords.push_back(Vertices[i].m_TexCoord);
		}
		glGenBuffers(NUM_BUFFERS, m_VertexArrayBuffers);
		///////////////////////////////////////////////////////////////////////////////////////////////////
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffers[POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, NumVertices*sizeof(Positions[0]), &Positions[0], GL_STATIC_DRAW);
		//Attrib Array at 0 - Pos
		glEnableVertexAttribArray(0);
		//Treat Attrib as array
		glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////;
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffers[TEXCOORD_VB]);
		glBufferData(GL_ARRAY_BUFFER, NumVertices * sizeof(TexCoords[0]), &TexCoords[0], GL_STATIC_DRAW);
		//Attrib Array at 0 - Pos
		glEnableVertexAttribArray(1);
		//Treat Attrib as array
		glVertexAttribPointer(1, 2, GL_DOUBLE, GL_FALSE, 0, 0);
		///////////////////////////////////////////////////////////////////////////////////////////////////
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