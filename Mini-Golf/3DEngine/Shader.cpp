#include "Shader.h"

#include <iostream>
#include <fstream>

namespace D3DEngine
{
	//Helper Functions
	static void CheckShaderError(GLuint Shader, GLuint Flag, bool isProgram, const std::string& ErrorMessage)
	{
		GLint Success = 0;
		GLchar Error[1024] = { 0 };
		
		if (isProgram)
			glGetProgramiv(Shader, Flag, &Success);
		else
			glGetShaderiv(Shader, Flag, &Success);

		if (Success == GL_FALSE)
		{
			if (isProgram)
				glGetProgramInfoLog(Shader, sizeof(Error), NULL, Error);
			else
				glGetShaderInfoLog(Shader, sizeof(Error), NULL, Error);

			std::cerr << ErrorMessage << ": '" << Error << "'" << std::endl;
		}
	}
	static std::string LoadShader(const std::string& FileName)
	{
		std::ifstream File;
		File.open((FileName).c_str());
		std::string Output;
		std::string Line;

		if (File.is_open())
		{
			while (File.good())
			{
				getline(File, Line);
				Output.append(Line + "\n");
			}
		}
		else
		{
			std::cerr << "Unable to Load Shader: " << FileName << std::endl;
		}

		return Output;
	}
	static  GLuint CreateShader(const std::string& Text, GLenum ShaderType)
	{
		GLuint Shader = glCreateShader(ShaderType);

		if (Shader == 0)
			std::cerr << "Error: Shader Creation Failed!" << std::endl;

		const GLchar* ShaderSourceStrings[1];
		GLint ShaderSourceStringLengths[1];
		ShaderSourceStrings[0] = Text.c_str();
		ShaderSourceStringLengths[0] = Text.length();

		glShaderSource(Shader, 1, ShaderSourceStrings, ShaderSourceStringLengths);
		glCompileShader(Shader);

		CheckShaderError(Shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

		return Shader;
	}
	//End - Helper Functions

	Shader::Shader()
	{
	}

	Shader::Shader(const std::string& FileName)
	{
		m_Program = glCreateProgram();
		m_Shaders[0] = CreateShader(LoadShader(FileName + ".vert"), GL_VERTEX_SHADER);
		m_Shaders[1] = CreateShader(LoadShader(FileName + ".frag"), GL_FRAGMENT_SHADER);

		for (unsigned int i = 0; i < m_NUM_SHADERS; i++)
			glAttachShader(m_Program, m_Shaders[i]);

		glBindAttribLocation(m_Program, 0, "Position");
		glBindAttribLocation(m_Program, 1, "TexCoord");
		glBindAttribLocation(m_Program, 2, "Normal");

		glLinkProgram(m_Program);
		CheckShaderError(m_Program, GL_LINK_STATUS, true, "Error: Program linking failed: ");
		
		glValidateProgram(m_Program);
		CheckShaderError(m_Program, GL_VALIDATE_STATUS, true, "Error: Program validation failed: ");

		m_Uniforms[TRANSFORM_U] = glGetUniformLocation(m_Program, "transform");
	}

	Shader::~Shader()
	{
		std::cerr << "Deleted Shader" << std::endl;
		for (unsigned int i = 0; i < m_NUM_SHADERS; i++)
		{
			glDetachShader(m_Program, m_Shaders[i]);
			glDeleteShader(m_Shaders[i]);
		}

		glDeleteProgram(m_Program);
	}

	void Shader::Bind()
	{
		glUseProgram(m_Program);
	}

	void Shader::Update(const Transform& transform, const Camera& camera)
	{
		glm::mat4 Model = camera.GetViewProjection() * transform.GetModel();
		glUniformMatrix4fv(m_Uniforms[TRANSFORM_U], 1, GL_FALSE, &Model[0][0]);
	}
}