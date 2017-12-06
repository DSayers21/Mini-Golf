#include "PhysicsEngineComponent.h"

namespace D3DEngine
{
	PhysicsEngineComponent::PhysicsEngineComponent(PhysicsEngine* engine) :
		m_PhysicsEngine(engine)
	{
	}


	PhysicsEngineComponent::~PhysicsEngineComponent()
	{
		std::cerr << "Destructor: Physics Engine Component" << std::endl;
	}

	void PhysicsEngineComponent::Update(float Delta)
	{
		m_PhysicsEngine->Simulate(Delta);
		m_PhysicsEngine->HandleCollisions();
	}
}