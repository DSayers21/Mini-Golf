#include "Vector3f.h"

namespace D3DEngine
{
	Vector3f::Vector3f(float X, float Y, float Z) :
		x(X), y(Y), z(Z)
	{

	}

	Vector3f::~Vector3f()
	{

	}

	Vector3f Vector3f::Normalise()
	{
		float Len = Length();
		x /= Len;
		y /= Len;
		z /= Len;
		return *this;
	}

	Vector3f Vector3f::Rotate(float Angle)
	{
		return Vector3f(0,0,0);
	}

	Vector3f Vector3f::CrossProduct(Vector3f Other)
	{
		float X = y * Other.GetZ() - z * Other.GetY();
		float Y = z * Other.GetX() - x * Other.GetZ();
		float Z = x * Other.GetY() - y * Other.GetX();

		return Vector3f(X, Y, Z);
	}
}