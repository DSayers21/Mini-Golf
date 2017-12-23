//Includes
#include "Matrix4f.h"
#include "Vector3f.h"
#include <iostream>

namespace D3DEngine
{
	Matrix4f::Matrix4f()
	{
		//Set to identity matrix
		*this = InitIdentity();
	}

	Matrix4f::~Matrix4f()
	{
		//Empty
	}

	Matrix4f::Matrix4f(const Matrix4f & Other)
	{
		//Copy the matrix into the current matrix
		for (unsigned int i = 0; i < 4; i++)
			for (unsigned int j = 0; j < 4; j++)
				m_Matrix[i][j] = Other[i][j];
	}

	Matrix4f Matrix4f::InitIdentity()
	{
		//Init the identiy matrix
		m_Matrix[0][0] = 1; m_Matrix[0][1] = 0; m_Matrix[0][2] = 0; m_Matrix[0][3] = 0;
		m_Matrix[1][0] = 0; m_Matrix[1][1] = 1; m_Matrix[1][2] = 0; m_Matrix[1][3] = 0;
		m_Matrix[2][0] = 0; m_Matrix[2][1] = 0; m_Matrix[2][2] = 1; m_Matrix[2][3] = 0;
		m_Matrix[3][0] = 0; m_Matrix[3][1] = 0; m_Matrix[3][2] = 0; m_Matrix[3][3] = 1;
		//Return self
		return *this;
	}

	Matrix4f Matrix4f::InitTranslation(float x, float y, float z)
	{
		m_Matrix[0][0] = 1; m_Matrix[0][1] = 0; m_Matrix[0][2] = 0; m_Matrix[0][3] = x;
		m_Matrix[1][0] = 0; m_Matrix[1][1] = 1; m_Matrix[1][2] = 0; m_Matrix[1][3] = y;
		m_Matrix[2][0] = 0; m_Matrix[2][1] = 0; m_Matrix[2][2] = 1; m_Matrix[2][3] = z;
		m_Matrix[3][0] = 0; m_Matrix[3][1] = 0; m_Matrix[3][2] = 0; m_Matrix[3][3] = 1;
		//Return self
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
		//Return self
		return *this;
	}

	Matrix4f Matrix4f::InitScaling(float x, float y, float z)
	{
		//Init scaling matrix
		m_Matrix[0][0] = x; m_Matrix[0][1] = 0; m_Matrix[0][2] = 0; m_Matrix[0][3] = 0;
		m_Matrix[1][0] = 0; m_Matrix[1][1] = y; m_Matrix[1][2] = 0; m_Matrix[1][3] = 0;
		m_Matrix[2][0] = 0; m_Matrix[2][1] = 0; m_Matrix[2][2] = z; m_Matrix[2][3] = 0;
		m_Matrix[3][0] = 0; m_Matrix[3][1] = 0; m_Matrix[3][2] = 0; m_Matrix[3][3] = 1;
		//Return self
		return *this;
	}

	Matrix4f Matrix4f::InitPerspective(float FOV, float AspectRatio, float zNear, float zFar)
	{
		//Tan of the half of FOV, distance to centre of screen
		float THFOV = tanf(FOV / 2);
		//Aspect Ratio
		float AR = AspectRatio;
		float ZRange = zNear - zFar;
		//Init perspective matrix
		m_Matrix[0][0] = 1 / (THFOV * AR); m_Matrix[0][1] = 0;			      m_Matrix[0][2] = 0;						m_Matrix[0][3] = 0;
		m_Matrix[1][0] = 0;				   m_Matrix[1][1] = 1 / THFOV;		  m_Matrix[1][2] = 0;						m_Matrix[1][3] = 0;
		m_Matrix[2][0] = 0;				   m_Matrix[2][1] = 0;				  m_Matrix[2][2] = (-zNear - zFar)/ ZRange; m_Matrix[2][3] = 2 * zFar * zNear / ZRange;
		m_Matrix[3][0] = 0;				   m_Matrix[3][1] = 0;			      m_Matrix[3][2] = 1;						m_Matrix[3][3] = 0;
		//Return self
		return *this;
	}

	Matrix4f Matrix4f::InitOrthographic(float Left, float Right, float Bottom, float Top, float zNear, float zFar)
	{
		//Get dimensions
		float Width = Right = Left;
		float Height = Top - Bottom;
		float Depth = zFar - zNear;
		//Scale for width, height and depth of the prism, ans scale
		m_Matrix[0][0] = 2/Width;	m_Matrix[0][1] = 0;			m_Matrix[0][2] = 0;			m_Matrix[0][3] = -(Right+Left)/Width;
		m_Matrix[1][0] = 0;			m_Matrix[1][1] = 2/Height;	m_Matrix[1][2] = 0;			m_Matrix[1][3] = -(Top+Bottom)/Height;
		m_Matrix[2][0] = 0;			m_Matrix[2][1] = 0;			m_Matrix[2][2] = -2/Depth;	m_Matrix[2][3] = -(zFar+zNear)/Depth;
		m_Matrix[3][0] = 0;			m_Matrix[3][1] = 0;			m_Matrix[3][2] = 0;			m_Matrix[3][3] = 1;
		//Return self
		return *this;
	}

	Matrix4f Matrix4f::InitRotation(Vector3f Forward, Vector3f Up)
	{
		//Get the forward vector
		Vector3f forward = Forward;
		//Get the right vector
		Vector3f right = Vector3f(right.CrossProduct(forward));
		//Get the up vector
		Vector3f up = forward.CrossProduct(right);

		//Init rotation
		this->InitRotation(forward, up, right);
		//Return self
		return *this;
	}

	Matrix4f Matrix4f::InitRotation(Vector3f Forward, Vector3f Up, Vector3f Right)
	{
		//Get the forward vector
		Vector3f forward = Forward;
		//Get the right vector
		Vector3f right = Right;
		//Get the up vector
		Vector3f up = Up;

		//Init Rotation Matrix
		m_Matrix[0][0] = right.GetX();		m_Matrix[0][1] = right.GetY();		 m_Matrix[0][2] = right.GetZ();		m_Matrix[0][3] = 0;
		m_Matrix[1][0] = up.GetX();			m_Matrix[1][1] = up.GetY();			 m_Matrix[1][2] = up.GetZ();		m_Matrix[1][3] = 0;
		m_Matrix[2][0] = forward.GetX();    m_Matrix[2][1] = forward.GetY();	 m_Matrix[2][2] = forward.GetZ();   m_Matrix[2][3] = 0;
		m_Matrix[3][0] = 0;					m_Matrix[3][1] = 0;					 m_Matrix[3][2] = 0;				m_Matrix[3][3] = 1;

		//Return self
		return *this;
	}

	Vector3f Matrix4f::Transform(const Vector3f& Pos)
	{
		//Retunr the vector transformed by the vector
		return Vector3f(m_Matrix[0][0] * Pos.GetX() + m_Matrix[0][1] * Pos.GetY() + m_Matrix[0][2] * Pos.GetZ() + m_Matrix[0][3],
						m_Matrix[1][0] * Pos.GetX() + m_Matrix[1][1] * Pos.GetY() + m_Matrix[1][2] * Pos.GetZ() + m_Matrix[1][3],
						m_Matrix[2][0] * Pos.GetX() + m_Matrix[2][1] * Pos.GetY() + m_Matrix[2][2] * Pos.GetZ() + m_Matrix[2][3]);
	}

	Matrix4f Matrix4f::Mult(Matrix4f Other)
	{
		//Create Matrix
		Matrix4f Ret;
		//Multiply both matrixs togehter
		for (int i = 0; i<4; i++)
		{
			for (int j = 0; j<4; j++)
			{
				//Sum line
				float Sum = 0;
				for (int k = 0; k<4; k++)
					Sum += m_Matrix[i][k] * Other.m_Matrix[k][j];
				//Make equal to the sum
				Ret.m_Matrix[i][j] = Sum;
			}
		}
		//Return the matrix representing the mutliplication
		return Ret;
	}

	Matrix4f Matrix4f::operator*(const Matrix4f & Other)
	{
		//Create Matrix
		Matrix4f Ret;
		//Multiply both matrixs togehter
		for (int i = 0; i<4; i++)
		{
			for (int j = 0; j<4; j++)
			{
				//Sum line
				float Sum = 0;
				for (int k = 0; k<4; k++)
					Sum += m_Matrix[i][k] * Other.m_Matrix[k][j];
				//Make equal to the sum
				Ret.m_Matrix[i][j] = Sum;
			}
		}
		//Return the matrix representing the mutliplication
		return Ret;
	}

	Matrix4f Matrix4f::operator*(const float & Other)
	{
		//Create Matrix
		Matrix4f Ret;
		//Multiply matrixs by a float
		for (int i = 0; i<4; i++)
			for (int j = 0; j<4; j++)
				Ret.m_Matrix[i][j] = m_Matrix[i][j] * Other;;
		//Return the matrix representing the mutliplication
		return Ret;
	}

	Matrix4f* Matrix4f::operator=(const Matrix4f & Other)
	{
		//Set the current matrix to be equal to the passed matrix
		for (unsigned int i = 0; i < 4; i++)
			for (unsigned int j = 0; j < 4; j++)
				m_Matrix[i][j] = Other[i][j];
		//Return self
		return this;
	}

	Matrix4f& Matrix4f::SetMatrix(const Matrix4f & Other)
	{
		//Set the current matrix to be equal to the passed matrix
		for (unsigned int i = 0; i < 4; i++)
			for (unsigned int j = 0; j < 4; j++)
				m_Matrix[i][j] = Other[i][j];
		//Return self
		return *this;
	}
}