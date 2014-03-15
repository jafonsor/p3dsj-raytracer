#include"Raytracer.h"
#include"DrawAPI.h"

Raytracer::Raytracer(int resX, int resY, Scene * scene) : _resX(resX), _resY(resY), _scene(scene) { }

void Raytracer::drawScene() {
	Ray r;
	Intersection * inter;
	Camera * cam = _scene->getCamera();
	for (int i = 0; i < _resX; i++) {
		for (int j = 0; j < _resY; j++) {
			r = cam->getPrimaryRay(i, j);
			inter = _scene->checkIntersection(&r);
			if (inter != nullptr) {
				Color * c = inter->object->getColor();
				drawPoint(i, j, c->r, c->g, c->b);
			}
		}
	}
}
