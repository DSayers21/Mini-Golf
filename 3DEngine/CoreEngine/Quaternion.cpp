//Includes
#include "Quaternion.h"

namespace D3DEngine
{
	Quaternion::Quaternion()
	{
		//Set quaternion to default values
		Quaternion(0.0f,0.0f,0.0f,1.0f);
	}

	Quaternion::Quaternion(float X, float Y, float Z, float W) :
		x(X), y(Y), z(Z), w(W)
	{
		//Empty
	}

	Quaternion::Quaternion(Vector3f Axis, float Angle)
	{
		//Init rotation
		InitRotation(Axis, Angle);
	}

	Quaternion* Quaternion::InitRotation(Vector3f Axis, float Angle)
	{
		//Set the sin and cos angle
		float SinHalfAngle = sinf(Angle / 2);
		float CosHalfAngle = cosf(Angle / 2);
		//Init Quaternion rotation
		x = Axis.GetX() * SinHalfAngle;
		y = Axis.GetY() * SinHalfAngle;
		z = Axis.GetZ() * SinHalfAngle;
		w = CosHalfAngle;
		//Return the quaternion
		return this;
	}

	Quaternion::~Quaternion()
	{
		//Empty
	}

	Quaternion Quaternion::Normalise()
	{
		//Get the length
		float Len = Length();
		//Divide each element by the length
		x /= Len;
		y /= Len;
		z /= Len;
		w /= Len;
		//Return the quaternion
		return *this;
	}

	Quaternion Quaternion::Conjugate()
	{
		//Invert all the imaginary parts
		return Quaternion(-x, -y, -z, w);
	}

	Quaternion Quaternion::Mult(Quaternion & Other)
	{
		//Get new quaternion valyes
		float X, Y, Z, W;
		//Calculate each component
		W = w * Other.GetW() - x * Other.GetX() - y * Other.GetY() - z * Other.GetZ();
		X = x * Other.GetW() + w * Other.GetX() + y * Other.GetZ() - z * Other.GetY();
		Y = y * Other.GetW() + w * Other.GetY() + z * Other.GetX() - x * Other.GetZ();
		Z = z * Other.GetW() + w * Other.GetZ() + x * Other.GetY() - y * Other.GetX();
		//Return the quaternion
		return Quaternion(X, Y, Z, W);
	}

	Quaternion Quaternion::Mult(Vector3f & Other)
	{
		//Get new quaternion valyes
		float X, Y, Z, W;
		//Calculate each component
		W = -x * Other.GetX() - y * Other.GetY() - z * Other.GetZ();
		X = w * Other.GetX() + y * Other.GetZ() - z * Other.GetY();
		Y = w * Other.GetY() + z * Other.GetX() - x * Other.GetZ();
		Z = w* Other.GetZ() + x * Other.GetY() - y * Other.GetX();
		//Return the quaternion
		return Quaternion(X, Y, Z, W);
	}

	Quaternion Quaternion::Mult(float & Other)
	{
		//Calculate each component
		w = w * Other - x * Other - y * Other - z * Other;
		x = x * Other + w * Other + y * Other - z * Other;
		y = y * Other + w * Other + z * Other - x * Other;
		z = z * Other + w * Other + x * Other - y * Other;
		//Return the quaternion
		return Quaternion(z, y, z, w);
	}

	Matrix4f Quaternion::ToRotationMatrix()
	{
		//Get forward, up and right directions, based on the quaternion
		Vector3f Forward = Vector3f(2.0f * (x*z - w*y), 2.0f * (y*z + w*x), 1.0f - 2.0f * (x*x + y*y));
		Vector3f Up = Vector3f(2.0f * (x*y + w*z), 1.0f - 2.0f * (x*x + z*z), 2.0f * (y*z - w*x));
		Vector3f Right = Vector3f(1.0f - 2.0f * (y*y + z*z), 2.0f * (x*y - w*z), 2.0f * (x*z + w*y));
		//Create matrix
		Matrix4f RotMat;
		//Init rotation matrix
		RotMat.InitRotation(Forward, Up, Right);
		//Return the rotation matrix
		return RotMat;
	}
}