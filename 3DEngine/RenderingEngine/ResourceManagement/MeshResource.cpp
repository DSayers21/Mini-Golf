#include "MeshResource.h"

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
		if (VBO) glDeleteBuffers(1, &VBO);
		if (IBO) glDeleteBuffers(1, &IBO);
	}
}