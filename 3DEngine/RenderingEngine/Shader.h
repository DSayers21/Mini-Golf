#pragma once

#include <GL/glew.h>
#include "Vector3f.h"
#include "Matrix4f.h"
#include "Material.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Util.h"
#include <map>

#include "Transform.h"

#include "BaseLight.h"

namespace D3DEngine
{
	struct StructComponent
	{
		StructComponent(std::string Name, std::string Type) : m_Name(Name), m_Type(Type){}
		std::string m_Name;
		std::string m_Type;
	};

	typedef std::map<std::string, std::vector<StructComponent>> STRUCTMAP;
	typedef std::pair<std::string, std::vector<StructComponent>> STRUCTPAIR;

	class RenderEngine;

	class Shader
	{
	public:
		Shader();
		~Shader();

		void Shader::InitShader(std::string FileName);

		void CompileShader();
		void Bind();

		inline void AddVertexShader(std::string Text) { AddProgram(Text, GL_VERTEX_SHADER); }
		inline void AddFragmentShader(std::string Text) { AddProgram(Text, GL_FRAGMENT_SHADER); }
		inline void AddGeometryShader(std::string Text) { AddProgram(Text, GL_GEOMETRY_SHADER); }
		inline void AddVertexShaderFromFile(std::string FileName) { AddProgram(LoadShader(FileName), GL_VERTEX_SHADER); }
		inline void AddFragmentShaderFromFile(std::string FileName) { AddProgram(LoadShader(FileName), GL_FRAGMENT_SHADER); }
		inline void AddGeometryShaderFromFile(std::string FileName) { AddProgram(LoadShader(FileName), GL_GEOMETRY_SHADER); }
		//Uniforms
		virtual void UpdateUniforms(Transform* transform, Material* material, RenderEngine* renderEngine);

		void AddAllAttributes(std::string ShaderText);

		void AddAllUniforms(std::string ShaderText);

		void AddUniform(std::string Uniform);
		void SetUniformI(std::string UniformName, int Value);
		void SetUniformF(std::string UniformName, float Value);
		void SetUniformV(std::string UniformName, Vector3f Value);
		void SetUniformM4(const std::string UniformName, const Matrix4f& Value);

		void SetUniformDL(std::string UniformName, BaseLight* DirLight);
		void SetUniformBL(std::string UniformName, BaseLight* BaseLight);

		void SetUniformPL(std::string UniformName, BaseLight* pointLight);

		void SetUniformSL(std::string UniformName, BaseLight* spotLight);

		void SetAttribLocation(std::string AttribName, int Location);
		
	protected:
		void AddProgram(std::string Text, int Type);
		static void CheckShaderError(int Shader, int Flag, bool isProgram, const std::string& ErrorMessage);
		std::string Shader::LoadShader(const std::string& fileName);
		STRUCTMAP FindUniformStructs(std::string ShaderText);
		void AddUniformWithStructCheck(std::string UniformName, std::string UniformType, STRUCTMAP Structs);
		std::vector<StructComponent> GetStuctFromMap(STRUCTMAP Structs, std::string Key);

		int m_Program;
		std::map<std::string, int> m_Uniforms = std::map<std::string, int>();


		std::vector<StructComponent> m_UniformsStuct;
	};
}