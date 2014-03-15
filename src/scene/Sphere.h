#ifndef SPHERE_H
#define SPHERE_H

#include "Geometry.h"

class Sphere : Geometry {
	Point _center;
	float _radius;

public:
	Sphere(float x, float y, float z, float r);
	
	Point * checkIntersection(Ray * ray);
};

#endif