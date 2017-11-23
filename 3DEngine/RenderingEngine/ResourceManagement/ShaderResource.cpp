#include "ShaderResource.h"

namespace D3DEngine
{
	ShaderResource::ShaderResource()
	{
		m_Program = glCreateProgram();

		m_Uniforms = std::map<std::string, int>();
		m_UniformsStuct = std::vector<StructComponent*>();

		if (m_Program == 0)
			std::cerr << "Shader Creation Failed: Could not find valid memory location" << std::endl;
		m_RefCount = 1;
	}


	ShaderResource::~ShaderResource()
	{

		std::cerr << "Deleted Shader" << std::endl;
	}

	ShaderResource::ShaderResource(const ShaderResource &other)
	{
		std::cerr << "Shader Resource Copied" << std::endl;
		m_Program = other.m_Program;
		m_Uniforms = other.m_Uniforms;
		m_UniformsStuct = other.m_UniformsStuct;
	}
}