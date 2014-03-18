#include "Light.h"

Light * createLight(glm::vec3 position, glm::vec3 color){
	Light* l = new Light;
	l->position = position;
	l->color = color;
	return l;
}