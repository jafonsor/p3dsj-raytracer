#ifndef SCENE_H
#define SCENE_H

#include "Object.h"

// Information about an intersection
typedef struct intersection {
	Object * obj, // object that was intersected
	Point  * pnt  // point of intersection
} Intersection;

class Scene {
	std::vector<Object*> _objects;

public:
	Scene();

	// If no intersection was found returns null
	Intersection * checkIntersection(Ray * ray);

	void addObject(Object * object);
};

#endif