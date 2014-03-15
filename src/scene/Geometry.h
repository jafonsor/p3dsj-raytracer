#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Scene.h"

class Geometry {
	// Returns null if the ray doesn't intersect the object
	virtual Point * checkIntersection(Ray * ray);
};

#endif