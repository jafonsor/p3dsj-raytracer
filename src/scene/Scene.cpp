#include "Scene.h"
#include <float.h>

Scene::Scene() : _grid(), _lights(), _background(0.0f) {}

// If no intersection was found returns null
Intersection * Scene::checkIntersection(Ray * ray) {
	Intersection * result = _grid.checkIntersection(ray);
	// If the ray doesn't intersect any object on the grid
	// test an intersection with the planes.
	if(result == nullptr) {
		std::vector<Object*>::iterator it;
		Intersection * intersectionPoint;
		float minDist = FLT_MAX;
		for(it = _planes.begin(); it != _planes.end(); it++) {
			intersectionPoint = (*it)->checkIntersection(ray);
			if(intersectionPoint != nullptr && intersectionPoint->distanceToEye < minDist) {
				delete result;
				result = intersectionPoint;
				minDist = result->distanceToEye;
			}
		}
	}
	return result;
}

void Scene::addObject(Object * object) {
	_grid.addObject(object);
}

void Scene::addPlane(Object * plane) {
	_planes.push_back(plane);
}

void Scene::addLight(Light * light) {
	_lights.push_back(light);
}


void Scene::addAreaLight(Light * areaLight, glm::vec3 u, glm::vec3 v, int n) {
	glm::vec3 p = areaLight->position;
	int ite = (int)floorf(sqrt(1.0f * n));
	float h = 1 / sqrt(1.0f * n);
	float prob = 1.0f / n;
	for (int i = 0; i < ite; i++) {
		for (int j = 0; j < ite; j++) {
			glm::vec3 w = p + u * (((2.0f - h) * i) / h) + v * (((2.0f - h) * j)/ h);
			addLight(createLight(w, areaLight->color * prob));
		}
	}
}

void Scene::setCamera(Camera * camera) {
	_camera = camera;
}

Camera *  Scene::getCamera() {
	return _camera;
}

std::vector<Light *> Scene::getLights() {
	return _lights;
}

std::vector<Light *> Scene::getLights(Intersection * intersection) {
		float epsilon = 1E-3;
		std::vector<Light *> result = std::vector<Light *>();
		std::vector<Light *> lights = this->getLights();

		for (std::vector<Light*>::iterator it = lights.begin(); it != lights.end(); it++) {
			glm::vec3 l = (*it)->position - intersection->position;
			l = glm::normalize(l);
			Ray r;
			r.point = intersection->position + l * epsilon;
			r.direction = l;

			Intersection * inter = this->checkIntersection(&r);

			if (inter == nullptr) {
				result.push_back(*it);
			}
			else if (inter->object == intersection->object) {
				result.push_back(*it);
			}
			delete inter;
		}
		return result;
	}

void Scene::setBackground(glm::vec3 color) {
	_background = color;
}

glm::vec3 Scene::background() {
	return _background;
}

int Scene::resX() {
	return _camera->resX();
}

int Scene::resY() {
	return _camera->resY();
}