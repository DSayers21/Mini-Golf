#include "PhysicsObjectComponent.h"

namespace D3DEngine
{
	PhysicsObjectComponent::PhysicsObjectComponent(const PhysicsObject* object) :
		m_PhysicsObject(object)
	{
	}


	PhysicsObjectComponent::~PhysicsObjectComponent()
	{
	}

	void PhysicsObjectComponent::Update(float Delta)
	{
		//Set Position
		GetTransform()->SetPosition(m_PhysicsObject->GetPosition());
	}
}