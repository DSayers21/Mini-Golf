#pragma once

namespace D3DEngine
{
	struct OBJIndex
	{
	//OBJIndex();
	//~OBJIndex();

		int VertexIndex;
		int TexCoordIndex;
		int NormalIndex;

		//Operators
		bool operator<(const OBJIndex &other) const;

		int HashCode();
	};
}