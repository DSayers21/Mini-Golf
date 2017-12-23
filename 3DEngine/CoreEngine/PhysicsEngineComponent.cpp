//Includes
#include "PhysicsEngineComponent.h"

namespace D3DEngine
{
	PhysicsEngineComponent::PhysicsEngineComponent(PhysicsEngine* engine) :
		m_PhysicsEngine(engine)
	{
		//Empty
	}


	PhysicsEngineComponent::~PhysicsEngineComponent()
	{
		//Display Message
		std::cerr << "Destructor: Physics Engine Component" << std::endl;
	}

	void PhysicsEngineComponent::Update(float Delta)
	{
		//Simulate the physics engine
		m_PhysicsEngine->Simulate(Delta);
		//Handle collisions for all physics objects in the engine
		m_PhysicsEngine->HandleCollisions();
	}
}