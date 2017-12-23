#pragma once

//Includes
#include "MathBasics.h"
#include <string>

namespace D3DEngine
{
	//Forward Declarations
	class Vector3f;

	class Matrix4f
	{
	public:
		//Constructor
		Matrix4f();
		//Destructor
		~Matrix4f();
		//Copy Constructor
		Matrix4f::Matrix4f(const Matrix4f &Other);

		//Init identity matrix
		Matrix4f InitIdentity();
		//Init translation matrix
		Matrix4f InitTranslation(float x, float y, float z);
		//Init rotation matrix
		Matrix4f InitRotation(float x, float y, float z);
		//Init scaling matrix
		Matrix4f InitScaling(float x, float y, float z);
		//Init perspective matrix
		Matrix4f InitPerspective(float FOV, float AspectRatio, float zNear, float zFar);
		//Init orthographic matrix
		Matrix4f InitOrthographic(float Left, float Right, float Bottom, float Top, float zNear, float zFar);
		//Init rotation matrix
		Matrix4f InitRotation(Vector3f Forward, Vector3f Up);
		//Init rotation matrix
		Matrix4f InitRotation(Vector3f Forward, Vector3f Up, Vector3f Right);
		//Transform
		Vector3f Transform(const Vector3f& Pos);
		//Multiplication of two matrix
		Matrix4f Mult(Matrix4f Other);

		//Operators
		Matrix4f operator*(const Matrix4f& Other);
		Matrix4f operator*(const float & Other);
		Matrix4f* operator=(const Matrix4f & Other);
		inline const float* operator[](int index) const { return m_Matrix[index]; }
		inline float* operator[](int index) { return m_Matrix[index]; }

		//Getters
		float Get(int x, int y) const { return m_Matrix[x][y]; }

		//Setters
		void SetVal(float Value, unsigned int x, unsigned int y) { m_Matrix[x][y] = Value; }
		void SetPlusEquals(float Value, unsigned int x, unsigned int y) { m_Matrix[x][y] += Value; }
		Matrix4f& SetMatrix(const Matrix4f& Other);

	private:
		//Matrix Data
		float m_Matrix[4][4];
	};
}