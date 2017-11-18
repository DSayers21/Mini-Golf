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
#include "AxisAlignedBoundingBox.h"
#include "Plane.h"
#include "PhysicsObject.h"

#include "Vector3f.h"

#ifdef _WIN32
#undef main
#endif

int main(int argc, char** argv)
{
	//D3DEngine::BoundingSphere sphere1(D3DEngine::Vector3f(0.0f, 0.0f, 0.0f), 1.0f);
	//D3DEngine::BoundingSphere sphere2(D3DEngine::Vector3f(0.0f, 3.0f, 0.0f), 1.0f);
	//D3DEngine::BoundingSphere sphere3(D3DEngine::Vector3f(0.0f, 0.0f, 2.0f), 1.0f);
	//D3DEngine::BoundingSphere sphere4(D3DEngine::Vector3f(1.0f, 0.0f, 0.0f), 1.0f);

	//D3DEngine::IntersectData sphere1Intersect2 = sphere1.IntersectBoundingSphere(sphere2);
	//D3DEngine::IntersectData sphere1Intersect3 = sphere1.IntersectBoundingSphere(sphere3);
	//D3DEngine::IntersectData sphere1Intersect4 = sphere1.IntersectBoundingSphere(sphere4);

	//std::cout << "Sphere1 Intersect sphere2: " << sphere1Intersect2.GetDoesIntersect() << ", Distance: " << sphere1Intersect2.GetDistance() << std::endl;
	//std::cout << "Sphere2 Intersect sphere3: " << sphere1Intersect3.GetDoesIntersect() << ", Distance: " << sphere1Intersect3.GetDistance() << std::endl;
	//std::cout << "Sphere3 Intersect sphere4: " << sphere1Intersect4.GetDoesIntersect() << ", Distance: " << sphere1Intersect4.GetDistance() << std::endl;

	//D3DEngine::AxisAlignedBoundingBox aabb1(D3DEngine::Vector3f(0.0f, 0.0f, 0.0f), D3DEngine::Vector3f(1.0f, 1.0f, 1.0f));
	//D3DEngine::AxisAlignedBoundingBox aabb2(D3DEngine::Vector3f(1.0f, 1.0f, 1.0f), D3DEngine::Vector3f(2.0f, 2.0f, 2.0f));
	//D3DEngine::AxisAlignedBoundingBox aabb3(D3DEngine::Vector3f(1.0f, 0.0f, 0.0f), D3DEngine::Vector3f(2.0f, 1.0f, 1.0f));
	//D3DEngine::AxisAlignedBoundingBox aabb4(D3DEngine::Vector3f(0.0f, 0.0f, -2.0f), D3DEngine::Vector3f(1.0f, 1.0f, -1.0f));
	//D3DEngine::AxisAlignedBoundingBox aabb5(D3DEngine::Vector3f(0.0f, 0.5f, 0.0f), D3DEngine::Vector3f(1.0f, 1.5f, 1.0f));

	//D3DEngine::IntersectData aabb1Intersectaabb2 = aabb1.Intersect(aabb2);
	//D3DEngine::IntersectData aabb1Intersectaabb3 = aabb1.Intersect(aabb3);
	//D3DEngine::IntersectData aabb1Intersectaabb4 = aabb1.Intersect(aabb4);
	//D3DEngine::IntersectData aabb1Intersectaabb5 = aabb1.Intersect(aabb5);

	//std::cout << "AABB1 Intersect AABB2: " << aabb1Intersectaabb2.GetDoesIntersect() << ", Distance: " << aabb1Intersectaabb2.GetDistance() << std::endl;
	//std::cout << "AABB1 Intersect AABB3: " << aabb1Intersectaabb3.GetDoesIntersect() << ", Distance: " << aabb1Intersectaabb3.GetDistance() << std::endl;
	//std::cout << "AABB1 Intersect AABB4: " << aabb1Intersectaabb4.GetDoesIntersect() << ", Distance: " << aabb1Intersectaabb4.GetDistance() << std::endl;
	//std::cout << "AABB1 Intersect AABB5: " << aabb1Intersectaabb5.GetDoesIntersect() << ", Distance: " << aabb1Intersectaabb5.GetDistance() << std::endl;


	//D3DEngine::Plane plane1(D3DEngine::Vector3f(0.0f, 1.0f, 0.0f),0.0f);

	//D3DEngine::IntersectData plane1IntersectSphere1 = plane1.IntersectSphere(sphere1);
	//D3DEngine::IntersectData plane1IntersectSphere2 = plane1.IntersectSphere(sphere2); 
	//D3DEngine::IntersectData plane1IntersectSphere3 = plane1.IntersectSphere(sphere3); 
	//D3DEngine::IntersectData plane1IntersectSphere4 = plane1.IntersectSphere(sphere4); 

	//std::cout << "Plane1 intersect Sphere1: " << plane1IntersectSphere1.GetDoesIntersect() << ", Distance: " << plane1IntersectSphere1.GetDistance() << std::endl;
	//std::cout << "Plane1 intersect Sphere2: " << plane1IntersectSphere2.GetDoesIntersect() << ", Distance: " << plane1IntersectSphere2.GetDistance() << std::endl;
	//std::cout << "Plane1 intersect Sphere3: " << plane1IntersectSphere3.GetDoesIntersect() << ", Distance: " << plane1IntersectSphere3.GetDistance() << std::endl;
	//std::cout << "Plane1 intersect Sphere4: " << plane1IntersectSphere4.GetDoesIntersect() << ", Distance: " << plane1IntersectSphere4.GetDistance() << std::endl;
	//

	D3DEngine::PhysicsObject Test(D3DEngine::Vector3f(0.0f, 1.0f, 0.0f), D3DEngine::Vector3f(1.0f, 2.0f, 3.0f), 1.0f);
	Test.Integrate(20.0f);
	D3DEngine::Vector3f TestPos = Test.GetPosition();
	D3DEngine::Vector3f TestVel = Test.GetVelocity();
	std::cout << TestPos.ToString() << std::endl;
	std::cout << TestVel.ToString() << std::endl;

	//getchar();
	
	std::string Title = "Advanced Programming Assignment";
	D3DEngine::MainComp m_MainComp(Title, 1200, 800, 120, new TestGame());
	return 0;
}