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
		float SinHalfAngle = sinf(TO_RADIANS(Angle / 2));
		float CosHalfAngle = cosf(TO_RADIANS(Angle / 2));
		//Quaternion
		float rX = Axis.GetX() * SinHalfAngle;
		float rY = Axis.GetY() * SinHalfAngle;
		float rZ = Axis.GetZ() * SinHalfAngle;
		float rW = CosHalfAngle;
		Quaternion Rotation(rX, rY, rZ, rW);
		Quaternion Conjugate = Rotation.Conjugate();

		Vector3f THIS = *this;

		Quaternion RotResult = Rotation.Mult(THIS).Mult(Conjugate);

		x = RotResult.GetX();
		y = RotResult.GetY();
		z = RotResult.GetZ();

		return *this;
	}

	Vector3f Vector3f::CrossProduct(Vector3f Other)
	{
		float X = y * Other.GetZ() - z * Other.GetY();
		float Y = z * Other.GetX() - x * Other.GetZ();
		float Z = x * Other.GetY() - y * Other.GetX();

		return Vector3f(X, Y, Z);
	}
}