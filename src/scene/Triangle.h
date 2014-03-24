#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Plane.h"

class Triangle : public Geometry {
	glm::vec3 _v0, _v0v1, _v0v2;
	Plane _plane;
public:
	Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
	Intersection * checkIntersection(Ray * ray);
};

#endif