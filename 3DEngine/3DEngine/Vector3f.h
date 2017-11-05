#pragma once
#include "MathBasics.h"
#include <string>
namespace D3DEngine
{
	class Vector3f
	{
	public:
		Vector3f(float X, float Y, float Z);
		~Vector3f();

		float Length() { return (float)sqrt(x*x + y*y + z*z); }

		float Dot(Vector3f Other) { return x*Other.GetX() + y * Other.GetY() + z * Other.GetZ(); }
		Vector3f Normalise();
		Vector3f Rotate(float Angle);
		Vector3f CrossProduct(Vector3f Other);

		//Operators
		Vector3f& operator+(const Vector3f& Other) { return Vector3f(x + Other.x, y + Other.y, z + Other.z); }
		Vector3f& operator+(const float Other) { return Vector3f(x + Other, y + Other, z + Other); }
		Vector3f& operator-(const Vector3f& Other) { return Vector3f(x - Other.x, y - Other.y, z - Other.z); }
		Vector3f& operator-(const float Other) { return Vector3f(x - Other, y - Other, z - Other); }
		Vector3f& operator*(const Vector3f& Other) { return Vector3f(x * Other.x, y * Other.y, z * Other.z); }
		Vector3f& operator*(const float Other) { return Vector3f(x * Other, y * Other, z * Other); }
		Vector3f& operator/(const Vector3f& Other) { return Vector3f(x / Other.x, y / Other.y, z / Other.z); }
		Vector3f& operator/(const float Other) { return Vector3f(x / Other, y / Other, z / Other); }

		inline std::string ToString() { return std::string("(" + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + ")"); }

		//Getters
		inline float GetX() const { return x; }
		inline float GetY() const { return y; }
		inline float GetZ() const { return z; }
		//Setters
		inline float SetX(float X) { x = X; }
		inline float setY(float Y) { y = Y; }
		inline float setZ(float Z) { z = Z; }
	private:
		float x;
		float y;
		float z;
	};
}