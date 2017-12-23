//Includes
#include "OBJIndex.h"

namespace D3DEngine
{
	bool OBJIndex::operator<(const OBJIndex &other) const
	{
		//Tests if all elements are less than the same variable in the other OBJIndex
		if (VertexIndex < other.VertexIndex)
			return true;
		else if (VertexIndex == other.VertexIndex)
			if (NormalIndex < other.NormalIndex)
				return true;
			else if (NormalIndex == other.NormalIndex)
				if (TexCoordIndex < other.TexCoordIndex)
					return true;
				else if (TexCoordIndex == other.TexCoordIndex)
					return false;

		return false;
	}
}