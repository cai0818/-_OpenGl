/*
#include<GL/glut.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<windows.h>
#include<conio.h>
#include <thread>
#include<math.h>

int mainWindow;

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 30, -10, 30);
}

void show_myPoints() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 1.0);
	glRectf(0,0,1,1);
	glColor3f(0,0,255);
	glRectf(3,3,5,5);
	glFlush();
	
}



int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(300, 100);
	glutInitWindowSize(800, 800);
	mainWindow = glutCreateWindow("Display Points");
	init();
	glutDisplayFunc(show_myPoints);
	glutMainLoop();
	return 0;
}

*/