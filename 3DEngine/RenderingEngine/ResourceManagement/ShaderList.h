#pragma once

//Includes
#include <map>
#include "ShaderResource.h"

namespace D3DEngine
{
	class ShaderList
	{
	public:
		//Constructor
		ShaderList();
		//Destructor
		~ShaderList();
		//Get a shader from the shader map
		ShaderResource* GetShader(const std::string& Name);
		//Add a shader to the shader map
		void AddShader(const std::string& Name, ShaderResource* shaderResource);
		//Remove a shader from the map
		void RemoveShader(const std::string& Name);
	private:
		//Map representing all the loaded shader resources
		std::map<std::string, ShaderResource*> LoadedShaders;
	};
}