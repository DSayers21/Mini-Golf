#include "PhysicsObjectComponent.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	PhysicsObjectComponent::PhysicsObjectComponent(PhysicsObject* object, bool Control) :
		m_PhysicsObject(object), m_Control(Control)
	{
	}

	PhysicsObjectComponent::~PhysicsObjectComponent()
	{
		std::cerr << "Destructor: Physics Object Component" << std::endl;
		delete m_PhysicsObject;
	}

	void PhysicsObjectComponent::Input(GetInput * input, float Delta)
	{

	}

	void PhysicsObjectComponent::Update(float Delta)
	{
		//Set Position
		GetTransform()->SetPosition(m_PhysicsObject->GetPosition());
	}
}