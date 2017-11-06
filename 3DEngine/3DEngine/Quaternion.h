#pragma once
#include "MathBasics.h"
#include "Vector3f.h"

namespace D3DEngine
{
	class Vector3f;
	class Quaternion
	{
	public:
		Quaternion();
		Quaternion(float X, float Y, float Z, float W);
		~Quaternion();

		float Length() { return (float)sqrt(x*x + y*y + z*z + w*w); }
		Quaternion Normalise();
		Quaternion Conjugate();
		//Operators
		Quaternion Mult(Quaternion& Other);
		Quaternion Mult(Vector3f& Other);
		//Getters
		float GetX() const { return x; }
		float GetY() const { return y; }
		float GetZ() const { return z; }
		float GetW() const { return w; }
		//Setters
		void SetX(float X) { x = X; }
		void SetY(float Y) { y = Y; }
		void SetZ(float Z) { z = Z; }
		void SetW(float W) { w = W; }
	private:
		float x;
		float y;
		float z;
		float w;
	};
}