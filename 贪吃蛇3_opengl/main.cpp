
/*

#include<GL/glut.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<windows.h>
#include<conio.h>
#include <thread>
#define SNAKE_NUM 500
int speed, dir, size;
POINT coor[SNAKE_NUM][4];
//枚举
enum DIR {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

//键盘控制
void myKeyBorad() {
	if (_kbhit()) {
		switch (_getch()) {

		case 'w':
		case 'W':
		case 72:
			exit(0);
			if (dir != DOWN) {
				dir = UP;

			}
			break;
		case 's':
		case 80:
			if (dir != UP) {
				dir = DOWN;
			}
			break;
		case 'A':
		case 'a':
		case 75:
			if (dir != RIGHT) {
				dir = LEFT;
			}

			break;
		case 'D':
		case 'd':
		case 77:
			if (dir != LEFT) {
				dir = RIGHT;
			}

			break;


		default:
			break;

		}


	}

}
//第一次绘制贪吃蛇
void show_myPoints() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.6, 0.5, 0.2);
	glPointSize(1);

	for (int i = 0; i <= size;i++) {
		glRectf(coor[i][0].x, coor[i][0].y, coor[i][1].x, coor[i][1].y);
	}
		
	
	glFlush();
	
	
}
//初始化
void init()
{
	size = 3;
	speed = 12;
	dir = RIGHT;
	coor[0][0].x = 0;
	coor[0][0].y = 0;//第一个(0.0)
	coor[0][1].x = 10;
	coor[0][1].y = 10;//第三个(10,10)
	for (int i = 1; i <=size;i++) {
			coor[i][0].x = coor[i - 1][0].x - 12;
			coor[i][1].x = coor[i - 1][1].x - 12;
			coor[i][0].y = coor[i - 1][0].y;
			coor[i][1].y = coor[i - 1][1].y;
	}
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 300, -100,300);
	
}
//后续贪吃蛇坐标修改
void myPoints() {
	
		for (int i = size; i > 0; i--)
		{
			coor[i][0].x = coor[i - 1][0].x;
			coor[i][0].y = coor[i - 1][0].y;
			coor[i][1].x = coor[i - 1][1].x;
			coor[i][1].y = coor[i - 1][1].y;
		}
		switch (dir)
		{
		case UP:
			coor[0][0].y -= speed;
			coor[0][1].y -= speed;
			break;
		case DOWN:
			coor[0][0].y += speed;
			coor[0][1].y += speed;
			break;
		case LEFT:
			coor[0][0].x -= speed;
			coor[0][1].x -= speed;
			break;
		case RIGHT:
			coor[0][0].x += speed;
			coor[0][1].x += speed;
			break;
		default:
			break;
		}
		glutPostRedisplay();
	
	
}
int main(int argc,char* argv[]) {

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(300,100);
	glutInitWindowSize(600,500);
	glutCreateWindow("Display Points");
	init();
	while (1) {
		std::thread d2(myPoints);
		show_myPoints();
		d2.join();
		std::thread d1(myKeyBorad);
		d1.join();
		//glutKeyboardFunc();
		Sleep(1000);
		
	
	}
		
	
	return 0;
}

*/