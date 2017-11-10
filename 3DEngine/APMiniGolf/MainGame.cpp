#include "MainGame.h"

MainGame::MainGame(D3DEngine::Window* window, D3DEngine::Time* time)
{
	m_Window = window;
	m_Camera = new D3DEngine::Camera(window);
	m_Time = time;
	m_Input = new D3DEngine::Input(m_Window);
	
	//m_Mesh = *D3DEngine::ResourceLoader::LoadMesh("./Models/Cube.obj");

	m_Material = new D3DEngine::Material(D3DEngine::Texture("./Textures/Test.png"), D3DEngine::Vector3f(0,0,0), 1, 8);
	//D3DEngine::Vert Vertices[] = {
	//	D3DEngine::Vert(D3DEngine::Vector3f(-1,-1,0), D3DEngine::Vector2f(0.0f,0.0f)),
	//	D3DEngine::Vert(D3DEngine::Vector3f(0,1,0), D3DEngine::Vector2f(1.0f,0.0f)),
	//	D3DEngine::Vert(D3DEngine::Vector3f(1,-1,0), D3DEngine::Vector2f(1.0f,1.0f)),
	//	D3DEngine::Vert(D3DEngine::Vector3f(0,-1,1), D3DEngine::Vector2f(0.0f,1.0f)),
	//};
	//int Indices[] = { 3,1,0,2,1,3,0,1,2,0,2,3 };

	//D3DEngine::Vert Vertices[] = {
	//	D3DEngine::Vert(D3DEngine::Vector3f(-1,-1,0.5773), D3DEngine::Vector2f(0.0f,0.0f)),
	//	D3DEngine::Vert(D3DEngine::Vector3f(0,-1,-1.15475), D3DEngine::Vector2f(0.5f,0.0f)),
	//	D3DEngine::Vert(D3DEngine::Vector3f(1,-1,0.5773), D3DEngine::Vector2f(1.0f,1.0f)),
	//	D3DEngine::Vert(D3DEngine::Vector3f(0,1, 0), D3DEngine::Vector2f(0.5f,1.0f)),
	//};
	//int Indices[] = { 0, 3, 1 ,1, 3, 2, 2, 3, 0, 1, 2, 0};
	float FieldDepth = 10.0f;
	float FieldWidth = 10.0f;

	D3DEngine::Vert Vertices[] = {
		D3DEngine::Vert(D3DEngine::Vector3f(-FieldWidth, 0.0f, -FieldDepth), D3DEngine::Vector2f(0.0f,0.0f)),
		D3DEngine::Vert(D3DEngine::Vector3f(-FieldWidth, 0.0f, FieldDepth * 3), D3DEngine::Vector2f(0.0f,1.0f)),
		D3DEngine::Vert(D3DEngine::Vector3f(FieldWidth * 3, 0.0f, -FieldDepth), D3DEngine::Vector2f(1.0f,0.0f)),
		D3DEngine::Vert(D3DEngine::Vector3f(FieldWidth * 3, 0.0f, FieldDepth * 3), D3DEngine::Vector2f(1.0f,1.0f)),
	};
	int Indices[] = { 0, 1, 2 ,2, 1, 3 };

	m_Mesh = new D3DEngine::Mesh(Vertices, 4, Indices, 6, true);
	//Transform
	m_Transform.SetProjection(70.0f, m_Window->GetWidth(), m_Window->GetHeight(), 0.1f, 1000.0f);
	m_Transform.SetCamera(m_Camera);

	m_BShader.SetAmbientLight(D3DEngine::Vector3f(.1, .1, .1));
	m_BShader.SetTransform(&m_Transform);

	m_pLights = new D3DEngine::PointLight[2];
	m_pLights[0] = D3DEngine::PointLight(D3DEngine::BaseLight(D3DEngine::Vector3f(1, .5, 0), 0.8),D3DEngine::Attenuation(0, 0, 1),D3DEngine::Vector3f(-2, 0, 5), 6);
	m_pLights[1] = D3DEngine::PointLight(D3DEngine::BaseLight(D3DEngine::Vector3f(0, 0.5, 1), 0.8),D3DEngine::Attenuation(0, 0, 1),D3DEngine::Vector3f(2, 0, 7), 6);
	m_BShader.SetPointLight(m_pLights, 2);

	m_SpotLights = new D3DEngine::SpotLight[1];
	m_SpotLights[0] = D3DEngine::SpotLight(
		D3DEngine::PointLight(
			D3DEngine::BaseLight(
				D3DEngine::Vector3f(0, 1, 1),0.8),
			D3DEngine::Attenuation(0, 0, .1),
			D3DEngine::Vector3f(-2, 0, 5), 30), 
		D3DEngine::Vector3f(1, 1, 1), 0.7f);
	m_BShader.SetSpotLight(m_SpotLights, 1);
}

MainGame::~MainGame()
{
}

void MainGame::Input()
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
}

void MainGame::Update()
{
	m_Wave += 0.0001f;
	float TempAmount = sinf(m_Wave);
	m_Transform.SetTranslation(0, -1, 5);
	//m_Transform.SetRotation(0, TempAmount * 180, 0);
	m_Transform.SetScaling(.4, .4, .4);

	m_pLights[0].SetPosition(D3DEngine::Vector3f(TempAmount * 4, 0, 5));

	//Move Spot Light To Camera
	m_SpotLights[0].GetPointLight().SetPosition(m_Camera->GetPos());
	m_SpotLights[0].SetDirection(m_Camera->GetForward());
}

void MainGame::Draw()
{
	m_BShader.Bind();
	m_BShader.UpdateUniforms(m_Transform.GetTransformation(), m_Transform.GetProjectedTransformation(), *m_Material);
	m_Mesh->Draw();
}