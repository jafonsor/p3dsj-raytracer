#ifndef BUFFERED_PIXEL_DRAWER
#define BUFFERED_PIXEL_DRAWER

#include <glm.hpp>
#include "PixelDrawer.h"

/**
 * Works as a wrapper to another drawer. Stores the drawPixel
 * result of the inner drawer so that two calls for the same
 * pixel require only one calculation.
 */
class BufferedPixelDrawer : public PixelDrawer {
	PixelDrawer * _wrappedDrawer;
	glm::vec3 **_colorBuffer;
	bool **_savedValue;
public:
	BufferedPixelDrawer(PixelDrawer * wrappedDrawer, int sizeX, int sizeY);
	~BufferedPixelDrawer();
	glm::vec3 drawPixel(int x, int y);
};

#endif