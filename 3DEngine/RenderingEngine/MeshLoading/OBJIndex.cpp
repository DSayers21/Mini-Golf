#include "OBJIndex.h"

namespace D3DEngine
{
	/*OBJIndex::OBJIndex()
	{
	}

	OBJIndex::~OBJIndex()
	{
	}
*/
	bool OBJIndex::operator<(const OBJIndex &other) const
	{
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

	int OBJIndex::HashCode()
	{
		int BASE = 17;
		int MULTIPLIER = 31;
		int Result = BASE;

		Result = MULTIPLIER * Result + VertexIndex;
		Result = MULTIPLIER * Result + TexCoordIndex;
		Result = MULTIPLIER * Result + NormalIndex;

		return Result;
	}
}