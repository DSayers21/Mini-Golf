#include "PhysicsEngineComponent.h"

namespace D3DEngine
{
	PhysicsEngineComponent::PhysicsEngineComponent(PhysicsEngine* engine) :
		m_PhysicsEngine(engine)
	{
	}


	PhysicsEngineComponent::~PhysicsEngineComponent()
	{
	}

	void PhysicsEngineComponent::Update(float Delta)
	{
		m_PhysicsEngine->Simulate(Delta);
		m_PhysicsEngine->HandleCollisions();
	}
}