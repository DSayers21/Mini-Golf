#pragma once

//Includes
#include <vector>

namespace D3DEngine
{
	class Util
	{
	public:
		//Split Function
		static std::vector<std::string> Split(const std::string& String, char Deliminator);
		//Remove empty strings from vector
		static std::vector<std::string> RemoveEmptyStrings(std::vector<std::string> Strings);
	};
}
