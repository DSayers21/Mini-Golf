#pragma once
#include <GL/glew.h>
#include <Shader.h>
#include <Lighting.h>

#include <Camera.h>
#include <Cuboid.h>
#include <Rect.h>
//

#include <Vecmath.h>

class MainGame
{
public:
	MainGame();
	~MainGame();

	void RenderScene(void);
	void SpecKeyboardFunc(int key, int x, int y);
	void SpecKeyboardUpFunc(int key, int x, int y);
	void KeyboardFunc(unsigned char key, int x, int y);
	void KeyboardUpFunc(unsigned char key, int x, int y);

	void UpdateScene(int ms);

	//Getters
	D3DEngine::Camera* GetCamera() { return &m_MainCamera; }
private:
	D3DEngine::Camera m_MainCamera;
	D3DEngine::Lighting m_Lighting;
	D3DEngine::Shader* m_Shader;


	D3DEngine::Cuboid m_Cuboid = D3DEngine::Cuboid(0.01, 0.01, 0.01, D3DEngine::vec3(0,0,0));
	D3DEngine::Cuboid m_Cuboid2 = D3DEngine::Cuboid(0.1, 0.3, 0.1, D3DEngine::vec3(1,0, 0));


	D3DEngine::Rect m_Rect = D3DEngine::Rect(0.5, 1, -3, D3DEngine::vec3(1,0,0), D3DEngine::Colour(1.0,1.0,1.0));
};