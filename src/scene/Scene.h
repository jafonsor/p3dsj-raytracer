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
};

#endif