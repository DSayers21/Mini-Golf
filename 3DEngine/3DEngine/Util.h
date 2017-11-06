#pragma once

#include <vector>

namespace D3DEngine
{
	class Util
	{
	public:
		static std::vector<std::string> Split(const std::string& String, char Deliminator);
		static std::vector<std::string> RemoveEmptyStrings(std::vector<std::string> Strings);
	};
}
