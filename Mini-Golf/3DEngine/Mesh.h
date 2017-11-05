#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include "ObjLoader.h"

namespace D3DEngine
{
	class Vertex
	{
	public:
		Vertex(const glm::vec3& Pos, const glm::vec2& TexCoord, const glm::vec3& Normal = glm::vec3(0,0,0)) 
		{ 
			this->m_Pos = Pos; 
			this->m_TexCoord = TexCoord; 
			this->m_Normal = Normal;
		}
		//Getters
		inline glm::vec3* GetPos() { return &m_Pos; }
		inline glm::vec2* GetTexCoord() { return &m_TexCoord; }
		inline glm::vec3* GetNormal() { return &m_Normal; }
		//End - Getters
	private:
		glm::vec3 m_Pos;
		glm::vec2 m_TexCoord;//Position on the vector we map
		glm::vec3 m_Normal;
	};

	class Mesh
	{
	public:
		Mesh(){}
		Mesh(Vertex* Vertices, unsigned int NumVertices, unsigned int* Indices, unsigned int NumIndices);
		Mesh(const std::string& FileName);
		~Mesh();

		void Draw();

	private:
		void InitMesh(const IndexedModel& Model);

		enum
		{
			POSITION_VB,
			TEXCOORD_VB,
			NORMAL_VB,
			INDEX_VB,
			NUM_BUFFERS
		};
		GLuint m_VertexArrayObject;
		GLuint m_VertexArrayBuffers[NUM_BUFFERS];
		unsigned int m_DrawCount;
	};
}