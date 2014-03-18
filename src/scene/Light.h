#ifndef LIGHT_H
#define LIGHT_H

#include<glm.hpp>

typedef struct light {
	glm::vec3 position;
	glm::vec3 color;
} Light;

Light *  createLight(glm::vec3 position, glm::vec3 color);

#endif