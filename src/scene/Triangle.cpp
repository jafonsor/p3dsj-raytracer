#include <iostream>

#include "Triangle.h"

float max(float a, float b, float c) {
	if(a > b && a > c) {
		return a;
	} else if(b > c) {
		return b;
	} else {
		return c;
	}
}

float min(float a, float b, float c) {
	if(a < b && a < c) {
		return a;
	} else if(b < c) {
		return b;
	} else {
		return c;
	}
}

Triangle::Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2)
	: _v0(v0), _v0v1(v1 - v0), _v0v2(v2 - v0), _plane(v0, v1, v2)
{
	float maxX = max(v0.x,v1.x,v2.x);
	float maxY = max(v0.y,v1.y,v2.y);
	float maxZ = max(v0.z,v1.z,v2.z);

	_maxCorner = glm::vec3(maxX,maxY,maxZ);

	float minX = min(v0.x,v1.x,v2.x);
	float minY = min(v0.y,v1.y,v2.y);
	float minZ = min(v0.z,v1.z,v2.z);

	_minCorner = glm::vec3(maxX,maxY,maxZ);
}

Intersection * Triangle::checkIntersection(Ray * ray) {
	Intersection * inter = _plane.checkIntersection(ray);
	if(inter == nullptr) {
		// the ray doesn't intersect the triangle's plane
		return nullptr;
	}

	// Use the Didier Badouel algorithm to detect intersections with triangles

	// project the triangle on 2D
	int i1, i2;
	float absx = glm::abs(inter->normal.x);
	float absy = glm::abs(inter->normal.y);
	float absz = glm::abs(inter->normal.z);
	if(absx > absy && absx > absz) {
		i1 = 1; // y
		i2 = 2; // z
	} else if(absy > absz) {
		i1 = 0; // x
		i2 = 2; // z
	} else {
		i1 = 0; // x
		i2 = 1; // y
	}

	float u0 = inter->position[i1] - _v0[i1];
	float u1 = _v0v1[i1];
	float u2 = _v0v2[i1];

	float v0 = inter->position[i2] - _v0[i2];
	float v1 = _v0v1[i2];
	float v2 = _v0v2[i2];

	float alpha = 0, beta = 0;

	if( u1 == 0) {
		beta = u0 / u2;
		if(0 <= beta && beta <= 1) {
			alpha = (v0 - beta*v2)/v1;
		}
	} else {
		beta = (v0*u1 - u0*v1) / (v2*u1 - u2*v1);
		if(0 <= beta && beta <= 1) {
			alpha = (u0 - beta*u2)/u1;
		}
	}

	if(alpha + beta <= 1 && alpha > 0 && beta > 0) {
		// the point belongs to the triangle
		return inter;
	} else {
		delete inter;
		return nullptr;
	}


}

glm::vec3 Triangle::getMaxCorner() {
	return _maxCorner;
}

glm::vec3 Triangle::getMinCorner() {
	return _minCorner;
}