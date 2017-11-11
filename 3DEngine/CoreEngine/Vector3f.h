#pragma once
#include "MathBasics.h"
#include "Quaternion.h"
#include "Vector2f.h"
#include <string>

namespace D3DEngine
{
	class Vector3f
	{
	public:
		Vector3f() {};
		Vector3f(float X, float Y, float Z);
		~Vector3f();

		inline float Length() { return (float)sqrt(x*x + y*y + z*z); }

		inline float Dot(Vector3f Other) { return x*Other.GetX() + y * Other.GetY() + z * Other.GetZ(); }
		Vector3f Normalise();
		Vector3f Rotate(float Angle, Vector3f Axis);
		Vector3f Lerp(Vector3f Destination, float LerpFactor);
		Vector3f CrossProduct(Vector3f Other);

		//Operators
		inline Vector3f& operator+(const Vector3f& Other) { return Vector3f(x + Other.x, y + Other.y, z + Other.z); }
		inline Vector3f& operator+(const float Other) { return Vector3f(x + Other, y + Other, z + Other); }
		inline Vector3f& operator-(const Vector3f& Other) { return Vector3f(x - Other.x, y - Other.y, z - Other.z); }
		inline Vector3f& operator-(const float Other) { return Vector3f(x - Other, y - Other, z - Other); }
		inline Vector3f& operator*(const Vector3f& Other) { return Vector3f(x * Other.x, y * Other.y, z * Other.z); }
		inline Vector3f& operator*(const float Other) { return Vector3f(x * Other, y * Other, z * Other); }
		inline Vector3f& operator/(const Vector3f& Other) { return Vector3f(x / Other.x, y / Other.y, z / Other.z); }
		inline Vector3f& operator/(const float Other) { return Vector3f(x / Other, y / Other, z / Other); }
		inline Vector3f& operator=(const Vector3f& Other) { x = Other.x; y = Other.y; z = Other.z; return *this; }
		inline bool operator==(const Vector3f& Other) { return ((x == Other.x) && (y == Other.y) && (z == Other.z)); }

		inline std::string ToString() { return std::string("(" + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + ")"); }

		//Getters
		inline float GetX() const { return x; }
		inline float GetY() const { return y; }
		inline float GetZ() const { return z; }
		//Swizzling Getter Functions
		inline Vector2f GetXY() const { return Vector2f(x, y); }
		inline Vector2f GetYZ() const { return Vector2f(y, z); }
		inline Vector2f GetZX() const { return Vector2f(z, x); }
		inline Vector2f GetYX() const { return Vector2f(y, x); }
		inline Vector2f GetZY() const { return Vector2f(z, y); }
		inline Vector2f GetXZ() const { return Vector2f(x, z); }
		//Setters
		inline void SetX(float X) { x = X; }
		inline void SetY(float Y) { y = Y; }
		inline void SetZ(float Z) { z = Z; }
	private:
		float x;
		float y;
		float z;
	};
}