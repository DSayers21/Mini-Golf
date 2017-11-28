#include "Level.h"

void Level::TranslateHelper(float x, float z, int CurCount, D3DEngine::Vector3f tileCenter,
	D3DEngine::PhysicsEngineComponent* PhysicsEngineComponent)
{
	D3DEngine::Vector3f MyCenter = tileCenter;
	D3DEngine::Vector3f Pos = PhysicsEngineComponent->GetPhysicsEngine()->GetObject(CurCount).GetPosition();

	MyCenter.SetX(MyCenter.GetX() - x);
	MyCenter.SetZ(MyCenter.GetZ() - z);
	MyCenter.SetY(0.1f);

	PhysicsEngineComponent->GetPhysicsEngine()->GetObject(CurCount).SetPosition(MyCenter);
}

void Level::CreateHelper(int CurCount,
	D3DEngine::Mesh* mesh, D3DEngine::Material* material,
	D3DEngine::PhysicsEngineComponent* PhysicsEngineComponent, D3DEngine::GameObject* RootObject)
{
	m_GameObjects.push_back(new D3DEngine::GameObject());
	m_GameObjects.back()->AddComponent(new D3DEngine::MeshRenderer(mesh, material));
	m_GameObjects.back()->AddComponent(new D3DEngine::PhysicsObjectComponent(&PhysicsEngineComponent->GetPhysicsEngine()->GetObject(CurCount)));
}

Level::Level(int LevelData[7][7],
	D3DEngine::Window* Window, D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine,
	D3DEngine::GameObject* RootObject)
{
	D3DEngine::PhysicsEngineComponent* m_PhysicsEngineComponent = new D3DEngine::PhysicsEngineComponent(physicsEngine);
	D3DEngine::GameObject* PhysicsEngineObj = new D3DEngine::GameObject();
	PhysicsEngineObj->AddComponent(m_PhysicsEngineComponent);
	RootObject->AddChild(PhysicsEngineObj);

	D3DEngine::GameObject* CameraObject = new D3DEngine::GameObject();
	float Aspect = Window->GetWidth() / Window->GetHeight();
	CameraObject->AddComponent(new D3DEngine::Camera(TO_RADIANS(90.0f), Aspect, 0.01f, 1000.0f));
	CameraObject->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(1, 0, 0), TO_RADIANS(30.0f))); //Tilt Down
	CameraObject->GetTransform()->SetPosition(D3DEngine::Vector3f(-8.0f, 22.0f, 0.0f));
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

	D3DEngine::Material* SideMat = new D3DEngine::Material();
	SideMat->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/Wood.png"));
	SideMat->AddFloat("SpecularIntensity", 1);
	SideMat->AddFloat("SpecularExponent", 8);

	D3DEngine::Material* MetalMat = new D3DEngine::Material();
	MetalMat->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/Metal.png"));
	MetalMat->AddFloat("SpecularIntensity", 1);
	MetalMat->AddFloat("SpecularExponent", 8);

	D3DEngine::Mesh* BallMesh = new D3DEngine::Mesh("./Models/Ball.obj", m_MeshList);
	D3DEngine::Mesh* BackMesh = new D3DEngine::Mesh("./Models/CourseBack.obj", m_MeshList);
	D3DEngine::Mesh* SideMesh = new D3DEngine::Mesh("./Models/CourseSide.obj", m_MeshList);
	D3DEngine::Mesh* GroundTileMesh = new D3DEngine::Mesh("./Models/GroundTile.obj", m_MeshList);
	D3DEngine::Mesh* GolfClubMesh = new D3DEngine::Mesh("./Models/GolfClub.obj", m_MeshList);

	D3DEngine::MeshResource* BackRes = m_MeshList->GetModel("./Models/CourseBack.obj");
	D3DEngine::MeshResource* SideRes = m_MeshList->GetModel("./Models/CourseSide.obj");

	int PaddOffset = 1;

	int ObjectCount = 0;
	for (int i = PaddOffset; i < 5 + PaddOffset; i++)
		for (int j = PaddOffset; j <  5 + PaddOffset; j++)
			m_TileMap.insert(std::pair<std::string, Tile>(std::to_string(i) + std::to_string(j), Tile()));

	for (int i = PaddOffset; i < 5 + PaddOffset; i++)
	{
		for (int j = PaddOffset; j < 5 + PaddOffset; j++)
		{
			if ((LevelData[i][j] == 1) || (LevelData[i][j] == 2))
			{
				D3DEngine::Vector3f TileCenter = D3DEngine::Vector3f(i * 2, -0.05, j * 2);
				D3DEngine::GameObject* Tile = new D3DEngine::GameObject();
				Tile->AddComponent(new D3DEngine::MeshRenderer(GroundTileMesh, material));
				Tile->GetTransform()->SetPosition(TileCenter);
				RootObject->AddChild(Tile);

				if (LevelData[i][j] == 2)
				{
					m_PhysicsEngineComponent->GetPhysicsEngine()->AddObject(D3DEngine::PhysicsObject(new D3DEngine::BoundingSphere(D3DEngine::Vector3f(i * 2, -0.5f, j * 2), .2f), D3DEngine::Vector3f(0.0f, 0.0f, 0.0f)));
					m_ObjectsMap.push_back(LevelID(i, j, ObjectCount, TileCenter, TYPE::BALL));
					ObjectCount++;
				}

				if (j - 1 >= 0)
				{
					if (LevelData[i][j - 1] <= 0)
					{
						LevelData[i][j - 1] -= 1;
						m_PhysicsEngineComponent->GetPhysicsEngine()->AddAABBFromMesh(SideRes->GetVertices(), SideRes->GetVERTEXSIZE(), SideRes->GetIndices(), SideRes->GetINDEXSIZE());
						m_ObjectsMap.push_back(LevelID(i, j, ObjectCount, TileCenter, TYPE::WALLSIDE));
						ObjectCount++;
					}
				}
				if (j + 1 < 7)
				{
					if (LevelData[i][j + 1] <= 0)
					{
						LevelData[i][j + 1] -= 1;
						m_PhysicsEngineComponent->GetPhysicsEngine()->AddAABBFromMesh(SideRes->GetVertices(), SideRes->GetVERTEXSIZE(), SideRes->GetIndices(), SideRes->GetINDEXSIZE());
						m_ObjectsMap.push_back(LevelID(i, j, ObjectCount, TileCenter, TYPE::WALLSIDE));
						ObjectCount++;
					}
				}
				if (i - 1 >= 0)
				{
					if (LevelData[i - 1][j] <= 0)
					{
						LevelData[i - 1][j] -= 1;
						m_PhysicsEngineComponent->GetPhysicsEngine()->AddAABBFromMesh(BackRes->GetVertices(), SideRes->GetVERTEXSIZE(), BackRes->GetIndices(), BackRes->GetINDEXSIZE());
						m_ObjectsMap.push_back(LevelID(i, j, ObjectCount, TileCenter, TYPE::WALLBACK));
						ObjectCount++;
					}
				}
				if (i + 1 < 7)
				{
					if (LevelData[i + 1][j] <= 0)
					{
						LevelData[i + 1][j] -= 1;
						m_PhysicsEngineComponent->GetPhysicsEngine()->AddAABBFromMesh(BackRes->GetVertices(), BackRes->GetVERTEXSIZE(), BackRes->GetIndices(), BackRes->GetINDEXSIZE());
						m_ObjectsMap.push_back(LevelID(i, j, ObjectCount, TileCenter, TYPE::WALLBACK));
						ObjectCount++;
					}
				}
			}
		}
	}
	//Update Objects
	for (int i = 0; i < m_ObjectsMap.size(); i++)
	{
		int PosI = m_ObjectsMap[i].I;
		int PosJ = m_ObjectsMap[i].J;
		std::string Key = std::to_string(PosI) + std::to_string(PosJ);
		Tile* CurrentTile = &m_TileMap.find(Key)->second;

		int ObjectPos = m_ObjectsMap[i].Pos;
		TYPE ObjectType = m_ObjectsMap[i].m_Type;
		D3DEngine::Vector3f TileCenter = m_ObjectsMap[i].TileCenter;

		if (ObjectType == TYPE::BALL)
		{
			//GolfClub
			D3DEngine::GameObject* GolfClubObject = new D3DEngine::GameObject();
			GolfClubObject->AddComponent(new D3DEngine::MeshRenderer(GolfClubMesh, MetalMat));
			GolfClubObject->GetTransform()->SetPosition(D3DEngine::Vector3f(-1.4, 0, 0));
			GolfClubObject->GetTransform()->SetScaling(D3DEngine::Vector3f(8, 8, 6));
			//End GolfClub
			//Sphere
			m_GameObjects.push_back(new D3DEngine::GameObject());
			m_GameObjects.back()->GetTransform()->SetScaling(D3DEngine::Vector3f(0.1f, 0.1f, 0.1f));

			D3DEngine::Vector3f MyCenter = TileCenter;
			MyCenter.SetY(0.1f);

			D3DEngine::Vector3f CameraPos = MyCenter;
			CameraPos.SetX(CameraPos.GetX() + 0);
			CameraPos.SetY(CameraPos.GetY() + 2);
			CameraPos.SetZ(CameraPos.GetZ() - 1);
			CameraObject->GetTransform()->SetPosition(CameraPos); //Update Camera to Ball

			m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(ObjectPos).SetPosition(MyCenter);

			m_GameObjects.back()->AddComponent(new D3DEngine::MeshRenderer(BallMesh, GolfBallMat));
			m_GameObjects.back()->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(ObjectPos), true));
			GolfClubObject->AddComponent(new GolfClub(m_GameObjects.back(), &m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(ObjectPos), 8, 0.5, 10));
			m_GameObjects.back()->AddChild(GolfClubObject);
			
			//CameraObject->GetTransform()->SetRotation(m_GameObjects.back()->GetTransform()->GetRotation()); //Tilt Down
			//m_GameObjects.back()->AddChild(CameraObject);
			//End Sphere
		}
		if (ObjectType == TYPE::WALLBACK)
		{
			std::cerr << "Wall Back" << std::endl;
			if (PosI - 1 >= 0)
			{
				if (LevelData[PosI - 1][PosJ] < 0)
				{
					if (CurrentTile->Top == false)
					{
						CurrentTile->Top = true;
						TranslateHelper(1.08f, 0.0f, ObjectPos, TileCenter, m_PhysicsEngineComponent);
						CreateHelper(ObjectPos, BackMesh, SideMat, m_PhysicsEngineComponent, RootObject);
						continue;
					}
				}
			}
			if (PosI + 1 < 7)
			{
				if (LevelData[PosI + 1][PosJ] < 0)
				{
					if (CurrentTile->Bottom == false)
					{
						CurrentTile->Bottom = true;
						TranslateHelper(-1.08f, 0.0f, ObjectPos, TileCenter, m_PhysicsEngineComponent);
						CreateHelper(ObjectPos, BackMesh, SideMat, m_PhysicsEngineComponent, RootObject);
						continue;
					}
				}
			}
		}
		if (ObjectType == TYPE::WALLSIDE)
		{ 
			std::cerr << "Wall Side" << std::endl;
			if (PosJ - 1 >= 0)
			{
				if (LevelData[PosI][PosJ - 1] < 0)
				{
					if (CurrentTile->Left == false)
					{
						std::cerr << "Wall Side: Moved left" << std::endl;
						CurrentTile->Left = true;
						TranslateHelper(0.0f, 1.08f, ObjectPos, TileCenter, m_PhysicsEngineComponent);
						CreateHelper(ObjectPos, SideMesh, SideMat, m_PhysicsEngineComponent, RootObject);
						continue;
					}
				}
			}
			if (PosJ + 1 < 7)
			{
				if (LevelData[PosI][PosJ + 1] < 0)
				{
					if (CurrentTile->Right == false)
					{
						std::cerr << "Wall Side: Moved Right" << std::endl;
						CurrentTile->Right = true;
						TranslateHelper(0.0f, -1.08f, ObjectPos, TileCenter, m_PhysicsEngineComponent);
						CreateHelper(ObjectPos, SideMesh, SideMat, m_PhysicsEngineComponent, RootObject);
						continue;
					}
				}
			}
		}
	}
	
	//Lights
	D3DEngine::GameObject* DirectionalLightObject = new D3DEngine::GameObject();
	D3DEngine::DirectionalLight* directionalLight = new D3DEngine::DirectionalLight(renderEngine->GetShaderList(), D3DEngine::Vector3f(1, 1, 1), 0.9f);
	DirectionalLightObject->AddComponent(directionalLight);
	DirectionalLightObject->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(1, 1, 1), TO_RADIANS(-45.0f)));

	D3DEngine::GameObject* DirectionalLightObject2 = new D3DEngine::GameObject();
	D3DEngine::DirectionalLight* directionalLight2 = new D3DEngine::DirectionalLight(renderEngine->GetShaderList(), D3DEngine::Vector3f(1, 1, 1), 0.9f);
	DirectionalLightObject2->AddComponent(directionalLight2);
	DirectionalLightObject2->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(1, 1, 1), TO_RADIANS(45.0f)));
	//Lights End

	RootObject->AddChild(CameraObject);
	RootObject->AddChild(DirectionalLightObject);
	RootObject->AddChild(DirectionalLightObject2);

	for (int i = 0; i < m_GameObjects.size(); i++)
		RootObject->AddChild(m_GameObjects.at(i));
}

Level::Level(
	D3DEngine::Window* Window, D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine,
	D3DEngine::GameObject* RootObject)
{

	D3DEngine::PhysicsEngineComponent* m_PhysicsEngineComponent = new D3DEngine::PhysicsEngineComponent(physicsEngine);
	D3DEngine::GameObject* PhysicsEngineObj = new D3DEngine::GameObject();
	PhysicsEngineObj->AddComponent(m_PhysicsEngineComponent);
	RootObject->AddChild(PhysicsEngineObj);

	physicsEngine->AddObject(D3DEngine::PhysicsObject(new D3DEngine::BoundingSphere(D3DEngine::Vector3f(0.0f, 0.0f, 0.0f), .2f), D3DEngine::Vector3f(0.0f, 0.0f, 0.0f)));

	D3DEngine::GameObject* CameraObject = new D3DEngine::GameObject();
	float Aspect = Window->GetWidth() / Window->GetHeight();
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

	D3DEngine::Material* SideMat = new D3DEngine::Material();
	SideMat->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/Wood.png"));
	SideMat->AddFloat("SpecularIntensity", 1);
	SideMat->AddFloat("SpecularExponent", 8);

	D3DEngine::Material* MetalMat = new D3DEngine::Material();
	MetalMat->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/Metal.png"));
	MetalMat->AddFloat("SpecularIntensity", 1);
	MetalMat->AddFloat("SpecularExponent", 8);

	D3DEngine::Mesh* BallMesh = new D3DEngine::Mesh("./Models/Ball.obj", m_MeshList);
	D3DEngine::Mesh* BackMesh = new D3DEngine::Mesh("./Models/CourseBack.obj", m_MeshList);
	D3DEngine::Mesh* SideMesh = new D3DEngine::Mesh("./Models/CourseSide.obj", m_MeshList);
	D3DEngine::Mesh* GroundTileMesh = new D3DEngine::Mesh("./Models/GroundTile.obj", m_MeshList);
	D3DEngine::Mesh* GolfClubMesh = new D3DEngine::Mesh("./Models/GolfClub.obj", m_MeshList);

	D3DEngine::MeshResource* BackRes = m_MeshList->GetModel("./Models/CourseBack.obj");
	D3DEngine::MeshResource* SideRes = m_MeshList->GetModel("./Models/CourseSide.obj");

	//Back and Top
	physicsEngine->AddAABBFromMesh(BackRes->GetVertices(), BackRes->GetVERTEXSIZE(), BackRes->GetIndices(), BackRes->GetINDEXSIZE());
	physicsEngine->AddAABBFromMesh(BackRes->GetVertices(), BackRes->GetVERTEXSIZE(), BackRes->GetIndices(), BackRes->GetINDEXSIZE());
	//Sides
	for (int i = 0; i < 8; i++)
		physicsEngine->AddAABBFromMesh(SideRes->GetVertices(), SideRes->GetVERTEXSIZE(), SideRes->GetIndices(), SideRes->GetINDEXSIZE());

	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(1).SetPosition(D3DEngine::Vector3f(4.1f - (2.089 * 3.475), 0.0f, 0.0f));
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(2).SetPosition(D3DEngine::Vector3f(5.0f, 0.0f, 0.0f));
	//SideA
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(3).SetPosition(D3DEngine::Vector3f(4.1f, 0.0f, 1.089f));
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(4).SetPosition(D3DEngine::Vector3f(4.1f - 2.089, 0.0f, 1.089f));
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(5).SetPosition(D3DEngine::Vector3f(4.1f - (2.089 * 2), 0.0f, 1.089f));
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(6).SetPosition(D3DEngine::Vector3f(4.1f - (2.089 * 3), 0.0f, 1.089f));
	//SideB
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(7).SetPosition(D3DEngine::Vector3f(4.1f, 0.0f, -1.078f));
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(8).SetPosition(D3DEngine::Vector3f(4.1f - 2.089, 0.0f, -1.078f));
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(9).SetPosition(D3DEngine::Vector3f(4.1f - (2.089 * 2), 0.0f, -1.078f));
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(10).SetPosition(D3DEngine::Vector3f(4.1f - (2.089 * 3), 0.0f, -1.078f));

	D3DEngine::GameObject* GolfClubObject = new D3DEngine::GameObject();
	GolfClubObject->AddComponent(new D3DEngine::MeshRenderer(GolfClubMesh, MetalMat));
	GolfClubObject->GetTransform()->SetPosition(D3DEngine::Vector3f(-1.4, 0, 0));
	GolfClubObject->GetTransform()->SetScaling(D3DEngine::Vector3f(8, 8, 6));


	//Sphere
	D3DEngine::GameObject* Sphere = new D3DEngine::GameObject();
	D3DEngine::MeshRenderer* SphereMeshRenderer = new D3DEngine::MeshRenderer(BallMesh, GolfBallMat);
	Sphere->GetTransform()->SetScaling(D3DEngine::Vector3f(0.1f, 0.1f, 0.1f));
	Sphere->AddComponent(SphereMeshRenderer);
	Sphere->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(0), true));
	GolfClubObject->AddComponent(new GolfClub(Sphere, &m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(0), 8, 0.5, 10));
	Sphere->AddChild(GolfClubObject);
	//End Sphere





	D3DEngine::GameObject* FrontBarrier = new D3DEngine::GameObject();
	D3DEngine::MeshRenderer* PlaneMeshRenderer = new D3DEngine::MeshRenderer(BackMesh, SideMat);
	FrontBarrier->AddComponent(PlaneMeshRenderer);
	FrontBarrier->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(1)));

	D3DEngine::GameObject* BackBarrier = new D3DEngine::GameObject();
	D3DEngine::MeshRenderer* PlaneMeshRenderer2 = new D3DEngine::MeshRenderer(BackMesh, SideMat);
	BackBarrier->AddComponent(PlaneMeshRenderer2);
	BackBarrier->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(2)));

	D3DEngine::GameObject* GTile1 = new D3DEngine::GameObject();
	GTile1->AddComponent(new D3DEngine::MeshRenderer(GroundTileMesh, material));
	GTile1->GetTransform()->SetPosition(D3DEngine::Vector3f(3.9, -0.05, 0));

	D3DEngine::GameObject* GTile2 = new D3DEngine::GameObject();
	GTile2->AddComponent(new D3DEngine::MeshRenderer(GroundTileMesh, material));
	GTile2->GetTransform()->SetPosition(D3DEngine::Vector3f(3.9 - (2 * 1), -0.05, 0));

	D3DEngine::GameObject* GTile3 = new D3DEngine::GameObject();
	GTile3->AddComponent(new D3DEngine::MeshRenderer(GroundTileMesh, material));
	GTile3->GetTransform()->SetPosition(D3DEngine::Vector3f(3.9 - (2 * 2), -0.05, 0));

	D3DEngine::GameObject* GTile4 = new D3DEngine::GameObject();
	GTile4->AddComponent(new D3DEngine::MeshRenderer(GroundTileMesh, material));
	GTile4->GetTransform()->SetPosition(D3DEngine::Vector3f(3.9 - (2 * 3), -0.05, 0));

	//4.1f, 0.0f, 1.089f)
	//SideA
	D3DEngine::GameObject* Side1 = new D3DEngine::GameObject();
	Side1->AddComponent(new D3DEngine::MeshRenderer(SideMesh, SideMat));
	Side1->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(3)));

	D3DEngine::GameObject* Side2 = new D3DEngine::GameObject();
	Side2->AddComponent(new D3DEngine::MeshRenderer(SideMesh, SideMat));
	Side2->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(4)));

	D3DEngine::GameObject* Side3 = new D3DEngine::GameObject();
	Side3->AddComponent(new D3DEngine::MeshRenderer(SideMesh, SideMat));
	Side3->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(5)));

	D3DEngine::GameObject* Side4 = new D3DEngine::GameObject();
	Side4->AddComponent(new D3DEngine::MeshRenderer(SideMesh, SideMat));
	Side4->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(6)));
	//SideB
	D3DEngine::GameObject* Side5 = new D3DEngine::GameObject();
	Side5->AddComponent(new D3DEngine::MeshRenderer(SideMesh, SideMat));
	Side5->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(7)));

	D3DEngine::GameObject* Side6 = new D3DEngine::GameObject();
	Side6->AddComponent(new D3DEngine::MeshRenderer(SideMesh, SideMat));
	Side6->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(8)));

	D3DEngine::GameObject* Side7 = new D3DEngine::GameObject();
	Side7->AddComponent(new D3DEngine::MeshRenderer(SideMesh, SideMat));
	Side7->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(9)));

	D3DEngine::GameObject* Side8 = new D3DEngine::GameObject();
	Side8->AddComponent(new D3DEngine::MeshRenderer(SideMesh, SideMat));
	Side8->AddComponent(new D3DEngine::PhysicsObjectComponent(&m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(10)));





	//Lights
	D3DEngine::GameObject* DirectionalLightObject = new D3DEngine::GameObject();
	D3DEngine::DirectionalLight* directionalLight = new D3DEngine::DirectionalLight(renderEngine->GetShaderList(), D3DEngine::Vector3f(1, 1, 1), 0.9f);
	DirectionalLightObject->AddComponent(directionalLight);
	DirectionalLightObject->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(1, 1, 1), TO_RADIANS(-45.0f)));

	D3DEngine::GameObject* DirectionalLightObject2 = new D3DEngine::GameObject();
	D3DEngine::DirectionalLight* directionalLight2 = new D3DEngine::DirectionalLight(renderEngine->GetShaderList(), D3DEngine::Vector3f(1, 1, 1), 0.9f);
	DirectionalLightObject2->AddComponent(directionalLight2);
	DirectionalLightObject2->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(1, 1, 1), TO_RADIANS(45.0f)));
	//Lights End

	
	RootObject->AddChild(CameraObject);
	RootObject->AddChild(Sphere);
	
	RootObject->AddChild(DirectionalLightObject);
	RootObject->AddChild(DirectionalLightObject2);
	RootObject->AddChild(FrontBarrier);
	RootObject->AddChild(BackBarrier);
	//GTile
	RootObject->AddChild(GTile1);
	RootObject->AddChild(GTile2);
	RootObject->AddChild(GTile3);
	RootObject->AddChild(GTile4);
	//SideA
	RootObject->AddChild(Side1);
	RootObject->AddChild(Side2);
	RootObject->AddChild(Side3);
	RootObject->AddChild(Side4);
	//SideB
	RootObject->AddChild(Side5);
	RootObject->AddChild(Side6);
	RootObject->AddChild(Side7);
	RootObject->AddChild(Side8);


}


Level::~Level()
{
}
