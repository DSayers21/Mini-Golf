#pragma once
#include "MathBasics.h"
#include "Vector3f.h"
#include "Matrix4f.h"

namespace D3DEngine
{
	class Vector3f;
	class Quaternion
	{
	public:
		Quaternion();
		Quaternion(float X, float Y, float Z, float W);
		Quaternion(Vector3f Axis, float Angle);
		~Quaternion();
		Quaternion* Quaternion::InitRotation(Vector3f Axis, float Angle);

		float Length() { return (float)sqrt(x*x + y*y + z*z + w*w); }
		Quaternion Normalise();
		Quaternion Conjugate();
		//Operators
		Quaternion Mult(Quaternion& Other);
		Quaternion Mult(Vector3f& Other);
		Quaternion Mult(float& Other);
		Matrix4f* ToRotationMatrix();
		inline bool operator==(const Quaternion& Other) { return ((x == Other.x) && (y == Other.y) && (z == Other.z) && (w == Other.w)); }
		inline bool operator!=(const Quaternion& Other) { return ((x != Other.GetX()) && (y != Other.GetY()) && (z != Other.GetZ()) && (w != Other.GetW())); }
		//
		Vector3f GetBack();
		Vector3f GetUp();
		Vector3f GetDown();
		Vector3f GetRight();
		Vector3f GetLeft();
		Vector3f GetForward();
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
		inline void Set(Quaternion& Other) { x = Other.GetX(); y = Other.GetY(); z = Other.GetZ(); w = Other.GetW(); };

	private:
		float x;
		float y;
		float z;
		float w;
	};
}