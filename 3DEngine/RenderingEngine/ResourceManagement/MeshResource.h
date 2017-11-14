#pragma once
#include <GL/glew.h>

namespace D3DEngine
{
	class MeshResource
	{
	public:
		MeshResource();
		~MeshResource();

		inline void AddReference() { m_RefCount++; }
		inline bool RemoveReference() { m_RefCount--; return m_RefCount == 0; }

		//Getters
		inline unsigned int GetVBO() { return VBO; }
		inline unsigned int GetIBO() { return IBO; }
		inline unsigned int GetVERTEXSIZE() { return VERTEXSIZE; }
		inline unsigned int GetINDEXSIZE() { return INDEXSIZE; }
		//Setters
		inline void SetVERTEXSIZE(unsigned int VertexSize) { VERTEXSIZE = VertexSize; }
		inline void SetINDEXSIZE(unsigned int IndexSize) { INDEXSIZE = IndexSize; }
	private:
		unsigned int VBO;	//Vertex Buffer Object
		unsigned int IBO;	//Index Buffer Object
		unsigned int VERTEXSIZE;
		unsigned int INDEXSIZE;
		int m_RefCount = 0;
	};
}