#ifndef INTERSECTION_H
#define INTERSECTION_H

#include<glm.hpp>
class Object;

typedef struct intersection {
	glm::vec3 position;
	glm::vec3 normal;
	Object * object;
	float distanceToEye;
} Intersection;


#endif