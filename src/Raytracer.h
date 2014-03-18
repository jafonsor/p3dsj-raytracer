#ifndef RAYTRACER_H
#define RAYTRACER_H
#include "scene/Scene.h"

class Raytracer {
	int _resX, _resY;
	Scene * _scene;
public:
	Raytracer(int resX, int resY,Scene * scene);
	void drawScene();
};

#endif