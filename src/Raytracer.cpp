#include"Raytracer.h"
#include"DrawAPI.h"
#include<iostream>

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
				glm::vec3 c = inter->object->color;
				/*
					ambient color
				*/
				c = c * 0.1f;
				std::vector<Light *> lights = _scene->getLights();
				for (std::vector<Light*>::iterator it = lights.begin(); it != lights.end(); it++) {
					glm::vec3 l = (*it)->position - inter->position;
					l = glm::normalize(l);
					float lambert = glm::dot(inter->normal, l);
					if (lambert > 0) {
						c += (*it)->color * inter->object->color * lambert * inter->object->kd;

						glm::vec3 r = glm::reflect(-l, inter->normal);
						glm::vec3 eyeDir = glm::normalize(cam->getEye() - inter->position);

						float dot = glm::max(glm::dot(r, eyeDir), 0.0f);
						float specular = glm::pow(dot, inter->object->shininess);

						c += (*it)->color * inter->object->color * specular * inter->object->ks;
					}
				}

				
				drawPoint(i, j, c.r, c.g, c.b);
			}
			else {
				drawPoint(i, j, 0.0f,0.0f,0.0f);
			}
		}
	}
}
