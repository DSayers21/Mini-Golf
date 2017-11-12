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

	float Vector3f::Max()
	{
		float Max = (x < y) ? y : x;
		Max = (Max < z) ? z : Max;
		return Max;
	}

	Vector3f Vector3f::Normalise()
	{
		const float Len = Length();
		if (Len > 0)
		{
			x /= Len;
			y /= Len;
			z /= Len;
		}
		return Vector3f(x, y, z);
	}

	Vector3f Vector3f::Rotate(float Angle, Vector3f Axis)
	{
		Quaternion Rotation = *Quaternion().InitRotation(Axis, Angle);
		Quaternion Conjugate = Rotation.Conjugate();
		Quaternion RotResult = Rotation.Mult(*this).Mult(Conjugate);

		*this = Vector3f(RotResult.GetX(), RotResult.GetY(), RotResult.GetZ());

		return *this;
	}

	Vector3f Vector3f::Lerp(Vector3f Destination, float LerpFactor)
	{
		return Destination - *this * LerpFactor + *this;
	}

	Vector3f Vector3f::CrossProduct(Vector3f Other)
	{
		float X = y * Other.GetZ() - z * Other.GetY();
		float Y = z * Other.GetX() - x * Other.GetZ();
		float Z = x * Other.GetY() - y * Other.GetX();

		return Vector3f(X, Y, Z);
	}
}