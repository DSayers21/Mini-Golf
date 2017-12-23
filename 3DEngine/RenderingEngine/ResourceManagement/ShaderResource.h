#pragma once

//Includes
#include <vector>
#include <map>
#include <iostream>
#include <GL/glew.h>

namespace D3DEngine
{
	//Component representing the name and type of a uniform
	class StructComponent
	{
	public:
		//Default Constructor, init to ""s
		StructComponent() : m_Name(""), m_Type("") {}
		//Constructor
		StructComponent(std::string Name, std::string Type) : m_Name(Name), m_Type(Type) {}
		//Empty Destructor
		~StructComponent() {}

		//Getters
		inline std::string* GetName() { return &m_Name; }
		inline std::string* GetType() { return &m_Type; }

		//Setters
		inline void SetName(const std::string& Name) { m_Name = Name; }
		inline void SetType(const std::string& Type) { m_Type = Type; }

	private:
		std::string m_Name; //Name of uniform
		std::string m_Type; //Name of uniform type
	};

	class ShaderResource
	{
	public:
		//Constructor
		ShaderResource();
		//Destructor
		~ShaderResource();
		//Copy constructor
		ShaderResource(const ShaderResource &other);

		//Add reference to the shader resource
		inline void AddReference() { m_RefCount++; }
		//Remove reference from the shader resource
		inline bool RemoveReference() { m_RefCount--; return m_RefCount == 0; }

		//Getters
		inline int GetProgram() { return m_Program; }
		inline std::map<std::string, int>* GetUniforms() { return &m_Uniforms; }
		inline std::vector<StructComponent>* GetUniformsStruct() { return &m_UniformsStuct; }

		//Setters
		inline void SetProgram(int Program) { m_Program = Program; }
		inline void AddUniform(std::string UniformName, int UniformLoc) { m_Uniforms.insert(std::pair<std::string, int>(UniformName, UniformLoc)); }
		inline void AddUniformsStruct(StructComponent& uniformsstruct) { m_UniformsStuct.push_back(uniformsstruct); }

	private:
		int m_Program;			//Shader program
		int m_RefCount = 0;		//Reference counter

		std::map<std::string, int> m_Uniforms;			//Map of uniforms
		std::vector<StructComponent> m_UniformsStuct;	//Vector of struct components (representing uniforms names and types)
	};
}