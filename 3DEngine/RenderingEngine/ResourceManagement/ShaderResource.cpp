#include "ShaderResource.h"

namespace D3DEngine
{
	ShaderResource::ShaderResource()
	{
		m_Program = glCreateProgram();
		if (m_Program == 0)
			std::cerr << "Shader Creation Failed: Could not find valid memory location" << std::endl;
		m_RefCount = 1;
	}


	ShaderResource::~ShaderResource()
	{

	}
}