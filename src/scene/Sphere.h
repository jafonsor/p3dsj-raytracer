#ifndef SPHERE_H
#define SPHERE_H

#include "Geometry.h"
#include "Ray.h"
#include<glm.hpp>

class Sphere : public Geometry {
	glm::vec3 _center;
	float _radius;

public:
	Sphere(float x, float y, float z, float r);
	Intersection * checkIntersection(Ray * ray);

	// Bounding corners of the geometry.
	glm::vec3 getMaxCorner();
	glm::vec3 getMinCorner();
};

#endif