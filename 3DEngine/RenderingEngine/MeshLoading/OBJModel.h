#pragma once

#include <vector>
#include <iostream>
#include <fstream>

#include "Vector3f.h"
#include "OBJIndex.h"
#include "Util.h"

namespace D3DEngine
{
	class OBJModel
	{
	public:
		OBJModel(std::string FileName);
		~OBJModel();

		void LoadMesh(std::string FileName);

		//Getters
		inline std::vector<Vector3f> GetPositions() { return m_Positons; }
		inline std::vector<Vector2f> GetTexCoords() { return m_TexCoords; }
		inline std::vector<Vector3f> GetNormals() { return m_Normals; }
		inline std::vector<OBJIndex> GetIndices() { return m_Indices; }

	private:
		OBJIndex ParseObjIndex(std::string Token);

		std::vector<Vector3f> m_Positons;
		std::vector<Vector2f> m_TexCoords;
		std::vector<Vector3f> m_Normals;
		std::vector<OBJIndex> m_Indices;

		bool m_HasTexCoords;
		bool m_HasNormals;
	};
}