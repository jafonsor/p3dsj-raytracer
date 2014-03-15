#include "Sphere.h"

Sphere::Sphere(float x, float y, float z, float r)
	: _center({x,y,z}), _radius(r) 
{
	// empty
}

Intersection * Sphere::checkIntersection(Ray * ray) {
	
}