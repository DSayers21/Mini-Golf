#include "Vecmath.h"

namespace D3DEngine
{
	//Vec 2------------------------------------------------------------------------
	vec2::vec2() 
	{
		//Empty
	}

	vec2::vec2(double x, double y) 
	{ 
		m_elem[0] = x; 
		m_elem[1] = y; 
	}

	vec2::vec2(double x) 
	{ 
		m_elem[0] = m_elem[1] = x; 
	}

	vec2 vec2::operator *(const double x) const 
	{ 
		vec2 res(*this);
		res.m_elem[0] *= x; 
		res.m_elem[1] *= x; 
		return res; 
	}

	vec2 vec2::operator /(const double x) const 
	{ 
		vec2 res(*this); 
		res.m_elem[0] /= x; 
		res.m_elem[1] /= x; 
		return res; 
	}

	vec2 vec2::operator +(const vec2 &x) const 
	{ 
		vec2 res(*this); 
		res.m_elem[0] += x.m_elem[0]; 
		res.m_elem[1] += x.m_elem[1]; 
		return res; 
	}

	vec2 vec2::operator -(const vec2 &x) const
	{ 
		vec2 res(*this); 
		res.m_elem[0] -= x.m_elem[0]; 
		res.m_elem[1] -= x.m_elem[1]; 
		return res; 
	}

	vec2 vec2::operator -() const 
	{ 
		vec2 res(*this); 
		res.m_elem[0] = -res.m_elem[0]; 
		res.m_elem[1] = -res.m_elem[1]; 
		return res; 
	}

	vec2 &vec2::operator *=(const double x) 
	{ 
		m_elem[0] *= x;
		m_elem[1] *= x; 
		return (*this); 
	}

	vec2 &vec2::operator /=(const double x) 
	{
		m_elem[0] /= x; 
		m_elem[1] /= x; 
		return (*this); 
	}

	vec2 &vec2::operator +=(const vec2 &x) 
	{ 
		m_elem[0] += x.m_elem[0]; 
		m_elem[1] += x.m_elem[1]; 
		return (*this); 
	}

	vec2 &vec2::operator -=(const vec2 &x) 
	{
		m_elem[0] -= x.m_elem[0]; 
		m_elem[1] -= x.m_elem[1]; 
		return (*this); 
	}

	double vec2::Normalise(void) 
	{ 
		double x = Magnitude(); 
		m_elem[0] /= x; 
		m_elem[1] /= x; 
		return x; 
	}

	vec2 vec2::Normalised(void) const 
	{ 
		vec2 res(*this); 
		res.Normalise(); 
		return res; 
	}

	//Vec 3------------------------------------------------------------------------
	vec3::vec3() 
	{
		//Empty
	}
	
	vec3::vec3(double x, double y, double z) 
	{ 
		m_elem[0] = x; 
		m_elem[1] = y; 
		m_elem[2] = z; 
	}
	
	vec3::vec3(double x) 
	{ 
		m_elem[0] = m_elem[1] = m_elem[2] = x; 
	}

	vec3 vec3::operator *(const double x) const 
	{ 
		vec3 res(*this); 
		res.m_elem[0] *= x; 
		res.m_elem[1] *= x; 
		res.m_elem[2] *= x; 
		return res; 
	}
	
	vec3 vec3::operator /(const double x) const 
	{ 
		vec3 res(*this);
		res.m_elem[0] /= x; 
		res.m_elem[1] /= x; 
		res.m_elem[2] /= x; 
		return res; 
	}
	
	vec3 vec3::operator +(const vec3 &x) const
	{ 
		vec3 res(*this); 
		res.m_elem[0] += x.m_elem[0]; 
		res.m_elem[1] += x.m_elem[1]; 
		res.m_elem[2] += x.m_elem[2]; 
		return res; 
	}
	
	vec3 vec3::operator -(const vec3 &x) const 
	{ 
		vec3 res(*this); 
		res.m_elem[0] -= x.m_elem[0]; 
		res.m_elem[1] -= x.m_elem[1]; 
		res.m_elem[2] -= x.m_elem[2]; 
		return res; 
	}
	
	vec3 &vec3::operator *=(const double x) 
	{ 
		m_elem[0] *= x; 
		m_elem[1] *= x; 
		m_elem[2] *= x; 
		return (*this); 
	}
	
	vec3 &vec3::operator /=(const double x) 
	{ 
		m_elem[0] /= x; 
		m_elem[1] /= x; 
		m_elem[2] /= x; 
		return (*this); 
	}
	
	vec3 &vec3::operator +=(const vec3 &x) 
	{
		m_elem[0] += x.m_elem[0]; 
		m_elem[1] += x.m_elem[1]; 
		m_elem[2] += x.m_elem[2]; 
		return (*this); 
	}
	
	vec3 &vec3::operator -=(const vec3 &x)
	{ 
		m_elem[0] -= x.m_elem[0]; 
		m_elem[1] -= x.m_elem[1]; 
		m_elem[2] -= x.m_elem[2]; 
		return (*this); 
	}
	
	double vec3::Normalise(void) 
	{ 
		double x = Magnitude(); 
		m_elem[0] /= x; 
		m_elem[1] /= x; 
		m_elem[2] /= x; 
		return x; 
	}
	
	vec3 vec3::Normalised(void) const 
	{ 
		vec3 res(*this); 
		res.Normalise(); 
		return res;
	}

	vec3 vec3::Cross(const vec3 &x) const
	{
		vec3 res;
		res.m_elem[0] = m_elem[1] * x.m_elem[2] - m_elem[2] * x.m_elem[1];
		res.m_elem[1] = m_elem[2] * x.m_elem[0] - m_elem[0] * x.m_elem[2];
		res.m_elem[2] = m_elem[0] * x.m_elem[1] - m_elem[1] * x.m_elem[0];
		return res;
	}
}