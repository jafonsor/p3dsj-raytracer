#include "scene/Scene.h"
#include "scene/Sphere.h"
#include "Raytracer.h"
#include "DrawAPI.h"
#include "NFFLoader.h"

#define PI  3.1415926535897f

void test(Scene * s) {
	int resx = 500;
	int resy = 500;
	Ray ray;
	s->addObject(new Object(glm::vec3(0.0f,1.0f,0.0f),1.0f,1.0f,10.0f,new Sphere(0.0f, 0.0f, 0.0f, 1.0f)));
	s->addObject(new Object(glm::vec3(0.0f, 0.0f, 1.0f), 1.0f, 1.0f, 10.0f,new Sphere(1.0f, 0.5f, 1.0f, 1.0f)));
	s->addObject(new Object(glm::vec3(1.0f, 0.0f, 0.0f), 1.0f, 1.0f, 10.0f, new Sphere(2.0f, 0.7f, 1.5f, 0.1f)));
	s->addLight(createLight(glm::vec3(10.0f), glm::vec3(1.0f)));
	s->addLight(createLight(glm::vec3(4.0f,0.0f,5.0f), glm::vec3(1.0f)));
	s->setCamera(new Camera(glm::vec3(4.0f,0.0f,0.0f), glm::vec3(1.5f,0.0f,0.0f), glm::vec3(0.0f, 0.0f, 1.0f), PI / 2, resx, resy));
	ray.point = glm::vec3(2.0f,0.0f,0.0f);
	ray.direction = glm::normalize(glm::vec3(0.0f, 1.2f, 0.0f) - ray.point);
	s->checkIntersection(&ray);
}

int main(void) {
	int resx = 500;
	int resy = 500;
	//Scene * scene = NFFLoader::createScene("resources/test.nff");
	Scene * scene = new Scene();
	test(scene);
	Raytracer raytracer(resx, resy, scene);
	renderScene(&raytracer, resx, resy);
	return 0;
}