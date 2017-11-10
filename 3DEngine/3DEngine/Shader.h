#pragma once

#include <GL/glew.h>
#include "ResourceLoader.h"
#include "RenderUtil.h"
#include "Vector3f.h"
#include "Matrix4f.h"
#include "Material.h"
#include <iostream>
#include <string>
#include <map>
#include "DirectionalLight.h"

namespace D3DEngine
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		void CompileShader();
		void Bind();

		inline void AddVertexShader(std::string Text) { AddProgram(Text, GL_VERTEX_SHADER); }
		inline void AddFragmentShader(std::string Text) { AddProgram(Text, GL_FRAGMENT_SHADER); }
		inline void AddGeometryShader(std::string Text) { AddProgram(Text, GL_GEOMETRY_SHADER); }
		inline void AddVertexShaderFromFile(std::string FileName) { AddProgram(LoadShader(FileName), GL_VERTEX_SHADER); }
		inline void AddFragmentShaderFromFile(std::string FileName) { AddProgram(LoadShader(FileName), GL_FRAGMENT_SHADER); }
		inline void AddGeometryShaderFromFile(std::string FileName) { AddProgram(LoadShader(FileName), GL_GEOMETRY_SHADER); }
		//Uniforms
		void UpdateUniforms(Matrix4f WorldMatrix, Matrix4f ProjectedMatrix, Material material);

		void AddUniform(std::string Uniform);
		void SetUniformI(std::string UniformName, int Value);
		void SetUniformF(std::string UniformName, float Value);
		void SetUniformV(std::string UniformName, Vector3f Value);
		void SetUniformM4(const std::string UniformName, const Matrix4f& Value);
		void SetUniformDL(std::string UniformName, DirectionalLight DirLight);
		void SetUniformBL(std::string UniformName, BaseLight BaseLight);
	private:
		void AddProgram(std::string Text, int Type);
		static void CheckShaderError(int Shader, int Flag, bool isProgram, const std::string& ErrorMessage);
		std::string Shader::LoadShader(const std::string& fileName);

		int m_Program;
		std::map<std::string, int> m_Uniforms = std::map<std::string, int>();
	};
}