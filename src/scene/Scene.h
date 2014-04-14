#ifndef SCENE_H
#define SCENE_H

#include "Object.h"
#include <vector>
#include "Intersection.h"
#include "Camera.h"
#include "Light.h"
#include "Grid.h"

class Scene {
	Grid _grid;
	std::vector<Object*> _planes;
	std::vector<Light *> _lights;
	Camera * _camera;
	glm::vec3 _background;

public:
	Scene();

	// If no intersection was found returns null
	Intersection * checkIntersection(Ray * ray);

	void addObject(Object * object);
	void addPlane(Object * plane);
	void addLight(Light * light);
	void addAreaLight(Light * areaLight, glm::vec3 u, glm::vec3 v, int n);
	void setCamera(Camera * camera);
	std::vector<Light *> getLights();
	std::vector<Light *> getLights(Intersection * intersection);
	Camera *  getCamera();
	void setBackground(glm::vec3 color);
	glm::vec3 background();
	int resX();
	int resY();
};

#endif