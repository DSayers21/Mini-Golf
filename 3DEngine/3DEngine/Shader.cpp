#include "Shader.h"

namespace D3DEngine
{
	Shader::Shader()
	{
		m_Program = glCreateProgram();
		if (m_Program == 0)
			std::cerr << "Shader Creation Failed: Could not find valid memory location" << std::endl;
	}

	Shader::~Shader()
	{

	}

	void Shader::CompileShader()
	{
		glLinkProgram(m_Program);
		CheckShaderError(m_Program, GL_LINK_STATUS, true, "Error linking shader program");

		glValidateProgram(m_Program);
		CheckShaderError(m_Program, GL_VALIDATE_STATUS, true, "Invalid shader program");
	}

	void Shader::Bind()
	{
		glUseProgram(m_Program);
	}

	void Shader::AddUniform(std::string Uniform)
	{
		int UniformLocation = glGetUniformLocation(m_Program, Uniform.c_str());
		if (UniformLocation == -1)
			std::cerr << "Error: Couldnt find uniform: " << Uniform << std::endl;
		//Add Uniform to Map
		m_Uniforms.insert(std::pair<std::string, int>(Uniform, UniformLocation));
	}

	void Shader::SetUniformI(std::string UniformName, int Value)
	{
		glUniform1i(m_Uniforms.find(UniformName)->second, Value);
	}

	void Shader::SetUniformF(std::string UniformName, float Value)
	{
		glUniform1f(m_Uniforms.find(UniformName)->second, Value);
	}

	void Shader::SetUniform(std::string UniformName, Vector3f Value)
	{
		glUniform3f(m_Uniforms.find(UniformName)->second, Value.GetX(), Value.GetY(), Value.GetZ());
	}

	void Shader::SetUniform(const std::string UniformName, const Matrix4f& Value)
	{
		glUniformMatrix4fv(m_Uniforms.at(UniformName), 1, GL_TRUE, &(Value[0][0]));
	}

	void Shader::AddProgram(std::string Text, int Type)
	{
		int Shader = glCreateShader(Type);

		if (Shader == 0)
			std::cerr << "Shader Creation Failed: Could not find valid memory location when adding shader" << std::endl;

		const GLchar* p[1];
		p[0] = Text.c_str();
		GLint Lengths[1];
		Lengths[0] = Text.length();

		glShaderSource(Shader, 1, p, Lengths);
		glCompileShader(Shader);

		CheckShaderError(Shader, GL_COMPILE_STATUS, false, "ERR");

		glAttachShader(m_Program, Shader);
	}

	void Shader::CheckShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage)
	{
		GLint success = 0;
		GLchar error[1024] = { 0 };

		if (isProgram)
			glGetProgramiv(shader, flag, &success);
		else
			glGetShaderiv(shader, flag, &success);

		if (!success)
		{
			if (isProgram)
				glGetProgramInfoLog(shader, sizeof(error), NULL, error);
			else
				glGetShaderInfoLog(shader, sizeof(error), NULL, error);

			fprintf(stderr, "%s: '%s'\n", errorMessage.c_str(), error);
		}
	}
}