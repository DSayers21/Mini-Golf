#include "MainGame.h"

MainGame::MainGame(D3DEngine::Window* window, D3DEngine::Time* time)
{
	m_Window = window;
	m_Camera = new D3DEngine::Camera(window);
	m_Time = time;
	m_Input = new D3DEngine::Input(m_Window);
	
	m_BShader.SetAmbientLight(D3DEngine::Vector3f(1,1,1));
	//m_Mesh = D3DEngine::ResourceLoader::LoadMesh("./Models/Tower.obj");

	m_Material = new D3DEngine::Material(D3DEngine::Texture("./Textures/Test.png"), D3DEngine::Vector3f(0,0,0));
	D3DEngine::Vert Vertices[] = {
		D3DEngine::Vert(D3DEngine::Vector3f(-1,-1,0), D3DEngine::Vector2f(0.0f,0.0f)),
		D3DEngine::Vert(D3DEngine::Vector3f(0,1,0), D3DEngine::Vector2f(1.0f,0.0f)),
		D3DEngine::Vert(D3DEngine::Vector3f(1,-1,0), D3DEngine::Vector2f(1.0f,1.0f)),
		D3DEngine::Vert(D3DEngine::Vector3f(0,-1,1), D3DEngine::Vector2f(0.0f,1.0f)),
	};
	int Indices[] = { 3,1,0,2,1,3,0,1,2,0,2,3 };
	m_Mesh.AddVertices(Vertices, 4, Indices, 12);
	//Transform
	m_Transform.SetProjection(70.0f, m_Window->GetWidth(), m_Window->GetHeight(), 0.1f, 1000.0f);
	m_Transform.SetCamera(m_Camera);
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
	Temp += 0.0001f;
	float TempAmount = sin(Temp);
	m_Transform.SetTranslation(TempAmount, 0, 5);
	m_Transform.SetRotation(TempAmount * 180, TempAmount * 180, TempAmount * 180);
	m_Transform.SetScaling(.4, .4, .4);
}

void MainGame::Draw()
{
	m_BShader.Bind();
	m_BShader.UpdateUniforms(m_Transform.GetTransformation(), m_Transform.GetProjectedTransformation(), *m_Material);
	m_Mesh.Draw();
}