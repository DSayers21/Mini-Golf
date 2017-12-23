#include "Util.h"

namespace D3DEngine
{
	std::vector<std::string> Util::Split(const std::string& String, char Deliminator)
	{
		//Create vector of strings
		std::vector<std::string> elems;

		//Get current string
		const char* cstr = String.c_str();
		//Get length of current string
		unsigned int strLength = (unsigned int)String.length();
		//Start and end pos
		unsigned int start = 0;
		unsigned int end = 0;
		//While end is less than or equal to the string length
		while (end <= strLength)
		{
			//While end is less than or equal to the string length
			while (end <= strLength)
			{
				//Check if equal to delim
				if (cstr[end] == Deliminator)
					break;
				//Increment end
				end++;
			}
			//Add current string to the found delim
			elems.push_back(String.substr(start, end - start));
			//Increase start
			start = end + 1;
			//Set end to be at start
			end = start;
		}
		//Return the vector of strings
		return elems;
	}
	std::vector<std::string> Util::RemoveEmptyStrings(std::vector<std::string> Strings)
	{
		//Setup vector of strings
		std::vector<std::string> Return;
		//Loop through all strings
		for (int i = 0; i < Strings.size(); i++)
			if (Strings[i] != "")	//If string is not empty
				Return.push_back(Strings[i]);	//Add it to return vector
		//Returns all strings with data
		return Return;
	}
}