#pragma once

//Includes
#include "MathBasics.h"
#include "Matrix4f.h"
#include "Vector3f.h"

namespace D3DEngine
{
	class Quaternion
	{
	public:
		//Constructors
		Quaternion();
		Quaternion(float X, float Y, float Z, float W);
		Quaternion(Vector3f Axis, float Angle);
		//Destructor
		~Quaternion();

		//Init rotation
		Quaternion* Quaternion::InitRotation(Vector3f Axis, float Angle);

		//Normalise the quaternion
		Quaternion Normalise();
		//Conjugate the quaternion
		Quaternion Conjugate();
		//Operators
		Quaternion Mult(Quaternion& Other);
		Quaternion Mult(Vector3f& Other);
		Quaternion Mult(float& Other);
		Matrix4f ToRotationMatrix();
		inline bool operator==(const Quaternion& Other) { return ((x == Other.x) && (y == Other.y) && (z == Other.z) && (w == Other.w)); }
		inline bool operator!=(const Quaternion& Other) { return ((x != Other.GetX()) && (y != Other.GetY()) && (z != Other.GetZ()) && (w != Other.GetW())); }

		//Get vector directions from the quaternion
		inline Vector3f GetBack()	 { return Vector3f(0, 0, -1).Rotate(*this); }
		inline Vector3f GetUp()		 { return Vector3f(0, 1, 0).Rotate(*this);  }
		inline Vector3f GetDown()	 { return Vector3f(0, -1, 0).Rotate(*this); }
		inline Vector3f GetRight()	 { return Vector3f(1, 0, 0).Rotate(*this);  }
		inline Vector3f GetLeft()	 { return Vector3f(-1, 0, 0).Rotate(*this); }
		inline Vector3f GetForward() { return Vector3f(0, 0, 1).Rotate(*this);  }

		//Getters
		inline float Length() { return (float)sqrt(x*x + y*y + z*z + w*w); }
		inline float GetX() const { return x; }
		inline float GetY() const { return y; }
		inline float GetZ() const { return z; }
		inline float GetW() const { return w; }

		//Setters
		inline void SetX(float X) { x = X; }
		inline void SetY(float Y) { y = Y; }
		inline void SetZ(float Z) { z = Z; }
		inline void SetW(float W) { w = W; }
		inline void Set(Quaternion& Other) { x = Other.GetX(); y = Other.GetY(); z = Other.GetZ(); w = Other.GetW(); };

	private:
		//Quaternion information
		float x;
		float y;
		float z;
		float w;
	};
}