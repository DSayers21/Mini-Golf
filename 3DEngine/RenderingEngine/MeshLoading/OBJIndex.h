#pragma once

namespace D3DEngine
{
	struct OBJIndex
	{
		int VertexIndex;	//Vertex Index
		int TexCoordIndex;	//TexCoord Index
		int NormalIndex;	//Normal Index

		//Operators, Overloaded Map Key
		bool operator<(const OBJIndex &other) const;
	};
}