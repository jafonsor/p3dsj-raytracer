#ifndef DEPTH_OF_FIELD_H
#define DEPTH_OF_FIELD_H

#include <glm.hpp>
#include "PixelDrawer.h"
#include "Raytracer.h"

class DepthOfField : public PixelDrawer {
	Raytracer * _wrappedDrawer;
	float _focalDistance, _lensRadius;
	int _numOfSamples;
public:
	DepthOfField(Raytracer * wrappedDrawer, float focalDistanceRatio, float lensRadius, int numOfSamples);
	inline glm::vec3 drawPixel(float x, float y);
};

#endif