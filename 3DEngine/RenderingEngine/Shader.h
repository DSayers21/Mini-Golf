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

#include "ResourceManagement/ShaderResource.h"
#include "ResourceManagement/ShaderList.h"

namespace D3DEngine
{
	typedef std::map<std::string, std::vector<StructComponent>> STRUCTMAP;
	typedef std::pair<std::string, std::vector<StructComponent>> STRUCTPAIR;

	class RenderEngine;
	class BaseLight;

	class Shader
	{
	public:
		Shader(std::string FileName, ShaderList* shaderList);
		~Shader();
		Shader(const Shader &other);


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

		void AddAllAttributes(std::string* ShaderText);

		void AddAllUniforms(std::string* ShaderText);

		void AddUniform(std::string Uniform);

		void SetUniformI(const std::string& UniformName, const int& Value) const;
		void SetUniformF(const std::string& UniformName, float Value) const;
		void SetUniformV(const std::string& UniformName, Vector3f Value) const;
		void SetUniformM4(const std::string& UniformName, const Matrix4f& Value) const;

		void SetUniformDL(const std::string& UniformName, BaseLight* DirLight) const;
		void SetUniformBL(const std::string& UniformName, BaseLight* BaseLight) const;

		void SetUniformPL(const std::string& UniformName, BaseLight* pointLight) const;

		void SetUniformSL(const std::string& UniformName, BaseLight* spotLight) const;

		void SetAttribLocation(const std::string& AttribName, int& Location);
		
	protected:
		void AddProgram(std::string Text, int Type);
		static void CheckShaderError(int Shader, int Flag, bool isProgram, const std::string& ErrorMessage);
		std::string Shader::LoadShader(const std::string& fileName);
		STRUCTMAP FindUniformStructs(std::string ShaderText);
		void AddUniformWithStructCheck(std::string UniformName, std::string UniformType, STRUCTMAP Structs);
		std::vector<StructComponent> GetStuctFromMap(STRUCTMAP Structs, std::string Key);

		//
		std::string m_Name;
		ShaderResource* m_ShaderResource;
		ShaderList* m_ShaderList;
	};
}