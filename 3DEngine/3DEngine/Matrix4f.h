#pragma once
#include "MathBasics.h"
#include <string>

namespace D3DEngine
{
	class Matrix4f
	{
	public:
		Matrix4f();
		~Matrix4f();

		Matrix4f InitIdentity();

		//Operators
		Matrix4f& operator*(const Matrix4f& Other) const;

		//Getters
		float Get(int x, int y) const { return m_Matrix[x][y]; }
		//Setters
		void Set(float Value, unsigned int x, unsigned int y) { m_Matrix[x][y] = Value; }
		void SetPlusEquals(float Value, unsigned int x, unsigned int y) { m_Matrix[x][y] += Value; }

		inline const float* operator[](int index) const { return m_Matrix[index]; }
		inline float* operator[](int index) { return m_Matrix[index]; }
	private:
		float m_Matrix[4][4];
	};
}