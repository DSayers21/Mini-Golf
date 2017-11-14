#pragma once
#include "MathBasics.h"
#include <string>

namespace D3DEngine
{
	class Vector3f;
	class Matrix4f
	{
	public:
		Matrix4f();
		~Matrix4f();
		Matrix4f::Matrix4f(const Matrix4f &Other);

		Matrix4f InitIdentity();
		Matrix4f InitTranslation(float x, float y, float z);

		Matrix4f InitRotation(float x, float y, float z);

		Matrix4f InitScaling(float x, float y, float z);

		Matrix4f InitPerspective(float FOV, float AspectRatio, float zNear, float zFar);

		Matrix4f InitOrthographic(float Left, float Right, float Bottom, float Top, float zNear, float zFar);

		Matrix4f InitRotation(Vector3f Forward, Vector3f Up);

		Matrix4f InitRotation(Vector3f Forward, Vector3f Up, Vector3f Right);

		Matrix4f Mult(Matrix4f Other);

		//Operators
		Matrix4f operator*(const Matrix4f& Other);
		Matrix4f* operator=(const Matrix4f & Other);
		void SetEquals(const Matrix4f& Other);
		inline const float* operator[](int index) const { return m_Matrix[index]; }
		inline float* operator[](int index) { return m_Matrix[index]; }
		//Getters
		float Get(int x, int y) const { return m_Matrix[x][y]; }
		//Setters
		void SetVal(float Value, unsigned int x, unsigned int y) { m_Matrix[x][y] = Value; }
		void SetPlusEquals(float Value, unsigned int x, unsigned int y) { m_Matrix[x][y] += Value; }
		Matrix4f& SetMatrix(const Matrix4f& Other);

	private:
		float m_Matrix[4][4];
	};
}