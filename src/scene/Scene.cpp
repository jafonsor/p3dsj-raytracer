#include "Scene.h"

Scene::Scene() {

}

// If no intersection was found returns null
Intersection * Scene::checkIntersection(Ray * ray) {
	std::vector<Object*>::iterator it;
	Point * intersectionPoint;
	Intersection * result = 0;
	for(it = _objects.begin(); it != _objects.end(); it++) {
		intersectionPoint = (*it)->checkIntersection(ray);
		if(intersectionPoint && intersectionPoint  é o mais proximo) {
			result = new Intersection((*it), intersectionPoint);
		}
	}
	return result;
}

void addObject(Object * object) {
	_objects.push_back(object);
}