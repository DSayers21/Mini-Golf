#include "IndexedModel.h"

namespace D3DEngine
{
	IndexedModel::IndexedModel()
	{
		m_Positons = new std::vector<Vector3f>();
		m_TexCoords = new std::vector<Vector2f>();
		m_Normals = new std::vector<Vector3f>();
		m_Indices = new std::vector<int>();
	}

	IndexedModel::~IndexedModel()
	{
	}

	void IndexedModel::CalcNormals()
	{

		for (int i = 0; i < m_Indices->size(); i += 3)
		{
			int i0 = m_Indices->at(i);
			int i1 = m_Indices->at(i + 1);
			int i2 = m_Indices->at(i + 2);

			Vector3f a = m_Positons->at(i1);
			Vector3f b = m_Positons->at(i2);
			Vector3f c = m_Positons->at(i0);

			Vector3f Vertex1 = (a - c);
			Vertex1 = Vertex1.Normalise();
			Vector3f Vertex2 = (b - c);
			Vertex2 = Vertex2.Normalise();
			//Calc Normal
			Vector3f Normal = Vertex1.CrossProduct(Vertex2);
			//Normal = Normal.Normalise();
			m_Normals->at(i0).Set(Normal);
			m_Normals->at(i1).Set(Normal);
			m_Normals->at(i2).Set(Normal);
		}

		for (int i = 0; i < m_Normals->size(); i++)
		{
			Vector3f New = m_Normals->at(i);
			Vector3f NewN = New.Normalise();
			m_Normals->at(i).Set(NewN);
		}
	}
}