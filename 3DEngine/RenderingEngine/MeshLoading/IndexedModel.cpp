#include "IndexedModel.h"

namespace D3DEngine
{
	IndexedModel::IndexedModel()
	{
		m_Positons = std::vector<Vector3f>();
		m_TexCoords = std::vector<Vector2f>();
		m_Normals = std::vector<Vector3f>();
		m_Indices = std::vector<int>();
	}

	IndexedModel::~IndexedModel()
	{
	}
}