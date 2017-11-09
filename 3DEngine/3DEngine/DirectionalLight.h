#pragma once

#include "BaseLight.h"
#include "Vector3f.h"

namespace D3DEngine
{
	class DirectionalLight
	{
	public:
		DirectionalLight();
		DirectionalLight(BaseLight base, Vector3f direction);
		~DirectionalLight();

		//Getters
		BaseLight GetBaseLight() { return m_Base; }
		Vector3f GetDirection() { return m_Direction; }
		//Setters
		void SetBaseLight(BaseLight base) { m_Base= base; }
		void SetDirection(Vector3f direction) { m_Direction = direction; }

	private:
		BaseLight m_Base = BaseLight(Vector3f(0,0,0), 0);
		Vector3f m_Direction;
	};
}