#include "TestGame.h"

TestGame::TestGame()
{

}

TestGame::~TestGame()
{

}

void TestGame::Init()
{
	m_Camera = new D3DEngine::Camera(m_Window);
	m_RootObject = new D3DEngine::GameObject(m_Camera);
	//

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

	D3DEngine::GameObject* PlaneObject = new D3DEngine::GameObject(m_Camera);
	MeshRenderer* meshRenderer = new MeshRenderer(mesh, material);
	PlaneObject->AddComponent(meshRenderer);
	PlaneObject->GetTransform()->SetTranslation(-2, -1, 5);
	m_RootObject->AddChild(PlaneObject);
	
}

void TestGame::Input()
{
	m_Input->Update();
	//Do Camera
	m_Camera->DoInput(*m_Input, *m_Time);

	int MX = (m_Input->GetMousePos().GetX());
	int MY = (m_Input->GetMousePos().GetY());
	if (m_Input->GetMouseDown(D3DEngine::MOUSE_LEFT_BUTTON))
	{
		std::cout << "Mouse Pressed Left at:: (" << MX << "," << MY << ")" << std::endl;
	}
	m_RootObject->Input();
}