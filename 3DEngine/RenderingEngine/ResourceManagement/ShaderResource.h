#pragma once

#include <vector>
#include <map>
#include <iostream>
#include <GL/glew.h>

namespace D3DEngine
{
	struct StructComponent
	{
		StructComponent() : m_Name(""), m_Type("") {}
		StructComponent(std::string Name, std::string Type) : m_Name(Name), m_Type(Type) {}
		std::string m_Name;
		std::string m_Type;
	};

	class ShaderResource
	{
	public:
		ShaderResource();
		~ShaderResource();

		ShaderResource(const ShaderResource &other);

		inline void AddReference() { m_RefCount++; }
		inline bool RemoveReference() { m_RefCount--; return m_RefCount == 0; }

		//Getters
		inline int GetProgram() { return m_Program; }
		inline std::map<std::string, int>* GetUniforms() { return m_Uniforms; }
		inline std::vector<StructComponent>* GetUniformsStruct() { return m_UniformsStuct; }
		//Setters
		inline void SetProgram(int Program) { m_Program = Program; }
		inline void AddUniform(std::string UniformName, int UniformLoc) { m_Uniforms->insert(std::pair<std::string, int>(UniformName, UniformLoc)); }
		inline void AddUniformsStruct(StructComponent& uniformsstruct) { m_UniformsStuct->push_back(uniformsstruct); }

	private:
		int m_Program;
		int m_RefCount = 0;

		std::map<std::string, int>* m_Uniforms;
		std::vector<StructComponent>* m_UniformsStuct;
	};
}