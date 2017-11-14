#include "Quaternion.h"

namespace D3DEngine
{
	Quaternion::Quaternion()
	{
		Quaternion(0.0f,0.0f,0.0f,1.0f);
	}

	Quaternion::Quaternion(float X, float Y, float Z, float W) :
		x(X), y(Y), z(Z), w(W)
	{

	}

	Quaternion::Quaternion(Vector3f Axis, float Angle)
	{
		InitRotation(Axis, Angle);
	}

	Quaternion* Quaternion::InitRotation(Vector3f Axis, float Angle)
	{
		float SinHalfAngle = sinf(Angle / 2);
		float CosHalfAngle = cosf(Angle / 2);
		//Quaternion
		x = Axis.GetX() * SinHalfAngle;
		y = Axis.GetY() * SinHalfAngle;
		z = Axis.GetZ() * SinHalfAngle;
		w = CosHalfAngle;

		return this;
	}

	Quaternion::~Quaternion()
	{

	}

	Quaternion Quaternion::Normalise()
	{
		float Len = Length();
		x /= Len;
		y /= Len;
		z /= Len;
		w /= Len;
		return *this;
	}

	Quaternion Quaternion::Conjugate()
	{
		//Invert all the imaginary parts
		return Quaternion(-x, -y, -z, w);
	}

	Quaternion Quaternion::Mult(Quaternion & Other)
	{
		float X, Y, Z, W;

		W = w * Other.GetW() - x * Other.GetX() - y * Other.GetY() - z * Other.GetZ();
		X = x * Other.GetW() + w * Other.GetX() + y * Other.GetZ() - z * Other.GetY();
		Y = y * Other.GetW() + w * Other.GetY() + z * Other.GetX() - x * Other.GetZ();
		Z = z * Other.GetW() + w * Other.GetZ() + x * Other.GetY() - y * Other.GetX();

		return Quaternion(X, Y, Z, W);
	}

	Quaternion Quaternion::Mult(Vector3f & Other)
	{
		float X, Y, Z, W;
		
		W = -x * Other.GetX() - y * Other.GetY() - z * Other.GetZ();
		X = w * Other.GetX() + y * Other.GetZ() - z * Other.GetY();
		Y = w * Other.GetY() + z * Other.GetX() - x * Other.GetZ();
		Z = w* Other.GetZ() + x * Other.GetY() - y * Other.GetX();

		return Quaternion(X, Y, Z, W);
	}

	Quaternion Quaternion::Mult(float & Other)
	{
		w = w * Other - x * Other - y * Other - z * Other;
		x = x * Other + w * Other + y * Other - z * Other;
		y = y * Other + w * Other + z * Other - x * Other;
		z = z * Other + w * Other + x * Other - y * Other;

		return Quaternion(z, y, z, w);
	}

	Matrix4f* Quaternion::ToRotationMatrix()
	{
		Vector3f Forward = Vector3f(2.0f * (x*z - w*y), 2.0f * (y*z + w*x), 1.0f - 2.0f * (x*x + y*y));
		Vector3f Up = Vector3f(2.0f * (x*y + w*z), 1.0f - 2.0f * (x*x + z*z), 2.0f * (y*z - w*x));
		Vector3f Right = Vector3f(1.0f - 2.0f * (y*y + z*z), 2.0f * (x*y - w*z), 2.0f * (x*z + w*y));

		Matrix4f* RotMat = new Matrix4f();
		RotMat->InitRotation(Forward, Up, Right);
		return RotMat;
	}

	Vector3f Quaternion::GetForward()
	{
		return Vector3f(0, 0, 1).Rotate(*this);
	}

	Vector3f Quaternion::GetBack()
	{
		return Vector3f(0, 0, -1).Rotate(*this);
	}
	Vector3f Quaternion::GetUp()
	{
		return Vector3f(0, 1, 0).Rotate(*this);
	}

	Vector3f Quaternion::GetDown()
	{
		return Vector3f(0, -1, 0).Rotate(*this);
	}

	Vector3f Quaternion::GetRight()
	{
		return Vector3f(1, 0, 0).Rotate(*this);
	}

	Vector3f Quaternion::GetLeft()
	{
		return Vector3f(-1, 0, 0).Rotate(*this);
	}
}