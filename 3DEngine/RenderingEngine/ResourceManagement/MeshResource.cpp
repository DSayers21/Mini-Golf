//Includes
#include "MeshResource.h"
#include <iostream>

namespace D3DEngine
{
	MeshResource::MeshResource()
	{
		//Generate VBO and IBO buffers
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &IBO);
		//Set reference counter to 1
		m_RefCount = 1;
	}

	MeshResource::~MeshResource()
	{
		//Display message
		std::cerr << "Destructor: MeshResource" << std::endl;
		//Delete buffers
		if (VBO) glDeleteBuffers(1, &VBO);
		if (IBO) glDeleteBuffers(1, &IBO);
		//Delete the vert and index arrays
		delete[] m_Vertices;
		delete[] m_Indices;
	}

	MeshResource::MeshResource(const MeshResource & other)
	{
		//Copy the data from the other mesh resource to this mesh resource
		VBO = other.VBO;
		IBO = other.IBO;
		VERTEXSIZE = other.VERTEXSIZE;
		INDEXSIZE = other.INDEXSIZE;
		m_RefCount = other.m_RefCount;
		m_Vertices = other.m_Vertices;
		m_Indices = other.m_Indices;
	}

	MeshResource & MeshResource::operator=(const MeshResource & other)
	{
		//Copy the data from the other mesh resource to this mesh resource
		VBO = other.VBO;
		IBO = other.IBO;
		VERTEXSIZE = other.VERTEXSIZE;
		INDEXSIZE = other.INDEXSIZE;
		m_RefCount = other.m_RefCount;
		m_Vertices = other.m_Vertices;
		m_Indices = other.m_Indices;
		//Return this mesh resource
		return *this;
	}
}