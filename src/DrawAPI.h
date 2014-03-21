#ifndef DRAWAPI_H
#define DRAWAPI_H
#include"Raytracer.h"

int renderScene(Raytracer * raytracer,
	            int res_x, int res_y,
	            // background color
	            float r, float g, float b); 
void drawPoint(int x, int y, float r, float g, float b);

#endif