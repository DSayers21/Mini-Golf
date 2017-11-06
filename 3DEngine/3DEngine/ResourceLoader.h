#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "Util.h"
#include "Mesh.h"
#include <Vector>

namespace D3DEngine
{
	class ResourceLoader
	{
	public:
		static std::string ResourceLoader::LoadShader(const std::string& FileName);
		static Mesh* LoadMesh(std::string FileName);
	};
}