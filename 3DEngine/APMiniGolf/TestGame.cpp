#include "TestGame.h"
#include "Quaternion.h"
#include "MathBasics.h"
#include <string>

TestGame::TestGame()
{

}

TestGame::~TestGame()
{

}

void TestGame::Init(D3DEngine::RenderEngine* renderEngine)
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
	D3DEngine::Vert Vertices2[] = {
		D3DEngine::Vert(D3DEngine::Vector3f(-FieldWidth / 10, 0.0f, -FieldDepth / 10), D3DEngine::Vector2f(0.0f,0.0f)),
		D3DEngine::Vert(D3DEngine::Vector3f(-FieldWidth/10, 0.0f, FieldDepth / 10 * 3), D3DEngine::Vector2f(0.0f,1.0f)),
		D3DEngine::Vert(D3DEngine::Vector3f(FieldWidth / 10 * 3, 0.0f, -FieldDepth / 10), D3DEngine::Vector2f(1.0f,0.0f)),
		D3DEngine::Vert(D3DEngine::Vector3f(FieldWidth / 10 * 3, 0.0f, FieldDepth / 10 * 3), D3DEngine::Vector2f(1.0f,1.0f)),
	};
	int Indices2[] = { 0, 1, 2 ,2, 1, 3 };
	D3DEngine::Mesh* mesh2 = new D3DEngine::Mesh(Vertices2, 4, Indices2, 6, true);
	
	D3DEngine::Material* material = new D3DEngine::Material();
	material->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/Test.png"));
	material->AddFloat("SpecularIntensity", 1);
	material->AddFloat("SpecularExponent", 8);

	D3DEngine::Material* material2 = new D3DEngine::Material();
	material2->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/Bricks.jpg"));
	material2->AddFloat("SpecularIntensity", 1);
	material2->AddFloat("SpecularExponent", 8);


	D3DEngine::Mesh* MonkeyMesh = new D3DEngine::Mesh("./Models/Monkey.obj", m_MeshList);
	D3DEngine::Mesh* MonkeyMesh2 = new D3DEngine::Mesh("./Models/Monkey.obj", m_MeshList);

	D3DEngine::GameObject* PlaneObject = new D3DEngine::GameObject();
	D3DEngine::MeshRenderer* meshRenderer = new D3DEngine::MeshRenderer(mesh, material);
	PlaneObject->AddComponent(meshRenderer);
	PlaneObject->GetTransform()->GetPosition()->Set(-2, -1, 5);

	D3DEngine::GameObject* DirectionalLightObject = new D3DEngine::GameObject();
	D3DEngine::DirectionalLight* directionalLight = new D3DEngine::DirectionalLight(renderEngine->GetShaderList(), D3DEngine::Vector3f(0,0,1), 0.9f);
	DirectionalLightObject->AddComponent(directionalLight);
	DirectionalLightObject->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(1, 1, 1), TO_RADIANS(-45.0f)));


	D3DEngine::GameObject* PointLightObject = new D3DEngine::GameObject();
	PointLightObject->AddComponent(new D3DEngine::PointLight(renderEngine->GetShaderList(), D3DEngine::Vector3f(0, 1, 0), 0.9f, D3DEngine::Attenuation(0, 0, 1)));
	PointLightObject->GetTransform()->GetPosition()->Set(6, 0,12);

	D3DEngine::GameObject* PointLightObject2 = new D3DEngine::GameObject();
	PointLightObject2->AddComponent(new D3DEngine::PointLight(renderEngine->GetShaderList(), D3DEngine::Vector3f(1, 0, 0), 0.9f, D3DEngine::Attenuation(0, 0, 1)));
	PointLightObject2->GetTransform()->GetPosition()->Set(12, 0, 12);

	D3DEngine::GameObject* SpotLightObject = new D3DEngine::GameObject();
	SpotLightObject->AddComponent(new D3DEngine::SpotLight(renderEngine->GetShaderList(), D3DEngine::Vector3f(0, 1, 1),12.0f,
		D3DEngine::Attenuation(0, 0, 1), 0.7));
	SpotLightObject->GetTransform()->GetPosition()->Set(5, 0, 5);
	SpotLightObject->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(0, 1, 0), TO_RADIANS(90.0f)));

	D3DEngine::GameObject* CameraObject = new D3DEngine::GameObject();
	CameraObject->AddComponent(new D3DEngine::Camera(TO_RADIANS(90.0f), 800/600, 0.01f, 1000.0f));
	CameraObject->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(0, 1, 0), TO_RADIANS(140.0f)));
	CameraObject->AddComponent(new D3DEngine::FreeLook());


	

	D3DEngine::GameObject* testMesh2 = new D3DEngine::GameObject();
	testMesh2->AddComponent(new D3DEngine::MeshRenderer(mesh2, material));
	testMesh2->GetTransform()->GetPosition()->Set(0, 3, 5);

	D3DEngine::GameObject* testMesh3 = new D3DEngine::GameObject();
	testMesh3->AddComponent(new D3DEngine::MeshRenderer(MonkeyMesh, material));
	testMesh3->GetTransform()->GetPosition()->Set(12, 0, 12);
	


	D3DEngine::PhysicsEngine* m_PhysicsEngine = new D3DEngine::PhysicsEngine();
	m_PhysicsEngine->AddObject(D3DEngine::PhysicsObject(D3DEngine::Vector3f(0.0f, 0.0f, 0.0f), D3DEngine::Vector3f(1.0f, 1.0f, 0.0f)));
	m_PhysicsEngine->AddObject(D3DEngine::PhysicsObject(D3DEngine::Vector3f(20.0f, 30.0f, -9.0f), D3DEngine::Vector3f(-0.8f, -0.9f, 0.7f)));

	D3DEngine::PhysicsEngineComponent* m_PhysicsEngineComponent = new D3DEngine::PhysicsEngineComponent(*m_PhysicsEngine);

	D3DEngine::GameObject* testMesh1 = new D3DEngine::GameObject();
	testMesh1->AddComponent(new D3DEngine::MeshRenderer(MonkeyMesh2, material));
	testMesh1->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine().GetObject(1)));

	D3DEngine::GameObject* PhysicsEngineObj = new D3DEngine::GameObject();
	PhysicsEngineObj->AddComponent(m_PhysicsEngineComponent);
	
	
	AddObject(testMesh2);
	AddObject(CameraObject);
	AddObject(PlaneObject);
	AddObject(PhysicsEngineObj);
	AddObject(DirectionalLightObject);
	AddObject(PointLightObject);
	AddObject(PointLightObject2);
	AddObject(SpotLightObject);
	AddObject(testMesh1);
	AddObject(testMesh3);
}

void TestGame::Input(D3DEngine::GetInput* input, float Delta)
{
	input->Update();

	int MX = input->GetMousePos().GetX();
	int MY = (input->GetMousePos().GetY());
	if (input->GetMouseDown(D3DEngine::MOUSE_LEFT_BUTTON))
	{
		std::cout << "Mouse Pressed Left at:: (" << MX << "," << MY << ")" << std::endl;
	}
	m_RootObject->Input(input, Delta);
}