#include "Util.h"

namespace D3DEngine
{
	std::vector<std::string> Util::Split(const std::string& String, char Deliminator)
	{
		std::vector<std::string> elems;

		const char* cstr = String.c_str();
		unsigned int strLength = (unsigned int)String.length();
		unsigned int start = 0;
		unsigned int end = 0;

		while (end <= strLength)
		{
			while (end <= strLength)
			{
				if (cstr[end] == Deliminator)
					break;
				end++;
			}

			elems.push_back(String.substr(start, end - start));
			start = end + 1;
			end = start;
		}

		return elems;
	}
	std::vector<std::string> Util::RemoveEmptyStrings(std::vector<std::string> Strings)
	{
		std::vector<std::string> Return;
		for (int i = 0; i < Strings.size(); i++)
		{
			if (Strings[i] != "")
			{
				Return.push_back(Strings[i]);
			}
		}
		//Returns all strings with data
		return Return;
	}
}