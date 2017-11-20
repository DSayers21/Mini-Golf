#include "PhysicsObjectComponent.h"

namespace D3DEngine
{
	PhysicsObjectComponent::PhysicsObjectComponent(PhysicsObject* object) :
		m_PhysicsObject(object)
	{
	}

	PhysicsObjectComponent::~PhysicsObjectComponent()
	{
	}

	void PhysicsObjectComponent::Input(GetInput * input, float Delta)
	{
		if (input->GetKeyDown(KEY_SPACE))
		{
			float rndX = 0 + (1 - 0) * rand() / ((double)RAND_MAX);
			float rndY = 0 + (1 - 0) * rand() / ((double)RAND_MAX);
			float rndZ = 0 + (1 - 0) * rand() / ((double)RAND_MAX);
			m_PhysicsObject->ApplyImpulse(Vector3f(rndX, 0, rndZ));
		}
	}

	void PhysicsObjectComponent::Update(float Delta)
	{
		//Set Position
		GetTransform()->SetPosition(m_PhysicsObject->GetPosition());
	}
}