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