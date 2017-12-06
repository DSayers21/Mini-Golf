#pragma once

#include <vector>
#include "Vector3f.h"

namespace D3DEngine
{
	class IndexedModel
	{
	public:
		IndexedModel();
		~IndexedModel();

		void CalcNormals();

		//Getters
		inline std::vector<Vector3f>& GetPositions() { return m_Positons; }
		inline std::vector<Vector2f>& GetTexCoords() { return m_TexCoords; }
		inline std::vector<Vector3f>& GetNormals() { return m_Normals; }
		inline std::vector<int>& GetIndices() { return m_Indices; }

	private:
		std::vector<Vector3f> m_Positons;
		std::vector<Vector2f> m_TexCoords;
		std::vector<Vector3f> m_Normals;
		std::vector<int> m_Indices;
	};
}