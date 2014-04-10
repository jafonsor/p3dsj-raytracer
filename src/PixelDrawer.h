#ifndef PIXEL_DRAWER_H
#define PIXEL_DRAWER_H

#include <glm.hpp>

class PixelDrawer {
public:
	virtual glm::vec3 drawPixel(float x, float y) = 0;
	virtual void print();
};

#endif