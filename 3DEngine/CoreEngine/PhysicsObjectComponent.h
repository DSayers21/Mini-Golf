#pragma once

#include "GameComponent.h"
#include "PhysicsObject.h"

namespace D3DEngine
{
	class PhysicsObjectComponent : public GameComponent
	{
	public:
		PhysicsObjectComponent(const PhysicsObject* engine);
		~PhysicsObjectComponent();

		virtual void Update(float Delta);

	private:
		const PhysicsObject* m_PhysicsObject;
	};
}