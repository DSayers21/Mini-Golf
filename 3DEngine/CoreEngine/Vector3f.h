#pragma once
#include "MathBasics.h"
#include "Quaternion.h"
#include "Vector2f.h"
#include <string>

namespace D3DEngine
{
	class Quaternion;
	class Vector3f
	{
	public:
		Vector3f() {};
		Vector3f(float X, float Y, float Z);
		~Vector3f();

		Vector3f Max(const Vector3f& other) const;
		Vector3f Min(const Vector3f& other) const;
		float Max();
		inline float Dot(Vector3f Other) { return x*Other.GetX() + y * Other.GetY() + z * Other.GetZ(); }
		inline float Dot(Vector3f Other) const { return (x*Other.GetX()) + (y * Other.GetY()) + (z * Other.GetZ()); }
		inline float Distance(Vector3f Other) { return sqrtf(pow(x-Other.GetX(), 2) + pow(y - Other.GetY(), 2) + pow(z - Other.GetZ(), 2)); }
		inline float Magnitude(void) const { return(sqrt((x * x) + (y * y) + (z * z))); }

		Vector3f Normalise() const;
		Vector3f Rotate(Vector3f Axis, float Angle);
		Vector3f Rotate(Quaternion Rotation);
		Vector3f Lerp(Vector3f Destination, float LerpFactor);
		Vector3f CrossProduct(Vector3f Other);

		Vector3f Reflect(const Vector3f & normal) const;

		//Operators
		inline Vector3f& Add(const Vector3f& Other) { return Vector3f(x + Other.x, y + Other.y, z + Other.z); }
		//Operators
		inline Vector3f& operator+(const Vector3f& Other) { return Vector3f(x + Other.x, y + Other.y, z + Other.z); }
		inline Vector3f& operator+(const float Other) { return Vector3f(x + Other, y + Other, z + Other); }
		inline  Vector3f& Sub(const Vector3f& Other) const { return Vector3f(x - Other.x, y - Other.y, z - Other.z); }
		inline Vector3f& operator-(const Vector3f& Other) { return Vector3f(x - Other.x, y - Other.y, z - Other.z); }
		inline Vector3f& operator-(const Vector3f& Other) const { return Vector3f(x - Other.x, y - Other.y, z - Other.z); }
		inline Vector3f& operator-(const float Other) { return Vector3f(x - Other, y - Other, z - Other); }
		inline Vector3f& operator*(const Vector3f& Other) { return Vector3f(x * Other.x, y * Other.y, z * Other.z); }

		//inline Vector3f& operator*(const float Other) { return Vector3f(x * Other, y * Other, z * Other); }

		inline Vector3f& operator*(const float Other) const { return Vector3f(x * Other, y * Other, z * Other); }

		inline Vector3f& operator/(const Vector3f& Other) { return Vector3f(x / Other.x, y / Other.y, z / Other.z); }
		inline Vector3f& operator/(const float Other) const { return Vector3f(x / Other, y / Other, z / Other); }
		//inline Vector3f& operator/(const float Other) { return Vector3f(x / Other, y / Other, z / Other); }
		inline Vector3f& operator=(const Vector3f& Other) { x = Other.x; y = Other.y; z = Other.z; return *this; }
		inline Vector3f& operator=(const Vector3f& Other) const { return Vector3f(Other.x,Other.y,Other.z); }
		inline bool operator==(const Vector3f& Other) { return ((x == Other.x) && (y == Other.y) && (z == Other.z)); }
		inline bool operator!=(const Vector3f& Other) { return ((x != Other.GetX()) || (y != Other.GetY()) || (z != Other.GetZ())); }

		inline std::string ToString() { return std::string("(" + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + ")"); }
		inline float Length() const { 
			return sqrtf((x*x) + (y*y) + (z*z)); 
		}

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
		inline void Set(float X, float Y, float Z) { x = X; y = Y; z = Z; };
		inline void Set(Vector3f& Other) { x = Other.GetX(); y = Other.GetY(); z = Other.GetZ(); };

	private:
		float x;
		float y;
		float z;
	};
}