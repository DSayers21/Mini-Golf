//Includes
#include "Vector3f.h"
#include "Quaternion.h"
#include <iostream>

namespace D3DEngine
{
	Vector3f::Vector3f(float X, float Y, float Z) :
		x(X), y(Y), z(Z)
	{
		//Empty
	}

	Vector3f::~Vector3f()
	{
		//Empty
	}

	Vector3f Vector3f::Max(const Vector3f& other) const
	{
		//Get the max x,y and z from the vectors
		float X = (x < other.x) ? other.x : x;
		float Y = (y < other.y) ? other.y : y;
		float Z = (z < other.z) ? other.z : z;
		//Return the vector of the maximum components
		return Vector3f(X, Y, Z);
	}

	Vector3f Vector3f::Min(const Vector3f& other) const
	{
		//Get the min x,y and z from the vectors
		float X = (x < other.x) ? other.x : x;
		float Y = (y < other.y) ? other.y : y;
		float Z = (z < other.z) ? other.z : z;
		//Return the vector of the minimum components
		return Vector3f(X, Y, Z);
	}

	float Vector3f::Max()
	{
		//Get the maximum component from a vector
		float Max = (x < y) ? y : x;
		Max = (Max < z) ? z : Max;
		//Return the max
		return Max;
	}

	Vector3f Vector3f::Normalise() const
	{
		//Divide the vector by the length of the vector
		return Vector3f(*this/Length());
	}

	Vector3f Vector3f::Rotate(Vector3f Axis, float Angle)
	{
		//Get the sin and cos of the angle
		float sinAngle = sinf(-Angle);
		float cosAngle = cosf(-Angle);

		//Rotate the vector
		*this = Vector3f(this->CrossProduct(Axis * sinAngle).Add(			//Rotation on local X
			Vector3f(*this * cosAngle))).Add(								//Rotation on local Z
				Vector3f(Axis * (this->Dot(Axis * (1 - cosAngle)))));		//Rotation on local Y
		//Return the vector
		return *this;
	}
	
	Vector3f Vector3f::Rotate(Quaternion Rotation)
	{
		//Prepare the conjugate
		Quaternion Conjugate = Rotation.Conjugate();
		//Do rotation
		Quaternion RotResult = Rotation.Mult(*this).Mult(Conjugate);
		//Set the current vector to the rotated vector
		*this = Vector3f(RotResult.GetX(), RotResult.GetY(), RotResult.GetZ());
		//Return the vector
		return *this;
	}

	Vector3f Vector3f::Lerp(Vector3f Destination, float LerpFactor)
	{
		//Calculate the lerp of the vector
		return Destination - *this * LerpFactor + *this;
	}

	Vector3f Vector3f::CrossProduct(Vector3f Other)
	{
		//Calculate the cross product of the vector
		float X = y * Other.GetZ() - z * Other.GetY();
		float Y = z * Other.GetX() - x * Other.GetZ();
		float Z = x * Other.GetY() - y * Other.GetX();
		//Return the resultant vector
		return Vector3f(X, Y, Z);
	}

	Vector3f Vector3f::Reflect(const Vector3f& normal) const
	{
		//Calculate the reflection of the vector given a nromal
		float Dot = this->Dot(normal) * 2;
		Vector3f Reflected = Vector3f(*this - Vector3f(normal *  Dot));

		//Return the reflected vector
		return Reflected;
	}
}