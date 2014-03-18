#include "Scene.h"
#include <float.h>

Scene::Scene() : _objects(), _lights() {}

// If no intersection was found returns null
Intersection * Scene::checkIntersection(Ray * ray) {
	std::vector<Object*>::iterator it;
	Intersection * intersectionPoint;
	Intersection * result = nullptr;
	float minDist = FLT_MAX;
	for(it = _objects.begin(); it != _objects.end(); it++) {
		intersectionPoint = (*it)->checkIntersection(ray);
		if(intersectionPoint != nullptr && intersectionPoint->distanceToEye < minDist) {
			result = intersectionPoint;
			minDist = result->distanceToEye;
		}
	}
	return result;
}

void Scene::addObject(Object * object) {
	_objects.push_back(object);
}

void Scene::addLight(Light * light) {
	_lights.push_back(light);
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
	}
	return result;
}