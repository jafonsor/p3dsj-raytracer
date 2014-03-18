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
	s->addObject(new Object(glm::vec3(0.0f,1.0f,0.0f),0.0f,0.0f,0.0f,new Sphere(0.0f, 0.0f, 0.0f, 1.0f)));
	s->addObject(new Object(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, 0.0f, 0.0f,new Sphere(0.0f, 0.5f, 0.0f, 1.0f)));
	s->setCamera(new Camera(glm::vec3(2.0f,0.0f,0.0f), glm::vec3(1.5f,0.0f,0.0f), glm::vec3(0.0f, 0.0f, 1.0f), PI / 2, resx, resy));
	ray.point = glm::vec3(2.0f,0.0f,0.0f);
	ray.direction = glm::normalize(glm::vec3(0.0f, 1.2f, 0.0f) - ray.point);
	s->checkIntersection(&ray);
}

int main(void) {
	int resx = 500;
	int resy = 500;
	Scene * scene = NFFLoader::createScene("resources/test.nff");
	//test(&scene);
	Raytracer raytracer(scene);
	renderScene(&raytracer, scene->resX(), scene->resY());
	return 0;
}