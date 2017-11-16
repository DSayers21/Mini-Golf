#pragma once

#include <map>
#include "ShaderResource.h"

namespace D3DEngine
{
	class ShaderList
	{
	public:
		ShaderList();
		~ShaderList();

		ShaderResource* GetShader(std::string Name);
		void AddShader(std::string Name, ShaderResource* shaderResource);
		void RemoveShader(std::string Name);
	private:
		std::map<std::string, ShaderResource*>* LoadedShaders;
	};
}