#pragma once
#include <GL/glew.h>
#include "../Vert.h"

namespace D3DEngine
{
	class MeshResource
	{
	public:
		MeshResource();
		~MeshResource();
		MeshResource(const MeshResource &other);
		MeshResource& operator=(const MeshResource& other);

		inline void AddReference() { m_RefCount++; }
		inline bool RemoveReference() { m_RefCount--; return m_RefCount == 0; }

		//Getters
		inline unsigned int GetVBO() { return VBO; }
		inline unsigned int GetIBO() { return IBO; }
		inline unsigned int GetVERTEXSIZE() { return VERTEXSIZE; }
		inline unsigned int GetINDEXSIZE() { return INDEXSIZE; }
		inline Vert* GetVertices() { return m_Vertices; }
		inline int* GetIndices() { return m_Indices; }
		//Setters
		inline void SetVERTEXSIZE(unsigned int VertexSize) { VERTEXSIZE = VertexSize; }
		inline void SetINDEXSIZE(unsigned int IndexSize) { INDEXSIZE = IndexSize; }
		inline void SetVertices(Vert* Vertices) { m_Vertices = Vertices; }
		inline void SetIndices(int* Indices) { m_Indices = Indices; }

	private:
		unsigned int VBO;	//Vertex Buffer Object
		unsigned int IBO;	//Index Buffer Object
		unsigned int VERTEXSIZE;
		unsigned int INDEXSIZE;
		int m_RefCount = 0;

		Vert* m_Vertices;
		int* m_Indices;
	};
}