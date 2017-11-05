#include "Matrix4f.h"

namespace D3DEngine
{
	Matrix4f::Matrix4f()
	{
		*this = InitIdentity();
	}


	Matrix4f::~Matrix4f()
	{
	}

	Matrix4f::Matrix4f(const Matrix4f & Other)
	{
		for (unsigned int i = 0; i < 4; i++)
			for (unsigned int j = 0; j < 4; j++)
				m_Matrix[i][j] = Other[i][j];
	}

	Matrix4f Matrix4f::InitIdentity()
	{
		m_Matrix[0][0] = 1; m_Matrix[0][1] = 0; m_Matrix[0][2] = 0; m_Matrix[0][3] = 0;
		m_Matrix[1][0] = 0; m_Matrix[1][1] = 1; m_Matrix[1][2] = 0; m_Matrix[1][3] = 0;
		m_Matrix[2][0] = 0; m_Matrix[2][1] = 0; m_Matrix[2][2] = 1; m_Matrix[2][3] = 0;
		m_Matrix[3][0] = 0; m_Matrix[3][1] = 0; m_Matrix[3][2] = 0; m_Matrix[3][3] = 1;

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

	Matrix4f Matrix4f::InitRotation(float x, float y, float z) 
	{
		Matrix4f Rx, Ry, Rz;
		//Convert To radians
		x = (float)TO_RADIANS(x);
		y = (float)TO_RADIANS(y);
		z = (float)TO_RADIANS(z);

		//Init z rotation matrix
		Rz.m_Matrix[0][0] = cosf(z);	Rz.m_Matrix[0][1] = -(sinf(z));	Rz.m_Matrix[0][2] = 0;			Rz.m_Matrix[0][3] = 0;
		Rz.m_Matrix[1][0] = sinf(z);	Rz.m_Matrix[1][1] = cosf(z);	Rz.m_Matrix[1][2] = 0;			Rz.m_Matrix[1][3] = 0;
		Rz.m_Matrix[2][0] = 0;			Rz.m_Matrix[2][1] = 0;			Rz.m_Matrix[2][2] = 1;			Rz.m_Matrix[2][3] = 0;
		Rz.m_Matrix[3][0] = 0;			Rz.m_Matrix[3][1] = 0;			Rz.m_Matrix[3][2] = 0;			Rz.m_Matrix[3][3] = 1;
		//Init x rotation matrix
		Rx.m_Matrix[0][0] = 1;			Rx.m_Matrix[0][1] = 0;			Rx.m_Matrix[0][2] = 0;			Rx.m_Matrix[0][3] = 0;
		Rx.m_Matrix[1][0] = 0;			Rx.m_Matrix[1][1] = cosf(x);	Rx.m_Matrix[1][2] = -(sinf(x));	Rx.m_Matrix[1][3] = 0;
		Rx.m_Matrix[2][0] = 0;			Rx.m_Matrix[2][1] = sinf(x);	Rx.m_Matrix[2][2] = cosf(x);	Rx.m_Matrix[2][3] = 0;
		Rx.m_Matrix[3][0] = 0;			Rx.m_Matrix[3][1] = 0;			Rx.m_Matrix[3][2] = 0;			Rx.m_Matrix[3][3] = 1;
		//Init y rotation matrix
		Ry.m_Matrix[0][0] = cosf(y);	Ry.m_Matrix[0][1] = 0;			Ry.m_Matrix[0][2] = -(sinf(y));	Ry.m_Matrix[0][3] = 0;
		Ry.m_Matrix[1][0] = 0;			Ry.m_Matrix[1][1] = 1;			Ry.m_Matrix[1][2] = 0;			Ry.m_Matrix[1][3] = 0;
		Ry.m_Matrix[2][0] = sinf(y);	Ry.m_Matrix[2][1] = 0;			Ry[2][2] = cosf(y);				Ry.m_Matrix[2][3] = 0;
		Ry.m_Matrix[3][0] = 0;			Ry.m_Matrix[3][1] = 0;			Ry.m_Matrix[3][2] = 0;			Ry.m_Matrix[3][3] = 1;

		SetMatrix(Rz * (Ry * Rx));
		return *this;
	}

	Matrix4f Matrix4f::InitScaling(float x, float y, float z)
	{
		m_Matrix[0][0] = x; m_Matrix[0][1] = 0; m_Matrix[0][2] = 0; m_Matrix[0][3] = 0;
		m_Matrix[1][0] = 0; m_Matrix[1][1] = y; m_Matrix[1][2] = 0; m_Matrix[1][3] = 0;
		m_Matrix[2][0] = 0; m_Matrix[2][1] = 0; m_Matrix[2][2] = z; m_Matrix[2][3] = 0;
		m_Matrix[3][0] = 0; m_Matrix[3][1] = 0; m_Matrix[3][2] = 0; m_Matrix[3][3] = 1;

		return *this;
	}

	Matrix4f Matrix4f::Mult(Matrix4f Other)
	{
		Matrix4f Ret;
		Ret.InitIdentity();
		for (int i = 0; i<4; i++)
		{
			for (int j = 0; j<4; j++)
			{
				float Sum = 0;
				for (int k = 0; k<4; k++)
				{
					Sum += m_Matrix[i][k] * Other.m_Matrix[k][j];
				}

				Ret.m_Matrix[i][j] = Sum;
			}
		}
		return Ret;
	}

	Matrix4f Matrix4f::operator*(const Matrix4f & Other)
	{
		Matrix4f Ret;
		Ret.InitIdentity();
		for (int i = 0; i<4; i++)
		{
			for (int j = 0; j<4; j++)
			{
				float Sum = 0;
				for (int k = 0; k<4; k++)
					Sum += m_Matrix[i][k] * Other.m_Matrix[k][j];
				
				Ret.m_Matrix[i][j] = Sum;
			}
		}
		return Ret;
	}

	Matrix4f Matrix4f::operator=(const Matrix4f & Other)
	{
		for (unsigned int i = 0; i < 4; i++)
			for (unsigned int j = 0; j < 4; j++)
				m_Matrix[i][j] = Other[i][j];
		return *this;
	}

	void Matrix4f::SetEquals(const Matrix4f & Other)
	{
		for (unsigned int i = 0; i < 4; i++)
			for (unsigned int j = 0; j < 4; j++)
				m_Matrix[i][j] = Other[i][j];
	}

	Matrix4f& Matrix4f::SetMatrix(const Matrix4f & Other)
	{
		for (unsigned int i = 0; i < 4; i++)
			for (unsigned int j = 0; j < 4; j++)
				m_Matrix[i][j] = Other[i][j];

		return *this;
	}
}