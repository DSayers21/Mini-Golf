//Includes
#include "PhysicsObjectComponent.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	PhysicsObjectComponent::PhysicsObjectComponent(PhysicsObject* object, bool Control) :
		m_PhysicsObject(object)
	{
		//Empty
	}

	PhysicsObjectComponent::~PhysicsObjectComponent()
	{
		//Display Message
		std::cerr << "Destructor: Physics Object Component" << std::endl;
		//Delete the physics object
		delete m_PhysicsObject;
	}

	void PhysicsObjectComponent::Update(float Delta)
	{
		//Set Position
		GetTransform()->SetPosition(m_PhysicsObject->GetPosition());
	}
}