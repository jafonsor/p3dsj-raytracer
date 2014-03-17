#ifndef RAY_H
#define RAY_H

#include<glm.hpp>

typedef struct ray {
	glm::vec3 point;
	glm::vec3 direction;
	glm::vec3 f(float t) {
		return point + direction * t;
	}
} Ray;

#endif