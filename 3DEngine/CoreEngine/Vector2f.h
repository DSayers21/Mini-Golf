#pragma once

#include <string>
#include "MathBasics.h"

namespace D3DEngine
{
	class Vector2f
	{
	public:
		Vector2f(float X, float Y);
		~Vector2f();

		inline float Max() { return (x < y) ? y : x; }
		inline float Length(){ return (float)sqrt(x*x + y*y); }
		inline float Dot(Vector2f Other) { return x*Other.GetX() + y * Other.GetY(); }
		Vector2f Normalise();
		Vector2f Rotate(float Angle);

		Vector2f Lerp(Vector2f Destination, float LerpFactor);

		float CrossProduct(Vector2f & Other);

		//Operators
		inline Vector2f& operator+(const Vector2f& Other) { return Vector2f(x + Other.x, y + Other.y); }
		inline Vector2f& operator+(const float Other) { return Vector2f(x + Other, y + Other); }
		inline Vector2f& operator-(const Vector2f& Other) { return Vector2f(x - Other.x, y - Other.y); }
		inline Vector2f& operator-(const float Other) { return Vector2f(x - Other, y - Other); }
		inline Vector2f& operator*(const Vector2f& Other) { return Vector2f(x * Other.x, y * Other.y); }
		inline Vector2f& operator*(const float Other) { return Vector2f(x * Other, y * Other); }
		inline Vector2f& operator/(const Vector2f& Other) { return Vector2f(x / Other.x, y / Other.y); }
		inline Vector2f& operator/(const float Other) { return Vector2f(x / Other, y / Other); }
		inline bool operator==(const Vector2f& Other) { return ((x == Other.x) && (y == Other.y)); }

		inline std::string ToString() { return std::string("(" + std::to_string(x) + " " + std::to_string(y) + ")"); }
		//Getters
		inline float GetX() { return x; }
		inline float GetY() { return y; }
		//Setters
		inline void SetX(float X) { x = X; }
		inline void SetY(float Y) { y = Y; }
		inline void Set(float X, float Y) { x = X; y = Y; };
		inline void Set(Vector2f& Other) { x = Other.GetX(); y = Other.GetY(); };
	private:
		float x;
		float y;
	};
}