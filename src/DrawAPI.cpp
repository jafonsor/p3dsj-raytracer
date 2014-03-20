#include <stdlib.h> 
#include <GL/glut.h> 
#include <iostream> 
#include <stdio.h> 
#include "scene/Scene.h" 
#include "DrawAPI.h"
 
#define MAX_DEPTH 6 
 
Raytracer * raytracer;
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
 
// Draw function by primary ray casting from the eye towards the scene's objects 
void drawScene() 
{ 
	raytracer->drawScene();
	printf("Terminou!\n"); 
} 

void drawPoint(int x, int y, float r, float g, float b) {
	glBegin(GL_POINTS); 
	glColor3f(r, g, b); 
	glVertex2f(x, y); 
	//std::cout << x << "   " << y << std::endl;
	glEnd(); 
	glFlush(); 
}
 
int renderScene(Raytracer * in_ratracer, int in_res_x, int in_res_y, float r, float g, float b)
{ 
	raytracer = in_ratracer;
	backgroundR = r;
	backgroundG = g;
	backgroundR = b;
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
	glutCreateWindow("JAP Ray Tracing"); 
	glClearColor(0.0f, 0.0f, 0.0f, 1); 
	glClear(GL_COLOR_BUFFER_BIT); 

	glutReshapeFunc(reshape); 
	glutDisplayFunc(drawScene); 
	glDisable(GL_DEPTH_TEST); 

	glutMainLoop(); 
	return 0; 
} 
 