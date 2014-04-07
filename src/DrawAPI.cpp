#include <stdlib.h> 
#include <GL/glut.h> 
#include <iostream> 
#include <stdio.h> 
#include <glm.hpp>
#include "RecursiveAntialising.h"
#include "scene/Scene.h" 
#include "DrawAPI.h"

#define MAX_DEPTH 6 
 
PixelDrawer * pixelDrawer;
int res_x, res_y;
float backgroundR, backgroundG, backgroundB;
 
void reshape(int w, int h) 
{ 
	glClearColor(backgroundR, backgroundG, backgroundB, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT); 
	glViewport(0, 0, w, h); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 

	gluOrtho2D(0, res_x-1, 0, res_y -1); 
	glMatrixMode (GL_MODELVIEW); 
	glLoadIdentity(); 
} 


void drawPoint(int x, int y, float r, float g, float b) {
	glBegin(GL_POINTS); 
	glColor3f(r, g, b); 
	glVertex2f(x, y); 
	glEnd(); 
	glFlush(); 
}
 
// Draw function by primary ray casting from the eye towards the scene's objects 
void drawScene() 
{ 
	glm::vec3 color;
	for(int i = 0; i < res_x; i++) {
		for(int j = 0; j < res_y; j++) {
			color = pixelDrawer->drawPixel(i,j);
			drawPoint(i,j,color.r,color.g,color.b);
		}
	}
	pixelDrawer->print();
	printf("Terminou!\n"); 
} 
 
int renderScene(PixelDrawer * in_pixelDrawer, int in_res_x, int in_res_y)
{ 
	pixelDrawer = in_pixelDrawer;
	backgroundR = 1.0f;
	backgroundG = 1.0f;
	backgroundB = 1.0f;
	res_x = in_res_x;
	res_y = in_res_y;
	printf("resx = %d resy= %d.\n", res_x, res_y);

	int argc = 1;
	char * argv[1];
	argv[0] = "raytraycer";

	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 

	glutInitWindowSize(res_x, res_y); 
	glutInitWindowPosition(100, 100); 
	glutCreateWindow("PSJ - Ray Tracing"); 
	glClearColor(0.0f, 0.0f, 0.0f, 1); 
	glClear(GL_COLOR_BUFFER_BIT); 

	glutReshapeFunc(reshape); 
	glutDisplayFunc(drawScene); 
	glDisable(GL_DEPTH_TEST); 

	glutMainLoop(); 
	return 0; 
} 
 