#pragma once

//Includes
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "Vector3f.h"
#include "Matrix4f.h"
#include "Material.h"
#include "Util.h"
#include "Transform.h"
#include "ResourceManagement/ShaderResource.h"
#include "ResourceManagement/ShaderList.h"

namespace D3DEngine
{
	//Typedef map and pair for easy access
	typedef std::map<std::string, std::vector<StructComponent>> STRUCTMAP;
	typedef std::pair<std::string, std::vector<StructComponent>> STRUCTPAIR;

	//Forward declarations
	class RenderEngine;
	class BaseLight;

	class Shader
	{
	public:
		//Constructor
		Shader(const std::string& FileName, ShaderList* shaderList);
		//Destructor
		~Shader();
		//Copy Constructor
		Shader(const Shader &other);

		//Init the shader
		void Shader::InitShader(const std::string& FileName);
		//Compile the vert and frag shader into one program
		void CompileShader();
		
		void Bind();		//Bind the shader
		void UnBind();		//Un bind the shader

		//Add the shaders
		inline void AddVertexShader(const std::string& Text)				{ AddProgram(Text, GL_VERTEX_SHADER);   }
		inline void AddFragmentShader(const std::string& Text)				{ AddProgram(Text, GL_FRAGMENT_SHADER); }
		inline void AddGeometryShader(const std::string& Text)				{ AddProgram(Text, GL_GEOMETRY_SHADER); }
		//Add the shaders from file
		inline void AddVertexShaderFromFile(const std::string& FileName)	{ AddProgram(LoadShader(FileName), GL_VERTEX_SHADER);   }
		inline void AddFragmentShaderFromFile(const std::string& FileName)  { AddProgram(LoadShader(FileName), GL_FRAGMENT_SHADER); }
		inline void AddGeometryShaderFromFile(const std::string& FileName)  { AddProgram(LoadShader(FileName), GL_GEOMETRY_SHADER); }
		
		//Update all the uniforms
		virtual void UpdateUniforms(Transform* transform, Material* material, RenderEngine* renderEngine);
		//Add all attributes for the shader
		void AddAllAttributes(std::string* ShaderText);
		//Add all the uniforms for the shader
		void AddAllUniforms(std::string* ShaderText);
		//Add a uniform
		void AddUniform(const std::string& Uniform);

		//Set the uniform values
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
		//Add the program
		void AddProgram(const std::string& Text, int Type);
		//Check for shader error
		static void CheckShaderError(int Shader, int Flag, bool isProgram, const std::string& ErrorMessage);
		//Load the shader
		std::string Shader::LoadShader(const std::string& fileName);
		//Find all the uniforms in the shader text
		STRUCTMAP FindUniformStructs(const std::string& ShaderText);
		//Add the uniform and check if its a struct
		void AddUniformWithStructCheck(const std::string& UniformName, const std::string& UniformType, STRUCTMAP Structs);
		//Get the struct from a map
		std::vector<StructComponent> GetStuctFromMap(STRUCTMAP Structs, const std::string& Key);

		std::string m_Name;					//Name of the shader
		ShaderResource* m_ShaderResource;	//This shaders shader resource
		ShaderList* m_ShaderList;			//Pointer to the list of shaders
	};
}