#include "Vector2f.h"

namespace D3DEngine
{
	Vector2f::Vector2f(float X, float Y) :
		x(X), y(Y)
	{
	}


	Vector2f::~Vector2f()
	{
	}

	Vector2f Vector2f::Normalise()
	{
		float Len = Length();
		x /= Len;
		y /= Len;
		return *this;
	}

	Vector2f Vector2f::Rotate(float Angle)
	{
		double Rad = (double)TO_RADIANS(Angle);
		double Cos = (double)cos(Rad);
		double Sin = (double)sin(Rad);

		return Vector2f(float(x*Cos - y*Sin), float(x*Sin + y * Cos));
	}

	Vector2f Vector2f::Lerp(Vector2f Destination, float LerpFactor)
	{
		return (Destination - *this * LerpFactor + *this);
	}

	float Vector2f::CrossProduct(Vector2f& Other)
	{
		return (x * Other.GetY()) - (y * Other.GetX());
	}
}