#include "ShaderResource.h"

namespace D3DEngine
{
	ShaderResource::ShaderResource()
	{
		m_Program = glCreateProgram();

		m_Uniforms = new std::map<std::string, int>();
		m_UniformsStuct = new std::vector<StructComponent>();

		if (m_Program == 0)
			std::cerr << "Shader Creation Failed: Could not find valid memory location" << std::endl;
		m_RefCount = 1;
	}


	ShaderResource::~ShaderResource()
	{
		delete[] m_Uniforms;
		delete[] m_UniformsStuct;

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