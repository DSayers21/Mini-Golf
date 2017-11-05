#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "Util.h"

namespace D3DEngine
{
	class ResourceLoader
	{
	public:
		static std::string ResourceLoader::LoadShader(const std::string& FileName);
	};
}