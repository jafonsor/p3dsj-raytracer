#ifndef OBJECT_H
#define OBJECT_H

#include "Ray.h"
#include "Intersection.h"
#include "Geometry.h"

class Object {
	Geometry *_geometry;

public:
	glm::vec3 color;
	float kd, ks, shininess;
	float transmittance, indexOfRefraction;

	Object(glm::vec3 color,float kd, float ks, float shininess,Geometry * geometry);
	Object(glm::vec3 color, float kd, float ks, float shininess, float transmittance, float indexOfRefraction, Geometry * geometry);
	Intersection * checkIntersection(Ray * ray);
};

#endif