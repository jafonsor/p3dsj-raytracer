#include "BufferedPixelDrawer.h"

BufferedPixelDrawer::BufferedPixelDrawer(PixelDrawer * pixelDrawer, int sizeX, int sizeY)
	: _wrappedDrawer(pixelDrawer), _colorBuffer(), _savedValue()
{
	_colorBuffer = new glm::vec3*[sizeX]();
	for(int i = 0; i < sizeX; i++) {
		_colorBuffer[i] = new glm::vec3[sizeY];
	}
	_savedValue = new bool*[sizeX]();
	for(int i = 0; i < sizeX; i++) {
		_savedValue[i] = new bool[sizeY]();
		for(int j = 0; j < sizeY; j++) {
			_savedValue[i][j] = false;
		}
	}
}

BufferedPixelDrawer::~BufferedPixelDrawer() {
	delete _colorBuffer;
}

glm::vec3 BufferedPixelDrawer::drawPixel(int x, int y) {
	if(!_savedValue[x][y]) {
		_colorBuffer[x][y] = _wrappedDrawer->drawPixel(x,y);
	}
	return _colorBuffer[x][y];
}