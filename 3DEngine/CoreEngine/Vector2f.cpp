//Includes
#include "Vector2f.h"

namespace D3DEngine
{
	Vector2f::Vector2f() :
		x(0), y(0)
	{
		//Empty
	}

	Vector2f::Vector2f(float X, float Y) :
		x(X), y(Y)
	{
		//Empty
	}

	Vector2f::~Vector2f()
	{
		//Empty
	}

	Vector2f Vector2f::Normalise()
	{
		//Get length of vector
		float Len = Length();
		//Divide each element by the length
		x /= Len;
		y /= Len;
		//Return the vector
		return *this;
	}

	Vector2f Vector2f::Rotate(float Angle)
	{
		//Calculate the radian angle
		double Rad = (double)TO_RADIANS(Angle);
		//Get the cos and sin of the angle
		double Cos = (double)cos(Rad);
		double Sin = (double)sin(Rad);
		//Return the rotated vector
		return Vector2f(float(x*Cos - y*Sin), float(x*Sin + y * Cos));
	}

	Vector2f Vector2f::Lerp(Vector2f Destination, float LerpFactor)
	{
		//Calculate the lerp and return it
		return (Destination - *this * LerpFactor + *this);
	}

	float Vector2f::CrossProduct(Vector2f& Other)
	{
		//Calculate the cross product and return it
		return (x * Other.GetY()) - (y * Other.GetX());
	}
}