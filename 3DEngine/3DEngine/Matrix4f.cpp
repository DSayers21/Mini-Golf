#include "Matrix4f.h"

namespace D3DEngine
{
	Matrix4f::Matrix4f()
	{
	}


	Matrix4f::~Matrix4f()
	{
	}

	Matrix4f Matrix4f::InitIdentity()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m_Matrix[i][j] = (i == j) ?  1 : 0;

		return *this;
	}

	Matrix4f Matrix4f::InitTranslation(float x, float y, float z)
	{
		m_Matrix[0][0] = 1; m_Matrix[0][1] = 0; m_Matrix[0][2] = 0; m_Matrix[0][3] = x;
		m_Matrix[1][0] = 0; m_Matrix[1][1] = 1; m_Matrix[1][2] = 0; m_Matrix[1][3] = y;
		m_Matrix[2][0] = 0; m_Matrix[2][1] = 0; m_Matrix[2][2] = 1; m_Matrix[2][3] = z;
		m_Matrix[3][0] = 0; m_Matrix[3][1] = 0; m_Matrix[3][2] = 0; m_Matrix[3][3] = 1;
		
		return *this;
	}

	Matrix4f& Matrix4f::operator*(const Matrix4f & Other) const
	{
		Matrix4f Ret;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				Ret.Set(float(0), i, j);
				for (unsigned int k = 0; k < 4; k++)
					Ret.SetPlusEquals(m_Matrix[k][j] * Other.m_Matrix[i][k], i, j);
			}
		}
		return Ret;
	}
}