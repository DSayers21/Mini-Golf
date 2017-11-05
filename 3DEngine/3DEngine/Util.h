#pragma once

#include <vector>

namespace D3DEngine
{
	class Util
	{
	public:
		static std::vector<std::string> Util::Split(const std::string& String, char Deliminator);
	};
}
