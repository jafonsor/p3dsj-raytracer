#include <iostream>

#include "Triangle.h"

Triangle::Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2)
	: _v0(v0), _v0v1(v1 - v0), _v0v2(v2 - v0), _plane(v0, v1, v2)
{
	// empty
}

Intersection * Triangle::checkIntersection(Ray * ray) {
	//if(ray->direction.x > 0 && ray->direction.y > 0 && ray->direction.z > 0)
		std::cout << "ray: " << ray->direction.x << ", " << ray->direction.y << ", " << ray->direction.z << std::endl;
	Intersection * inter = _plane.checkIntersection(ray);
	if(inter == nullptr) {
		// the ray doesn't intersect the triangle's plane
		return nullptr;
	}

	// Use the Didier Badouel algorithm to detect intersections with triangles

	// project the triangle on 2D
	int i1, i2;
	float absx = glm::abs(ray->point.x);
	float absy = glm::abs(ray->point.y);
	float absz = glm::abs(ray->point.z);
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

	float u0 = ray->point[i1] - _v0[i1];
	float u1 = _v0v1[i1];
	float u2 = _v0v2[i1];

	float v0 = ray->point[i2] - _v0[i2];
	float v1 = _v0v1[i2];
	float v2 = _v0v2[i2];

	float alpha, beta;

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

	/*
	float alpha = glm::determinant(glm::mat2(u0,v0,u2,v2)) 
	              / glm::determinant(glm::mat2(u1,v1,u2,v2));
	float beta  = glm::determinant(glm::mat2(u1,v1,u0,v0))
	              / glm::determinant(glm::mat2(u1,v1,u2,v2));
	*/

	if(alpha + beta <= 1 && alpha > 0 && beta > 0) {
		// the point belongs to the triangle
		return inter;
	} else {
		return nullptr;
	}


}