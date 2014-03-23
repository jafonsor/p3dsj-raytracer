#ifndef PLANE_H
#define PLANE_H

#include "Geometry.h"

class Plane : public Geometry {
  glm::vec3 _normal;
  float _d;

public:
	Plane(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
	Intersection * checkIntersection(Ray * ray);
};

#endif