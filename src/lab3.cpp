#include <iostream>
#include <cassert>
#include "scene/Scene.h"
#include "scene/Sphere.h"
#include "scene/Triangle.h"
#include "scene/Intersection.h"
#include "Raytracer.h"
#include "RecursiveAntialising.h"
#include "DrawAPI.h"
#include "NFFLoader.h"
#include "DepthOfField.h"



void test(Scene * s) {
	int resx = 500;
	int resy = 500;
	Ray ray;
	s->addObject(new Object(glm::vec3(0.0f, 1.0f, 0.0f), 0.50f, 1.0f, 50.0f, 1.0f, 0.0f, new Sphere(0.0f, 0.0f, 0.0f, 0.5f)));
	s->addObject(new Object(glm::vec3(0.0f, 0.0f, 1.0f), 0.50f, 2.0f, 50.0f, 1.0f, 0.0f, new Sphere(1.0f, 1.0f, 0.0f, 0.5f)));
	s->addObject(new Object(glm::vec3(1.0f, 0.0f, 0.0f), 0.50f, 1.0f, 50.0f, 1.0f, 0.0f, new Sphere(1.5f, 1.5f, 0.0f, 0.5f)));
	s->addObject(new Object(glm::vec3(1.0f, 0.0f, 0.0f), 0.50f, 1.0f, 50.0f, 1.0f, 0.0f, new Plane(glm::vec3(0.01f), glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f,1.0f,-1.0f))));
	//s->addLight(createLight(glm::vec3(10.0f), glm::vec3(1.0f)));
	s->addAreaLight(createLight(glm::vec3(10.0f), glm::vec3(1.0f)), glm::vec3(0.0f, 0.0f, 0.08f), glm::vec3(-0.08f, 0.0f, 0.0f), 10);
	//s->addLight(createLight(glm::vec3(4.0f,0.0f,5.0f), glm::vec3(1.0f)));
	s->setCamera(new Camera(glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), PI / 2, resx, resy));
}

void printVec3(glm::vec3 vec) {
	std::cout << vec.x << ", " << vec.y << ", " << vec.z << std::endl;
}

void testTriangle() {
	std::cout << "Test1" << std::endl;
	Ray ray1;
	ray1.point = glm::vec3(0,0,0);
	ray1.direction = glm::vec3(-1,0,0);
	Triangle t1(glm::vec3(0,-2,-2), glm::vec3(0,2,-2), glm::vec3(0,-2,2));
	assert(t1.checkIntersection(&ray1) != nullptr);

	std::cout << "Test2" << std::endl;
	Ray ray2;
	ray2.point = glm::vec3(4,-2.2,1);
	ray2.direction = glm::vec3(-1,0,0);
	Triangle t2(glm::vec3(0,-2,-2), glm::vec3(0,2,-2), glm::vec3(0,-2,2));
	assert(t2.checkIntersection(&ray2) == nullptr);

	std::cout << "Test2" << std::endl;
	Ray ray3;
	ray3.point = glm::vec3(4,-2.2,1);
	ray3.direction = glm::vec3(-1,0,0);
	Triangle t3(glm::vec3(0,0,0), glm::vec3(0,4,0), glm::vec3(0,0,4));
	assert(t3.checkIntersection(&ray3) != nullptr);
}

int main(int argc, char *argv[]) {
	const char * fileName = "resources/depthOfField.nff";
	// read the file name from the argument if any given
	if(argc >= 2) {
		fileName = argv[1];
	}
	
	std::cout << argc << ": " << fileName << std::endl;
	/** /
	Scene * scene = new Scene();
	test(scene);
	/** /
	testTriangle();
	/**/
	Scene * scene = NFFLoader::createScene(fileName);
	/** /
	Raytracer raytracer(scene);
	RecursiveAntialising antialising(&raytracer,8);
	renderScene(&antialising, scene->resX(), scene->resY());
	/**/
	Raytracer raytracer(scene);
	DepthOfField depthOfField(&raytracer, 2.0f,0.3f,2);
	renderScene(&raytracer, scene->resX(), scene->resY());
	/**/
	return 0;
}