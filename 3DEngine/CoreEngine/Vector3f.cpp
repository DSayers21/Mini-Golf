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

	Vector3f Vector3f::Max(const Vector3f& other) const
	{
		float X = (x < other.x) ? other.x : x;
		float Y = (y < other.y) ? other.y : y;
		float Z = (z < other.z) ? other.z : z;
		return Vector3f(X, Y, Z);
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

	Vector3f Vector3f::Rotate(Vector3f Axis, float Angle)
	{
		float sinAngle = sinf(-Angle);
		float cosAngle = cosf(-Angle);

		//Rotate
		*this = Vector3f(this->CrossProduct(Axis * sinAngle).Add(			//Rotation on local X
			Vector3f(*this * cosAngle))).Add(								//Rotation on local Z
				Vector3f(Axis * (this->Dot(Axis * (1 - cosAngle)))));		//Rotation on local Y

		return *this;
	}
	
	Vector3f Vector3f::Rotate(Quaternion Rotation)
	{
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