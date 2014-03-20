#ifndef LIGHT_H
#define LIGHT_H

#include<glm.hpp>


const glm::vec3 DEFAULT_POSITION = glm::vec3(0,0,0);
// default light color is white
const glm::vec3 DEFAULT_COLOR_LIGHT = glm::vec3(1,1,1);

typedef struct light {
	glm::vec3 position;
	glm::vec3 color;

	light()
			: position(DEFAULT_POSITION), color(DEFAULT_COLOR_LIGHT) { /* empty */ }

	light(glm::vec3 position)
		: position(position), color(DEFAULT_COLOR_LIGHT) { /* empty */ }

	light(glm::vec3 position, glm::vec3 color)
		: position(position), color(color) { /* empty */ }

} Light;

Light *  createLight(glm::vec3 position, glm::vec3 color);

#endif
