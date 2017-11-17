//Open GL includes
#include <GL/glew.h>
#include <glm/glm.hpp>
//Includes
#include <iostream>
#include <string>
//My Includes
#include <MainComp.h>
#include "TestGame.h"
#include "BoundingSphere.h"
#include "IntersectData.h"
#include "Vector3f.h"
#ifdef _WIN32
#undef main
#endif

int main(int argc, char** argv)
{
	D3DEngine::BoundingSphere sphere1(D3DEngine::Vector3f(0.0f, 0.0f, 0.0f), 1.0f);
	D3DEngine::BoundingSphere sphere2(D3DEngine::Vector3f(0.0f, 3.0f, 0.0f), 1.0f);
	D3DEngine::BoundingSphere sphere3(D3DEngine::Vector3f(0.0f, 0.0f, 2.0f), 1.0f);
	D3DEngine::BoundingSphere sphere4(D3DEngine::Vector3f(1.0f, 0.0f, 0.0f), 1.0f);

	D3DEngine::IntersectData sphere1Intersect2 = sphere1.IntersectBoundingSphere(sphere2);
	D3DEngine::IntersectData sphere1Intersect3 = sphere1.IntersectBoundingSphere(sphere3);
	D3DEngine::IntersectData sphere1Intersect4 = sphere1.IntersectBoundingSphere(sphere4);

	std::cout << "Sphere1 Intersect sphere2: " << sphere1Intersect2.GetDoesIntersect() << ", Distance: " << sphere1Intersect2.GetDistance() << std::endl;
	std::cout << "Sphere2 Intersect sphere3: " << sphere1Intersect3.GetDoesIntersect() << ", Distance: " << sphere1Intersect3.GetDistance() << std::endl;
	std::cout << "Sphere3 Intersect sphere4: " << sphere1Intersect4.GetDoesIntersect() << ", Distance: " << sphere1Intersect4.GetDistance() << std::endl;

	getchar();

	/*std::string Title = "Advanced Programming Assignment";
	D3DEngine::MainComp m_MainComp(Title, 1200, 800, 120, new TestGame());*/
	return 0;
}