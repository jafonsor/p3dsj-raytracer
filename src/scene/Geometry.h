#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Intersection.h"
#include "Ray.h"

class Geometry {
public:
	// Returns null if the ray doesn't intersect the object
	virtual Intersection * checkIntersection(Ray * ray) = 0;

	// Bounding corners of the geometry.
	virtual glm::vec3 getMaxCorner() = 0;
	virtual glm::vec3 getMinCorner() = 0;
};

#endif