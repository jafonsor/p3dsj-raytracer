#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <glm.hpp>
#include "scene/Scene.h"
#include "PixelDrawer.h"

class Raytracer : public PixelDrawer {
	Scene * _scene;
public:
	Raytracer(Scene * scene);
	glm::vec3 trace(Ray * r, int depth);
	glm::vec3 drawPixel(int x, int y);
};

#endif