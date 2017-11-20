#pragma once

#include "GameComponent.h"
#include "PhysicsObject.h"

namespace D3DEngine
{
	class PhysicsObjectComponent : public GameComponent
	{
	public:
		PhysicsObjectComponent(PhysicsObject* engine);
		~PhysicsObjectComponent();

		virtual void Input(GetInput* input, float Delta);
		virtual void Update(float Delta);

	private:
		PhysicsObject* m_PhysicsObject;
	};
}