#ifndef RAYTRACER_H
#define RAYTRACER_H
#include "scene/Scene.h"

class Raytracer {
	Scene * _scene;
public:
	Raytracer(Scene * scene);
	void drawScene();
};

#endif