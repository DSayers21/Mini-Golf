#pragma once

//Includes
#include <GL/glew.h>
#include "../Vert.h"

namespace D3DEngine
{
	class MeshResource
	{
	public:
		//Constructor
		MeshResource();
		//Destructor
		~MeshResource();
		//Copy Constructor
		MeshResource(const MeshResource &other);
		//Equals Operator
		MeshResource& operator=(const MeshResource& other);

		//Add reference to the mesh resource
		inline void AddReference() { m_RefCount++; }
		//Remove reference from the mesh resource
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
		unsigned int VBO;			//Vertex Buffer Object
		unsigned int IBO;			//Index Buffer Object
		unsigned int VERTEXSIZE;	//Size of vertex
		unsigned int INDEXSIZE;		//Size of index
		int m_RefCount = 0;			//Reference counter

		Vert* m_Vertices;			//Array of verts
		int* m_Indices;				//Array of indices
	};
}