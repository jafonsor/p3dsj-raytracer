#ifndef SCENE_H
#define SCENE_H

#include "Object.h"
#include <vector>
#include "Intersection.h"
#include "Camera.h"

class Scene {
	std::vector<Object*> _objects;
	Camera * _camera;

public:
	Scene();

	// If no intersection was found returns null
	Intersection * checkIntersection(Ray * ray);

	void addObject(Object * object);
	void setCamera(Camera * camera);
	Camera *  getCamera();
};

#endif