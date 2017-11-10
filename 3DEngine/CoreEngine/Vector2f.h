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

		float Length(){ return (float)sqrt(x*x + y*y); }
		float Dot(Vector2f Other) { return x*Other.GetX() + y * Other.GetY(); }
		Vector2f Normalise();
		Vector2f Rotate(float Angle);

		//Operators
		Vector2f& operator+(const Vector2f& Other) { return Vector2f(x + Other.x, y + Other.y); }
		Vector2f& operator+(const float Other) { return Vector2f(x + Other, y + Other); }
		Vector2f& operator-(const Vector2f& Other) { return Vector2f(x - Other.x, y - Other.y); }
		Vector2f& operator-(const float Other) { return Vector2f(x - Other, y - Other); }
		Vector2f& operator*(const Vector2f& Other) { return Vector2f(x * Other.x, y * Other.y); }
		Vector2f& operator*(const float Other) { return Vector2f(x * Other, y * Other); }
		Vector2f& operator/(const Vector2f& Other) { return Vector2f(x / Other.x, y / Other.y); }
		Vector2f& operator/(const float Other) { return Vector2f(x / Other, y / Other); }

		inline std::string ToString() { return std::string("(" + std::to_string(x) + " " + std::to_string(y) + ")"); }
		//Getters
		inline float GetX() { return x; }
		inline float GetY() { return y; }
		//Setters
		inline float SetX(float X) { x = X; }
		inline float setY(float Y) { y = Y; }
	private:
		float x;
		float y;
	};
}