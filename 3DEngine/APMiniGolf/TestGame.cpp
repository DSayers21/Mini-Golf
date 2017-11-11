#include "TestGame.h"

TestGame::TestGame()
{

}

TestGame::~TestGame()
{

}

void TestGame::Init()
{
	float FieldDepth = 10.0f;
	float FieldWidth = 10.0f;

	D3DEngine::Vert Vertices[] = {
		D3DEngine::Vert(D3DEngine::Vector3f(-FieldWidth, 0.0f, -FieldDepth), D3DEngine::Vector2f(0.0f,0.0f)),
		D3DEngine::Vert(D3DEngine::Vector3f(-FieldWidth, 0.0f, FieldDepth * 3), D3DEngine::Vector2f(0.0f,1.0f)),
		D3DEngine::Vert(D3DEngine::Vector3f(FieldWidth * 3, 0.0f, -FieldDepth), D3DEngine::Vector2f(1.0f,0.0f)),
		D3DEngine::Vert(D3DEngine::Vector3f(FieldWidth * 3, 0.0f, FieldDepth * 3), D3DEngine::Vector2f(1.0f,1.0f)),
	};
	int Indices[] = { 0, 1, 2 ,2, 1, 3 };

	D3DEngine::Mesh* mesh = new D3DEngine::Mesh(Vertices, 4, Indices, 6, true);
	D3DEngine::Material* material = new D3DEngine::Material(D3DEngine::Texture("./Textures/Test.png"), D3DEngine::Vector3f(0, 0, 0), 1, 8);

	D3DEngine::GameObject* PlaneObject = new D3DEngine::GameObject();
	D3DEngine::MeshRenderer* meshRenderer = new D3DEngine::MeshRenderer(mesh, material);
	PlaneObject->AddComponent(meshRenderer);
	PlaneObject->GetTransform()->SetPosition(-2, -1, 5);

	D3DEngine::GameObject* DirectionalLightObject = new D3DEngine::GameObject();
	D3DEngine::DirectionalLight* directionalLight = new D3DEngine::DirectionalLight(D3DEngine::Vector3f(0,0,1), 0.4f, D3DEngine::Vector3f(1,1,1));
	DirectionalLightObject->AddComponent(directionalLight);

	D3DEngine::GameObject* PointLightObject = new D3DEngine::GameObject();
	PointLightObject->AddComponent(new D3DEngine::PointLight(D3DEngine::Vector3f(0, 1, 0), 0.9f, D3DEngine::Attenuation(0, 0, 1), D3DEngine::Vector3f(5, 0, 5), 100));

	D3DEngine::GameObject* SpotLightObject = new D3DEngine::GameObject();
	SpotLightObject->AddComponent(new D3DEngine::SpotLight(D3DEngine::Vector3f(0, 1, 1),12.0f, 
		D3DEngine::Attenuation(0, 0, 1), D3DEngine::Vector3f(7, 0, 7), 100, D3DEngine::Vector3f(1, 0, 0), 0.7));

	m_RootObject->AddChild(PlaneObject);
	m_RootObject->AddChild(DirectionalLightObject);
	m_RootObject->AddChild(PointLightObject);
	m_RootObject->AddChild(SpotLightObject);
}

void TestGame::Input(D3DEngine::Input& input, float Delta)
{
	input.Update();
	//Do Camera
	//m_Camera->DoInput(*m_Input, *m_Time);

	int MX = input.GetMousePos().GetX();
	int MY = (input.GetMousePos().GetY());
	if (input.GetMouseDown(D3DEngine::MOUSE_LEFT_BUTTON))
	{
		std::cout << "Mouse Pressed Left at:: (" << MX << "," << MY << ")" << std::endl;
	}
	//m_RootObject->Input();
}