
#include "Attenuation.h"

namespace D3DEngine
{
	Attenuation::Attenuation()
	{
		//Create default Attenuation
		*this = Attenuation(0,0,0);
	}

	Attenuation::Attenuation(float Constant, float Linear, float Exponent) :
		m_Constant(Constant), m_Linear(Linear), m_Exponent(Exponent)
	{
		//Empty
	}

	Attenuation::~Attenuation()
	{
		//Empty
	}
}