#ifndef PIXEL_DRAWER_H
#define PIXEL_DRAWER_H

#include <glm.hpp>

class PixelDrawer {
public:
	virtual glm::vec3 drawPixel(int x, int y) = 0;
};

#endif