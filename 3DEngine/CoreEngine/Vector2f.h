#pragma once

//Includes
#include <string>
#include "MathBasics.h"

namespace D3DEngine
{
	class Vector2f
	{
	public:
		//Constructors
		Vector2f();
		Vector2f(float X, float Y);
		//Destructor
		~Vector2f();

		//Get the max element of the vector
		inline float Max() { return (x < y) ? y : x; }
		//Get the length of the vector
		inline float Length(){ return (float)sqrt(x*x + y*y); }
		//Get the dot product of the vector with another
		inline float Dot(Vector2f Other) { return x*Other.GetX() + y * Other.GetY(); }
		//Normalise the vector
		Vector2f Normalise();
		//Rotate the vector by an angle
		Vector2f Rotate(float Angle);
		//Calculate the lerp
		Vector2f Lerp(Vector2f Destination, float LerpFactor);
		//Calculate the cross product between two vectors
		float CrossProduct(Vector2f & Other);

		//Operators
		inline Vector2f& operator+(const Vector2f& Other)	{ return Vector2f(x + Other.x, y + Other.y); }
		inline Vector2f& operator+(const float Other)		{ return Vector2f(x + Other, y + Other);	 }
		inline Vector2f& operator-(const Vector2f& Other)	{ return Vector2f(x - Other.x, y - Other.y); }
		inline Vector2f& operator-(const float Other)		{ return Vector2f(x - Other, y - Other);	 }
		inline Vector2f& operator*(const Vector2f& Other)	{ return Vector2f(x * Other.x, y * Other.y); }
		inline Vector2f& operator*(const float Other)		{ return Vector2f(x * Other, y * Other);	 }
		inline Vector2f& operator/(const Vector2f& Other)	{ return Vector2f(x / Other.x, y / Other.y); }
		inline Vector2f& operator/(const float Other)		{ return Vector2f(x / Other, y / Other);	 }
		inline bool operator==(const Vector2f& Other)		{ return ((x == Other.x) && (y == Other.y)); }

		//Turn the x and y components into a string (for easy outputting)
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
		//Vector Data
		float x;
		float y;
	};
}