/*------------------------------------------------------------------------
  Header for Some Vector Classes
  ------------------------------------------------------------------------*/
#ifndef vecmat_h_included
#define vecmat_h_included

#include <math.h>

namespace D3DEngine
{
	/*------------------------------------------------------------------------
		vec2 : 2d Vector
	  ------------------------------------------------------------------------*/
	class vec2
	{
	public:
		//Constructors
		vec2();
		vec2(double x, double y);
		vec2(double x);
		//End - Constructor

		//Operator Overloads
		double operator()(int x) const { return m_elem[x]; }
		double &operator()(int x) { return m_elem[x]; }
		vec2 operator *(const double x) const;
		vec2 operator /(const double x) const;
		vec2 operator +(const vec2 &x) const;
		vec2 operator -(const vec2 &x) const;
		vec2 operator -() const;
		vec2 &operator *=(const double x);
		vec2 &operator /=(const double x);
		vec2 &operator +=(const vec2 &x);
		vec2 &operator -=(const vec2 &x);
		bool operator ==(const vec2 &x) const { return((m_elem[0] == x.m_elem[0]) && (m_elem[1] == x.m_elem[1])); }
		//End - Operator Overloads

		//Functions
		double Magnitude(void) const { return(sqrt((m_elem[0] * m_elem[0]) + (m_elem[1] * m_elem[1]))); }
		double Magnitude2(void) const { return((m_elem[0] * m_elem[0]) + (m_elem[1] * m_elem[1])); }
		double Normalise(void);
		vec2 Normalised(void) const;
		double Dot(const vec2 &x) const { return ((m_elem[0] * x.m_elem[0]) + (m_elem[1] * x.m_elem[1])); }
		//End - Functions
	
		//Public Members
		double 	m_elem[2];
	
	};

	/*------------------------------------------------------------------------
		vec3 : 3d Vector
	  ------------------------------------------------------------------------*/
	class vec3
	{
	public:
		//Constructors
		vec3();
		vec3(double x, double y, double z);
		vec3(double x);
		//End - Constructors

		//Operator Overloads
		double operator()(int x) const { return m_elem[x]; }
		double &operator()(int x) { return m_elem[x]; }

		vec3 operator *(const double x) const;
		vec3 operator /(const double x) const;
		vec3 operator +(const vec3 &x) const;
		vec3 operator -(const vec3 &x) const;
		vec3 &operator *=(const double x);
		vec3 &operator /=(const double x);
		vec3 &operator +=(const vec3 &x);
		vec3 &operator -=(const vec3 &x);
		//End - Operator Overloads

		//Functions
		double Magnitude(void) const { return(sqrt((m_elem[0] * m_elem[0]) + (m_elem[1] * m_elem[1]) + (m_elem[2] * m_elem[2]))); }
		double Magnitude2(void) const { return((m_elem[0] * m_elem[0]) + (m_elem[1] * m_elem[1]) + (m_elem[2] * m_elem[2])); }
		double Normalise(void);
		vec3 Normalised(void) const;

		double Dot(const vec3 &x) const { return ((m_elem[0] * x.m_elem[0]) + (m_elem[1] * x.m_elem[1]) + (m_elem[2] * x.m_elem[2])); }
		vec3 Cross(const vec3 &x) const;
		//End - Functions

		//Public Members
		double 	m_elem[3];
	};
}
#endif