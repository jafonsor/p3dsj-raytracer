#include <stdlib.h> 
#include <iostream>
#include <list>
#include <thread>
#include <stdio.h> 
#include <GL/glut.h> 
#include <glm.hpp>
#include <mutex>
#include "DrawAPI.h"
#include "RecursiveAntialising.h"
#include "scene/Scene.h" 

#define MAX_DEPTH 6 
 
PixelDrawer * pixelDrawer;
int res_x, res_y;
float backgroundR, backgroundG, backgroundB;

// for storing the threads that are drawing the pixels
std::list<std::thread*> threads;
glm::vec3 savedPixels[1000][1000];
 
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
}

void threadedDrawPoint(int x, int y, float r, float g, float b) {
	static std::mutex m;
	m.lock();
	drawPoint(x, y, r, g, b);
	m.unlock();
}

void savePixel(int x, int y, glm::vec3 color) {
	savedPixels[x][y] = color;
}

void printPixels() {
	glm::vec3 c;
	for(int i = 0; i < res_x; i++) {
		for(int j = 0; j < res_y; j++) {
			c = savedPixels[i][j];
			drawPoint(i,j, c.r, c.g, c.b);
		}
	}
}


void threadedPixel(int x, int y) {
	glm::vec3 color = pixelDrawer->drawPixel(x,y);
	savePixel(x,y,color);
	//drawPoint(x,y,color.r,color.g,color.b);
}

void threadedColumns(int ci, int cf, int lines) {
	for(int c = ci; c < cf; c++) {
		for(int l = 0; l < lines; l++) {
			threadedPixel(c,l);
		}
	}
}

void multi_threaded_draw_scene() {
	// devide the columns by eight threads
	int numberOfThreads = 8;
	int columnsByThread = res_x / numberOfThreads;
	int leftColumns     = res_x - (numberOfThreads-1)*columnsByThread;

	std::thread * th;
	int t, ci,cf;
	for(t = 0; t < numberOfThreads - 1; t++) {
		ci = t*columnsByThread;
		cf = ci + columnsByThread;
		std::cout << t << ":" << ci << ", " << cf << std::endl;
		th = new std::thread(threadedColumns, ci,cf,res_y);
		threads.push_back(th);
	}

	ci = t*columnsByThread;
	cf = ci + leftColumns;
	std::cout << t << ":" << ci << ", " << cf << std::endl;
	th = new std::thread(threadedColumns, ci,cf,res_y);
	threads.push_back(th);

	// join threads
	std::list<std::thread*>::iterator it;
	for(it = threads.begin(); it != threads.end(); it++) {
		(*it)->join();
		delete (*it); // the thread objects is no longer needed
	}
	threads.clear();

	printPixels();
}

void sequencial_draw_scene() {
	for(int i = 0; i < res_x; i++) {
		for(int j = 0; j < res_y; j++) {
			glm::vec3 color = pixelDrawer->drawPixel(i,j);
			drawPoint(i,j,color.r,color.g,color.b);
		}
	}
}
 
// Draw function by primary ray casting from the eye towards the scene's objects 
void drawScene() 
{ 
	// multi_threaded_draw_scene();
	sequencial_draw_scene();
	glFlush();

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
 