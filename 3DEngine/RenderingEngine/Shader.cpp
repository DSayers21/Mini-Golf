#include "Shader.h"
#include "RenderEngine.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
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

	void Shader::UpdateUniforms(Transform* transform, Material material)
	{

	}

	void Shader::AddUniform(std::string Uniform)
	{
		int UniformLocation = glGetUniformLocation(m_Program, Uniform.c_str());
		if (UniformLocation == -1)
			std::cerr << "Error: Couldnt find uniform: " << Uniform << std::endl;
		//Add Uniform to Map
		m_Uniforms.insert(std::pair<std::string, int>(Uniform, UniformLocation));
		std::cerr << "Uniform: " << Uniform << " added." << std::endl;
	}

	void Shader::SetUniformI(std::string UniformName, int Value)
	{
		glUniform1i(m_Uniforms.find(UniformName)->second, Value);
	}

	void Shader::SetUniformF(std::string UniformName, float Value)
	{
		glUniform1f(m_Uniforms.find(UniformName)->second, Value);
	}

	void Shader::SetUniformV(std::string UniformName, Vector3f Value)
	{
		glUniform3f(m_Uniforms.find(UniformName)->second, Value.GetX(), Value.GetY(), Value.GetZ());
	}

	void Shader::SetUniformM4(const std::string UniformName, const Matrix4f& Value)
	{
		glUniformMatrix4fv(m_Uniforms.at(UniformName), 1, GL_TRUE, &(Value[0][0]));
	}

	void Shader::SetUniformBL(std::string UniformName, BaseLight* BaseLight)
	{
		SetUniformV(UniformName + ".Colour", BaseLight->GetColour());
		SetUniformF(UniformName + ".Intensity", BaseLight->GetIntensity());
	}

	void Shader::SetUniformPL(std::string UniformName, BaseLight* pointLight)
	{
		SetUniformBL(UniformName + ".Light", pointLight);
		//Attenuation
		SetUniformF(UniformName + ".Atten.Constant", pointLight->GetAttenuation().GetConstant());
		SetUniformF(UniformName + ".Atten.Linear", pointLight->GetAttenuation().GetLinear());
		SetUniformF(UniformName + ".Atten.Exponent", pointLight->GetAttenuation().GetExponent());

		SetUniformV(UniformName + ".Position", *pointLight->GetTransform()->GetPosition());
		SetUniformF(UniformName + ".Range", pointLight->GetRange());
	}

	void Shader::SetUniformSL(std::string UniformName, BaseLight* spotLight)
	{
		SetUniformPL(UniformName + ".PLight", spotLight);
		//
		SetUniformV(UniformName + ".Direction", spotLight->GetDirection());
		SetUniformF(UniformName + ".Cutoff", spotLight->GetCutoff());
	}

	void Shader::SetAttribLocation(std::string AttribName, int Location)
	{
		glBindAttribLocation(m_Program, Location, AttribName.c_str());
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

	std::string Shader::LoadShader(const std::string& fileName)
	{
		std::ifstream File;
		File.open(("./Shaders/" + fileName).c_str());

		std::string Output, Line;

		if (File.is_open())
		{
			while (File.good())
			{
				getline(File, Line);

				if (Line.find("#include") == std::string::npos)
					Output.append(Line + "\n");
				else
				{
					std::string includeFileName = Util::Split(Line, ' ')[1];
					includeFileName = includeFileName.substr(1, includeFileName.length() - 2);

					std::string toAppend = LoadShader(includeFileName);
					Output.append(toAppend + "\n");
				}
			}
		}
		else
			std::cerr << "Unable to load shader: " << fileName << std::endl;

		return Output;
	}
}