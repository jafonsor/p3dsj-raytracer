#include"Raytracer.h"
#include"DrawAPI.h"
#include<iostream>

Raytracer::Raytracer(Scene * scene) : _scene(scene) { }


float sign(float x) {
	if (x < 0) {
		return -1;
	}
	else if (x > 0) {
		return 1;
	}
	else {
		return 0;
	}
}

Ray * computeRefractedRay(intersection * inter, glm::vec3 v) {
	float epsilon = 1E-3;
	
	Ray * refractedRay = new Ray;
	v = -v;
	float d = sign(glm::dot(v, inter->normal));
	glm::vec3 normal = d * inter->normal;
	glm::vec3 minusOrt = (glm::dot(v, normal) * normal - v);
	
	float sini = glm::length(minusOrt);
	/*
	index of refraction of air is =~ 1 so ni/nr = 1 /nr
	*/
	float sinr;
	if (d < 0) {
		sinr = inter->object->indexOfRefraction * sini;
	}
	else if(d > 0) {
		sinr = (1 / inter->object->indexOfRefraction) * sini;
	}
	float factor = 1 - sinr * sinr;
	if (factor < 0) {
		delete refractedRay;
		return refractedRay = nullptr;
	}
	float cosr = sqrt(factor);
	glm::vec3 t = glm::normalize(minusOrt);
	glm::vec3 refract = cosr * (-normal) + sinr * t;
	refract = glm::normalize(refract);
	refractedRay->point = inter->position + epsilon * refract;
	refractedRay->direction = refract;
	//std::cout << refract.x << std::endl;
	return refractedRay;
}

glm::vec3 Raytracer::trace(Ray * r, int depth) {
	float epsilon = 1E-3;
	Intersection * inter;
	glm::vec3 color;

	depth--;
	inter = _scene->checkIntersection(r);
	if (inter != nullptr) {
		color = inter->object->color;
		/*
		ambient color
		*/
		color = color * 0.05f;
		std::vector<Light *> lights = _scene->getLights(inter);
		for (std::vector<Light*>::iterator it = lights.begin(); it != lights.end(); it++) {
			glm::vec3 l = (*it)->position - inter->position;
			l = glm::normalize(l);
			float lambert = glm::dot(inter->normal, l);
			if (lambert > 0) {
				color += (*it)->color * inter->object->color * lambert * inter->object->kd;

				glm::vec3 r = glm::reflect(-l, inter->normal);
				glm::vec3 eyeDir = glm::normalize(_scene->getCamera()->getEye() - inter->position);

				float dot = glm::max(glm::dot(r, eyeDir), 0.0f);
				float specular = glm::pow(dot, inter->object->shininess);

				color += (*it)->color * inter->object->color * specular * inter->object->ks;
			}
		}
		if (depth < 1) {
			delete inter;
			return color;
		}

		// reflection
		glm::vec3 v = r->direction;
		/**/
		//this is the same as refelect(-v,inter->normal)
		//glm::vec3 r = -v - 2 * glm::dot(-v, inter->normal) * inter->normal;
		/**/
		glm::vec3 reflect = glm::reflect(v, inter->normal);
		/**/
		Ray * reflectedRay = new Ray;
		reflectedRay->point = inter->position + epsilon * reflect;
		reflectedRay->direction = reflect;
		color += inter->object->ks * (1.0f - inter->object->transmittance) * trace(reflectedRay, depth);
		delete reflectedRay;
		

		// refracted ray
		Ray * refractedRay = computeRefractedRay(inter, v);

		if (refractedRay != nullptr) {
			glm::vec3 refractColor = trace(refractedRay, depth);
			color += inter->object->transmittance * refractColor;
			delete refractedRay;
		}
		delete inter;
		return color;
	}
	else {
		delete inter;
		return _scene->background();
	}
}

glm::vec3 Raytracer::drawPixel(float x, float y) {
	Ray r = _scene->getCamera()->getPrimaryRay(x,y);
	return trace( &r, 3);
}

