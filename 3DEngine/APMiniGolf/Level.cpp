#include "Level.h"

void Level::TranslateHelper(float x, float z, int CurCount, D3DEngine::Vector3f tileCenter,
	D3DEngine::PhysicsEngineComponent* PhysicsEngineComponent)
{
	D3DEngine::Vector3f MyCenter = tileCenter;
	D3DEngine::Vector3f Pos = PhysicsEngineComponent->GetPhysicsEngine()->GetObject(CurCount)->GetPosition();

	MyCenter.SetX(MyCenter.GetX() - x);
	MyCenter.SetZ(MyCenter.GetZ() - z);
	MyCenter.SetY(0.1f);

	PhysicsEngineComponent->GetPhysicsEngine()->GetObject(CurCount)->SetPosition(MyCenter);
}

void Level::CreateHelper(int CurCount,
	D3DEngine::Mesh* mesh, D3DEngine::Material* material,
	D3DEngine::PhysicsEngineComponent* PhysicsEngineComponent, D3DEngine::GameObject* RootObject)
{

	D3DEngine::GameObject* Test = new D3DEngine::GameObject();
	Test->AddComponent(new D3DEngine::MeshRenderer(mesh, material));
	Test->AddComponent(new D3DEngine::PhysicsObjectComponent(PhysicsEngineComponent->GetPhysicsEngine()->GetObject(CurCount)));
	RootObject->AddChild(Test);
}

Level::Level(int LevelData[7][7],
	D3DEngine::Window* Window, D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine,
	D3DEngine::GameObject* RootObject)
{
	m_PhysicsEngineComponent = new D3DEngine::PhysicsEngineComponent(physicsEngine);
	D3DEngine::GameObject* PhysicsEngineObj = new D3DEngine::GameObject();
	PhysicsEngineObj->AddComponent(m_PhysicsEngineComponent);
	RootObject->AddChild(PhysicsEngineObj);

	D3DEngine::GameObject* CameraObject = new D3DEngine::GameObject();
	float Aspect = Window->GetWidth() / Window->GetHeight();
	CameraObject->AddComponent(new D3DEngine::Camera(TO_RADIANS(90.0f), Aspect, 0.01f, 1000.0f));
	CameraObject->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(1, 0, 0), TO_RADIANS(30.0f))); //Tilt Down
	CameraObject->GetTransform()->SetPosition(D3DEngine::Vector3f(-8.0f, 22.0f, 0.0f));
	CameraObject->AddComponent(new D3DEngine::FreeLook());

	//Materials
	D3DEngine::Material* GroundTexture = new D3DEngine::Material();
	GroundTexture->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/GolfTexture.png"));
	GroundTexture->AddFloat("SpecularIntensity", 0.01);
	GroundTexture->AddFloat("SpecularExponent", 42);
	m_MaterialList.push_back(GroundTexture);

	D3DEngine::Material* GolfBallMat = new D3DEngine::Material();
	GolfBallMat->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/GolfBallTexture.png"));
	GolfBallMat->AddFloat("SpecularIntensity", 1);
	GolfBallMat->AddFloat("SpecularExponent", 8);
	m_MaterialList.push_back(GolfBallMat);

	D3DEngine::Material* SideMat = new D3DEngine::Material();
	SideMat->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/Wood.png"));
	SideMat->AddFloat("SpecularIntensity", 1);
	SideMat->AddFloat("SpecularExponent", 8);
	m_MaterialList.push_back(SideMat);

	D3DEngine::Material* MetalMat = new D3DEngine::Material();
	MetalMat->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/Metal.png"));
	MetalMat->AddFloat("SpecularIntensity", 1);
	MetalMat->AddFloat("SpecularExponent", 8);
	m_MaterialList.push_back(MetalMat);

	D3DEngine::Material* FlagMat = new D3DEngine::Material();
	FlagMat->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/FlagTexture.png"));
	FlagMat->AddFloat("SpecularIntensity", 1);
	FlagMat->AddFloat("SpecularExponent", 8);
	m_MaterialList.push_back(FlagMat);

	D3DEngine::Material* StartZoneMat = new D3DEngine::Material();
	StartZoneMat->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/GolfStrtZone.png"));
	StartZoneMat->AddFloat("SpecularIntensity", 1);
	StartZoneMat->AddFloat("SpecularExponent", 8);
	m_MaterialList.push_back(StartZoneMat);
	//End Materials

	//Load Meshes
	D3DEngine::Mesh BackMesh = D3DEngine::Mesh("./Models/CourseBack.obj", &m_MeshList);
	D3DEngine::Mesh SideMesh = D3DEngine::Mesh("./Models/CourseSide.obj", &m_MeshList);
	//Get Mesh Resources for Physics Objects
	D3DEngine::MeshResource* BackRes = m_MeshList.GetModel("./Models/CourseBack.obj");
	D3DEngine::MeshResource* SideRes = m_MeshList.GetModel("./Models/CourseSide.obj");

	int PaddOffset = 1;

	int ObjectCount = 0;
	for (int i = PaddOffset; i < 5 + PaddOffset; i++)
		for (int j = PaddOffset; j <  5 + PaddOffset; j++)
			m_TileMap.insert(std::pair<std::string, Tile>(std::to_string(i) + std::to_string(j), Tile()));

	//Find the Ball And make sure it is created first,// Specials
	for (int i = PaddOffset; i < 5 + PaddOffset; i++)
	{
		for (int j = PaddOffset; j < 5 + PaddOffset; j++)
		{
			if (LevelData[i][j] == 2) //Ball
			{
				D3DEngine::Vector3f TileCenter = D3DEngine::Vector3f(i * 2, -0.05, j * 2);

				D3DEngine::GameObject* TileStrt = new D3DEngine::GameObject();
				TileStrt->AddComponent(new D3DEngine::MeshRenderer(new D3DEngine::Mesh("./Models/GolfBallStart.obj", &m_MeshList), StartZoneMat));
				TileStrt->GetTransform()->Rotate(D3DEngine::Vector3f(0, 1, 0), TO_RADIANS(90));
				D3DEngine::Vector3f MyPos = TileCenter;

				MyPos.SetY(-0.07f);
				TileStrt->GetTransform()->SetPosition(MyPos);
				TileStrt->GetTransform()->SetScaling(D3DEngine::Vector3f(0.5,1,0.5));
				RootObject->AddChild(TileStrt);

				m_PhysicsEngineComponent->GetPhysicsEngine()->AddObject(new D3DEngine::PhysicsObject(new D3DEngine::BoundingSphere(D3DEngine::Vector3f(i * 2, -0.5f, j * 2), .1f), D3DEngine::Vector3f(0.0f, 0.0f, 0.0f)));
				m_ObjectsMap.push_back(LevelID(i, j, ObjectCount, TileCenter, TYPE::BALL));
				ObjectCount++;
			}
			if (LevelData[i][j] == 3) //Flag
			{
				D3DEngine::Vector3f TileCenter = D3DEngine::Vector3f(i * 2, 0.0, j * 2);

				//Add Hole
				D3DEngine::GameObject* Hole = new D3DEngine::GameObject();
				Hole->AddComponent(new D3DEngine::MeshRenderer(new D3DEngine::Mesh("./Models/Hole.obj", &m_MeshList), StartZoneMat));
				D3DEngine::Vector3f MyPos = TileCenter;
				MyPos.SetY(-0.02f);
				Hole->GetTransform()->SetPosition(MyPos);
				Hole->GetTransform()->SetScaling(D3DEngine::Vector3f(0.1f, 0.0f, 0.1f));
				RootObject->AddChild(Hole);
				//End Add Hole

				//Add Flag
				D3DEngine::GameObject* FlagBack = new D3DEngine::GameObject();
				FlagBack->AddComponent(new D3DEngine::MeshRenderer(new D3DEngine::Mesh("./Models/Flag.obj", &m_MeshList), FlagMat));
				FlagBack->GetTransform()->SetPosition(D3DEngine::Vector3f(0.8f, 2.35f, 0.0f));
				FlagBack->GetTransform()->SetScaling(D3DEngine::Vector3f(1.0f, 0.3f, 1.0f));
				FlagBack->GetTransform()->Rotate(D3DEngine::Vector3f(0, 1, 0), TO_RADIANS(270));

				D3DEngine::GameObject* FlagFront = new D3DEngine::GameObject();
				FlagFront->AddComponent(new D3DEngine::MeshRenderer(new D3DEngine::Mesh("./Models/Flag.obj", &m_MeshList), FlagMat));
				FlagFront->GetTransform()->SetPosition(D3DEngine::Vector3f(0.8f, 2.5f, 0.0f));
				FlagFront->GetTransform()->SetScaling(D3DEngine::Vector3f(1.0f, 0.3f, 1.0f));
				FlagFront->GetTransform()->SetRotation(0, 1, 0, 0);
				FlagFront->GetTransform()->Rotate(D3DEngine::Vector3f(0, 1, 0), TO_RADIANS(270));
				FlagFront->GetTransform()->Rotate(D3DEngine::Vector3f(0, 0, 1), TO_RADIANS(180));
				//End Add Flag

				//Add Flag Shaft
				D3DEngine::GameObject* FlagShaft = new D3DEngine::GameObject();
				FlagShaft->AddComponent(new D3DEngine::MeshRenderer(new D3DEngine::Mesh("./Models/FlagShaft.obj", &m_MeshList), MetalMat));
				FlagShaft->GetTransform()->SetPosition(TileCenter);
				FlagShaft->GetTransform()->SetScaling(D3DEngine::Vector3f(0.2f, 1.0f, 0.2f));;

				FlagShaft->AddChild(FlagBack);
				FlagShaft->AddChild(FlagFront);

				RootObject->AddChild(FlagShaft);
				//End Add Flag Shaft
			}
		}
	}
	//Create remaing physics objects
	for (int i = PaddOffset; i < 5 + PaddOffset; i++)
	{
		for (int j = PaddOffset; j < 5 + PaddOffset; j++)
		{
			std::string Key = std::to_string(i) + std::to_string(j);
			Tile CurrentTile = m_TileMap.find(Key)->second;
			if ((LevelData[i][j] == 1) || (LevelData[i][j] == 2) || (LevelData[i][j] == 3))
			{
				D3DEngine::Vector3f TileCenter = D3DEngine::Vector3f(i * 2, -0.05, j * 2);
				D3DEngine::GameObject* Tile = new D3DEngine::GameObject();
				Tile->AddComponent(new D3DEngine::MeshRenderer(new D3DEngine::Mesh("./Models/GroundTile.obj", &m_MeshList), GroundTexture));
				Tile->GetTransform()->SetPosition(TileCenter);
				RootObject->AddChild(Tile);

				if (j - 1 >= 0)
				{
					if ((LevelData[i][j - 1] <= 0) && (CurrentTile.Left == false))
					{
						LevelData[i][j - 1] -= 1;
						m_PhysicsEngineComponent->GetPhysicsEngine()->AddAABBFromMesh(SideRes->GetVertices(), SideRes->GetVERTEXSIZE(), SideRes->GetIndices(), SideRes->GetINDEXSIZE());
						m_ObjectsMap.push_back(LevelID(i, j, ObjectCount, TileCenter, TYPE::WALLSIDEL));
						CurrentTile.Left = true;
						ObjectCount++;
					}
				}
				if (j + 1 < 7)
				{
					if ((LevelData[i][j + 1] <= 0) && (CurrentTile.Right == false))
					{
						LevelData[i][j + 1] -= 1;
						m_PhysicsEngineComponent->GetPhysicsEngine()->AddAABBFromMesh(SideRes->GetVertices(), SideRes->GetVERTEXSIZE(), SideRes->GetIndices(), SideRes->GetINDEXSIZE());
						m_ObjectsMap.push_back(LevelID(i, j, ObjectCount, TileCenter, TYPE::WALLSIDER));
						CurrentTile.Right = true;
						ObjectCount++;
					}
				}
				if (i - 1 >= 0)
				{
					if ((LevelData[i - 1][j] <= 0)&&(CurrentTile.Top == false))
					{
						LevelData[i - 1][j] -= 1;
						m_PhysicsEngineComponent->GetPhysicsEngine()->AddAABBFromMesh(BackRes->GetVertices(), SideRes->GetVERTEXSIZE(), BackRes->GetIndices(), BackRes->GetINDEXSIZE());
						m_ObjectsMap.push_back(LevelID(i, j, ObjectCount, TileCenter, TYPE::WALLBACKF));
						CurrentTile.Top = true;
						ObjectCount++;
					}
				}
				if (i + 1 < 7)
				{
					if ((LevelData[i + 1][j] <= 0) && (CurrentTile.Bottom == false))
					{
						LevelData[i + 1][j] -= 1;
						m_PhysicsEngineComponent->GetPhysicsEngine()->AddAABBFromMesh(BackRes->GetVertices(), BackRes->GetVERTEXSIZE(), BackRes->GetIndices(), BackRes->GetINDEXSIZE());
						m_ObjectsMap.push_back(LevelID(i, j, ObjectCount, TileCenter, TYPE::WALLBACKB));
						CurrentTile.Bottom = true;
						ObjectCount++;
					}
				}
			}
		}
	}

	//Update Objects
	for (int i = 0; i < m_ObjectsMap.size(); i++)
	{
		std::cerr << "Processing Physics Object: " << i << std::endl;
		int PosI = m_ObjectsMap[i].I;
		int PosJ = m_ObjectsMap[i].J;
		std::string Key = std::to_string(PosI) + std::to_string(PosJ);
		Tile CurrentTile = m_TileMap.find(Key)->second;

		int ObjectPos = m_ObjectsMap[i].Pos;
		TYPE ObjectType = m_ObjectsMap[i].m_Type;
		D3DEngine::Vector3f TileCenter = m_ObjectsMap[i].TileCenter;

		if (ObjectType == TYPE::BALL)
		{
			std::cerr << "Ball Proccessing" << std::endl;
			//GolfClub
			D3DEngine::GameObject* GolfClubObject = new D3DEngine::GameObject();
			GolfClubObject->AddComponent(new D3DEngine::MeshRenderer(new D3DEngine::Mesh("./Models/GolfClub.obj", &m_MeshList), MetalMat));
			GolfClubObject->GetTransform()->SetPosition(D3DEngine::Vector3f(-1.4, 0, 0));
			GolfClubObject->GetTransform()->SetScaling(D3DEngine::Vector3f(8, 8, 6));
			//End GolfClub
			//Sphere

			D3DEngine::GameObject* GolfBall = new D3DEngine::GameObject();
			GolfBall->GetTransform()->SetScaling(D3DEngine::Vector3f(0.1f, 0.1f, 0.1f));

			D3DEngine::Vector3f MyCenter = TileCenter;
			MyCenter.SetY(0.1f);

			D3DEngine::Vector3f CameraPos = MyCenter;
			CameraPos.SetX(CameraPos.GetX() + 0);
			CameraPos.SetY(CameraPos.GetY() + 2);
			CameraPos.SetZ(CameraPos.GetZ() - 1);
			CameraObject->GetTransform()->SetPosition(CameraPos); //Update Camera to Ball

			m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(ObjectPos)->SetPosition(MyCenter);
			GolfBall->AddComponent(new D3DEngine::MeshRenderer(new D3DEngine::Mesh("./Models/Ball.obj", &m_MeshList), GolfBallMat));
			GolfBall->AddComponent(new D3DEngine::PhysicsObjectComponent(m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(ObjectPos), true));

			GolfClubObject->AddComponent(new GolfClub(GolfBall, m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(ObjectPos), 8, 0.5, 10));
			GolfBall->AddChild(GolfClubObject);
			RootObject->AddChild(GolfBall);
			//End Sphere
		}
	}

	//Update Objects
	for (int i = 0; i < m_ObjectsMap.size(); i++)
	{
		std::cerr << "Processing Physics Object: " << i << std::endl;
		int PosI = m_ObjectsMap[i].I;
		int PosJ = m_ObjectsMap[i].J;
		std::string Key = std::to_string(PosI) + std::to_string(PosJ);
		Tile CurrentTile = m_TileMap.find(Key)->second;

		int ObjectPos = m_ObjectsMap[i].Pos;
		TYPE ObjectType = m_ObjectsMap[i].m_Type;
		D3DEngine::Vector3f TileCenter = m_ObjectsMap[i].TileCenter;

		if (ObjectType == TYPE::WALLBACKF)
		{
			std::cerr << "Wall Back Proccessing: Moved Up" << std::endl;
			TranslateHelper(1.08f, 0.0f, ObjectPos, TileCenter, m_PhysicsEngineComponent);
			CreateHelper(ObjectPos, new D3DEngine::Mesh("./Models/CourseBack.obj", &m_MeshList), SideMat, m_PhysicsEngineComponent, RootObject);
		}
		if (ObjectType == TYPE::WALLBACKB)
		{
			std::cerr << "Wall Back Proccessing: Moved Down" << std::endl;
			TranslateHelper(-1.08f, 0.0f, ObjectPos, TileCenter, m_PhysicsEngineComponent);
			CreateHelper(ObjectPos, new D3DEngine::Mesh("./Models/CourseBack.obj", &m_MeshList), SideMat, m_PhysicsEngineComponent, RootObject);
		}
		if (ObjectType == TYPE::WALLSIDER)
		{
			std::cerr << "Wall Back Proccessing: Moved Right" << std::endl;
			TranslateHelper(0.0f, -1.08f, ObjectPos, TileCenter, m_PhysicsEngineComponent);
			CreateHelper(ObjectPos, new D3DEngine::Mesh("./Models/CourseSide.obj", &m_MeshList), SideMat, m_PhysicsEngineComponent, RootObject);
		}
		if (ObjectType == TYPE::WALLSIDEL)
		{
			std::cerr << "Wall Back Proccessing: Moved Left" << std::endl;
			TranslateHelper(0.0f, 1.08f, ObjectPos, TileCenter, m_PhysicsEngineComponent);
			CreateHelper(ObjectPos, new D3DEngine::Mesh("./Models/CourseSide.obj", &m_MeshList), SideMat, m_PhysicsEngineComponent, RootObject);
		}
	}
	
	//Lights
	D3DEngine::GameObject* DirectionalLightObject = new D3DEngine::GameObject();
	D3DEngine::DirectionalLight* directionalLight = new D3DEngine::DirectionalLight(renderEngine->GetShaderList(), D3DEngine::Vector3f(0.5, 0.5, 0.5), 0.1f);
	DirectionalLightObject->AddComponent(directionalLight);
	DirectionalLightObject->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(1, 1, 1), TO_RADIANS(-45.0f)));


	RootObject->AddChild(CameraObject);
	RootObject->AddChild(DirectionalLightObject);
}

Level::Level(
	D3DEngine::Window* Window, D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine,
	D3DEngine::GameObject* RootObject)
{

	m_PhysicsEngineComponent = new D3DEngine::PhysicsEngineComponent(physicsEngine);
	D3DEngine::GameObject* PhysicsEngineObj = new D3DEngine::GameObject();
	PhysicsEngineObj->AddComponent(m_PhysicsEngineComponent);
	RootObject->AddChild(PhysicsEngineObj);

	D3DEngine::GameObject* CameraObject = new D3DEngine::GameObject();
	float Aspect = Window->GetWidth() / Window->GetHeight();
	CameraObject->AddComponent(new D3DEngine::Camera(TO_RADIANS(90.0f), Aspect, 0.01f, 1000.0f));
	CameraObject->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(0, 1, 0), TO_RADIANS(180.0f)));
	CameraObject->GetTransform()->SetPosition(D3DEngine::Vector3f(0.0f, 2.0f, 2.0f));
	CameraObject->AddComponent(new D3DEngine::FreeLook());

	//MaterialOne

	D3DEngine::Material* SideMat = new D3DEngine::Material();
	SideMat->AddTexture("Diffuse", new D3DEngine::Texture("./Textures/Wood.png"));
	SideMat->AddFloat("SpecularIntensity", 1);
	SideMat->AddFloat("SpecularExponent", 8);
	m_MaterialList.push_back(SideMat);

	D3DEngine::Mesh SideMesh = D3DEngine::Mesh("./Models/CourseSide.obj", &m_MeshList);
	D3DEngine::MeshResource* SideRes = m_MeshList.GetModel("./Models/CourseSide.obj");

	//Sides
	physicsEngine->AddAABBFromMesh(SideRes->GetVertices(), SideRes->GetVERTEXSIZE(), SideRes->GetIndices(), SideRes->GetINDEXSIZE());

	//SideA
	m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(0)->SetPosition(D3DEngine::Vector3f(4.1f, 0.0f, 1.089f));
	

	//4.1f, 0.0f, 1.089f)
	//SideA
	D3DEngine::GameObject* Side1 = new D3DEngine::GameObject();
	Side1->AddComponent(new D3DEngine::MeshRenderer(new D3DEngine::Mesh("./Models/CourseSide.obj", &m_MeshList), SideMat));
	Side1->AddComponent(new D3DEngine::PhysicsObjectComponent(m_PhysicsEngineComponent->GetPhysicsEngine()->GetObject(0)));

	D3DEngine::GameObject* DirectionalLightObject = new D3DEngine::GameObject();
	D3DEngine::DirectionalLight* directionalLight = new D3DEngine::DirectionalLight(renderEngine->GetShaderList(), D3DEngine::Vector3f(0.5, 0.5, 0.5), 0.1f);
	DirectionalLightObject->AddComponent(directionalLight);
	DirectionalLightObject->GetTransform()->SetRotation(&D3DEngine::Quaternion(D3DEngine::Vector3f(1, 1, 1), TO_RADIANS(-45.0f)));
	
	
	RootObject->AddChild(DirectionalLightObject);

	RootObject->AddChild(CameraObject);

	RootObject->AddChild(Side1);

}

Level::~Level()
{
	std::cerr << "Destructor: Level" << std::endl;
}

void Level::Destroy()
{
	for (int i = 0; i < m_MaterialList.size(); i++)
	{
		delete m_MaterialList[i];
	}
	m_MaterialList.clear();
}