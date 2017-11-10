#pragma once

namespace D3DEngine
{
	class Attenuation
	{
	public:
		Attenuation();
		Attenuation(float Constant, float Linear, float Exponent);
		~Attenuation();

		//Getters
		inline float GetConstant() { return m_Constant; }
		inline float GetLinear() { return m_Linear; }
		inline float GetExponent() { return m_Exponent; }
		//Setters
		inline void SetConstant(float Constant) { m_Constant = Constant; }
		inline void SetLinear(float Linear) { m_Linear = Linear; }
		inline void SetExponent(float Exponent) { m_Exponent = Exponent; }

	private:
		float m_Constant;
		float m_Linear;
		float m_Exponent;
	};
}