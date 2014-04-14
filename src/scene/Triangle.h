#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Plane.h"

class Triangle : public Geometry {
	glm::vec3 _v0, _v0v1, _v0v2;
	Plane _plane;
	glm::vec3 _maxCorner;
	glm::vec3 _minCorner;
public:
	Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
	Intersection * checkIntersection(Ray * ray);

	// Bounding corners of the geometry.
	glm::vec3 getMaxCorner();
	glm::vec3 getMinCorner();
};

#endif