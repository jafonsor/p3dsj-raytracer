#ifndef SCENE_H
#define SCENE_H

#include "Object.h"
#include <vector>
#include "Intersection.h"

class Scene {
	std::vector<Object*> _objects;

public:
	Scene();

	// If no intersection was found returns null
	Intersection * checkIntersection(Ray * ray);

	void addObject(Object * object);
};

#endif