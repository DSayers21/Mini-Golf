//Includes
#include "ShaderResource.h"

namespace D3DEngine
{
	ShaderResource::ShaderResource()
	{
		//Create program
		m_Program = glCreateProgram();
		//Prepare uniforms map
		m_Uniforms = std::map<std::string, int>();
		//Prepare vector list
		m_UniformsStuct = std::vector<StructComponent>();
		//If program failed, display message
		if (m_Program == 0) 
			std::cerr << "Shader Creation Failed: Could not find valid memory location" << std::endl;
		//Set reference counter to 1
		m_RefCount = 1;
	}

	ShaderResource::~ShaderResource()
	{
		//Display message
		std::cerr << "Destructor: Shader Resource" << std::endl;
	}

	ShaderResource::ShaderResource(const ShaderResource &other)
	{
		//Display message
		std::cerr << "Shader Resource Copied" << std::endl;
		//Copy all variables from other shader resource into this shader resource
		m_Program = other.m_Program;
		m_Uniforms = other.m_Uniforms;
		m_UniformsStuct = other.m_UniformsStuct;
	}
}