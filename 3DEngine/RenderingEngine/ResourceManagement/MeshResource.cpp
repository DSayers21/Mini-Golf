#include "MeshResource.h"
#include <iostream>

namespace D3DEngine
{
	MeshResource::MeshResource()
	{
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &IBO);
		m_RefCount = 1;
	}

	MeshResource::~MeshResource()
	{
		std::cerr << "Destructor: MeshResource" << std::endl;
		if (VBO) glDeleteBuffers(1, &VBO);
		if (IBO) glDeleteBuffers(1, &IBO);
		delete[] m_Vertices;
		delete[] m_Indices;
	}

	MeshResource::MeshResource(const MeshResource & other)
	{
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
		VBO = other.VBO;
		IBO = other.IBO;
		VERTEXSIZE = other.VERTEXSIZE;
		INDEXSIZE = other.INDEXSIZE;
		m_RefCount = other.m_RefCount;

		m_Vertices = other.m_Vertices;
		m_Indices = other.m_Indices;

		return *this;
	}
}