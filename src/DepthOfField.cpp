#include"DepthOfField.h"
#include <random> 

DepthOfField::DepthOfField(Raytracer * wrappedDrawer, float focalDistanceRatio, float lensRadius, int numOfSamples) 
: _wrappedDrawer(wrappedDrawer), _lensRadius(lensRadius), _numOfSamples(numOfSamples)
{
	_focalDistance = wrappedDrawer->getScene()->getCamera()->getDf()  * focalDistanceRatio;
}

glm::vec3 DepthOfField::drawPixel(float x, float y) {
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(-_lensRadius, _lensRadius);
	Camera * cam = _wrappedDrawer->getScene()->getCamera();
	
	Ray primaryRay = cam->getPrimaryRay(x, y);
	float t = -_focalDistance / (glm::dot(cam->getZe(), primaryRay.direction));

	glm::vec3 p = primaryRay.f(t);

	glm::vec3 u = cam->getXe();
	glm::vec3 v = cam->getYe();

	glm::vec3 colorAcm = glm::vec3(0.0f);

	for (int i = 0; i < _numOfSamples; i++) {
		float rx = distribution(generator);
		float ry = distribution(generator);
		glm::vec3 l = (_lensRadius * rx) * u + (_lensRadius * ry) * v + cam->getEye();
		Ray ray;
		ray.point = l;
		ray.direction = glm::normalize(p - l);
		colorAcm += _wrappedDrawer->trace(&ray,3);
	}
	colorAcm = colorAcm * (1.0f  / _numOfSamples);

	return colorAcm;
}