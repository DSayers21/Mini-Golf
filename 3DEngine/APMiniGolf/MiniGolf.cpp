#include "MiniGolf.h"

#include "DirectionalLight.h"

MiniGolf::MiniGolf()
{
}


MiniGolf::~MiniGolf()
{
}

void MiniGolf::Init(D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine)
{
	D3DEngine::PhysicsEngineComponent* m_PhysicsEngineComponent = new D3DEngine::PhysicsEngineComponent(physicsEngine);
	physicsEngine->AddObject(D3DEngine::PhysicsObject(new D3DEngine::BoundingSphere(D3DEngine::Vector3f(0.0f, 0.4f, 0.0f), .2f), D3DEngine::Vector3f(0.0f, 0.0f, 0.0f)));

	D3DEngine::GameObject* CameraObject = new D3DEngine::GameObject();
	float Aspect = m_Window->GetWidth() / m_Window->GetHeight();
	CameraObject->AddComponent(new D3DEngine::Camera(TO_RADIANS(90.0f), Aspect, 0.01f, 1000.0f));
	CameraObject->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(0, 1, 0), TO_RADIANS(180.0f)));
	CameraObject->GetTransform()->SetPosition(D3DEngine::Vector3f(0.0f, 2.0f, 2.0f));
	CameraObject->AddComponent(new D3DEngine::FreeLook());

	//MaterialOne
	D3DEngine::Material* material = new D3DEngine::Material();
	material->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/GolfTexture.png"));
	material->AddFloat("SpecularIntensity", 1);
	material->AddFloat("SpecularExponent", 8);

	D3DEngine::Material* GolfBallMat = new D3DEngine::Material();
	GolfBallMat->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/GolfBallTexture.png"));
	GolfBallMat->AddFloat("SpecularIntensity", 1);
	GolfBallMat->AddFloat("SpecularExponent", 8);

	D3DEngine::Mesh* BallMesh = new D3DEngine::Mesh("./Models/Sphere.obj", m_MeshList);
	D3DEngine::Mesh* LevelMesh = new D3DEngine::Mesh("./Models/CourseBack.obj", m_MeshList);
	D3DEngine::Mesh* LevelMesh2 = new D3DEngine::Mesh("./Models/CourseBack2.obj", m_MeshList);

	D3DEngine::MeshResource* Test = m_MeshList->GetModel("./Models/CourseBack.obj");
	D3DEngine::MeshResource* Test2 = m_MeshList->GetModel("./Models/CourseBack2.obj");
	physicsEngine->AddAABBFromMesh(Test->GetVertices(), Test->GetVERTEXSIZE(), Test->GetIndices(), Test->GetINDEXSIZE());
	physicsEngine->AddAABBFromMesh(Test2->GetVertices(), Test2->GetVERTEXSIZE(), Test2->GetIndices(), Test2->GetINDEXSIZE());

	//Sphere
	D3DEngine::GameObject* Sphere = new D3DEngine::GameObject();
	D3DEngine::MeshRenderer* SphereMeshRenderer = new D3DEngine::MeshRenderer(BallMesh, GolfBallMat);
	Sphere->GetTransform()->SetScaling(D3DEngine::Vector3f(0.1f, 0.1f, 0.1f));
	Sphere->AddComponent(SphereMeshRenderer);
	Sphere->GetTransform()->SetPosition(D3DEngine::Vector3f(0.0f, 0.0f, 0.0f));
	Sphere->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(0), true));
	//End Sphere

	D3DEngine::GameObject* PlaneObject = new D3DEngine::GameObject();
	D3DEngine::MeshRenderer* PlaneMeshRenderer = new D3DEngine::MeshRenderer(LevelMesh, material);
	PlaneObject->AddComponent(PlaneMeshRenderer);
	PlaneObject->AddChild(CameraObject);
	PlaneObject->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(1)));
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(1).SetPosition(D3DEngine::Vector3f(0.0f, 0.0f, -3.0f));

	D3DEngine::GameObject* PlaneObject2 = new D3DEngine::GameObject();
	D3DEngine::MeshRenderer* PlaneMeshRenderer2 = new D3DEngine::MeshRenderer(LevelMesh2, material);
	PlaneObject2->AddComponent(PlaneMeshRenderer2);
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(2).SetPosition(D3DEngine::Vector3f(0.0f, 0.0f, 3.0f));
	PlaneObject2->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(2)));

	D3DEngine::GameObject* DirectionalLightObject = new D3DEngine::GameObject();
	D3DEngine::DirectionalLight* directionalLight = new D3DEngine::DirectionalLight(renderEngine->GetShaderList(), D3DEngine::Vector3f(1, 1, 1), 0.9f);
	DirectionalLightObject->AddComponent(directionalLight);
	DirectionalLightObject->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(1, 1, 1), TO_RADIANS(-45.0f)));

	D3DEngine::GameObject* DirectionalLightObject2 = new D3DEngine::GameObject();
	D3DEngine::DirectionalLight* directionalLight2 = new D3DEngine::DirectionalLight(renderEngine->GetShaderList(), D3DEngine::Vector3f(1, 1, 1), 0.9f);
	DirectionalLightObject2->AddComponent(directionalLight2);
	DirectionalLightObject2->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(1, 1, 1), TO_RADIANS(45.0f)));
	
	
	D3DEngine::GameObject* PhysicsEngineObj = new D3DEngine::GameObject();
	PhysicsEngineObj->AddComponent(m_PhysicsEngineComponent);
	
	AddObject(Sphere);
	AddObject(PhysicsEngineObj);
	AddObject(DirectionalLightObject);
	AddObject(DirectionalLightObject2);
	AddObject(PlaneObject);
	AddObject(PlaneObject2);
}

void MiniGolf::Input(D3DEngine::GetInput* input, float Delta)
{
	input->Update();

	m_RootObject->Input(input, Delta);
}