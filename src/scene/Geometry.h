#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Intersection.h"
#include "Ray.h"

class Geometry {
	// Returns null if the ray doesn't intersect the object
public:
	virtual Intersection * checkIntersection(Ray * ray);
};

#endif