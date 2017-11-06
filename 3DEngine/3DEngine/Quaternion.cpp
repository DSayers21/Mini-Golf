#include "Quaternion.h"

namespace D3DEngine
{
	Quaternion::Quaternion()
	{
		Quaternion(0.0,0.0,0.0,0.0);
	}

	Quaternion::Quaternion(float X, float Y, float Z, float W) :
		x(X), y(Y), z(Z), w(W)
	{

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
}