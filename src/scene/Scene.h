#ifndef SCENE_H
#define SCENE_H

#include "Object.h"
#include <vector>
#include "Intersection.h"
#include "Camera.h"
#include "Light.h"

class Scene {
	std::vector<Object*> _objects;
	std::vector<Light *> _lights;
	Camera * _camera;
	glm::vec3 _background;

public:
	Scene();

	// If no intersection was found returns null
	Intersection * checkIntersection(Ray * ray);

	void addObject(Object * object);
	void addLight(Light * light);
	void setCamera(Camera * camera);
	std::vector<Light *> getLights();
	std::vector<Light *> getLights(Intersection * intersection);
	Camera *  getCamera();
	void setBackground(glm::vec3 color);
	glm::vec3 background();
	int resX();
	int resY();
};

#endif