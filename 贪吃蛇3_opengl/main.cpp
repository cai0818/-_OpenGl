
#include <GL/freeglut.h>
//#include<GL/glut.h>
#include <GLFW/glfw3.h>
#include<iostream>
//#include<windows.h>
#include<conio.h>
#include <thread>
#include<math.h>
#define SNAKE_NUM 500
#define MAX_CHAR        128
int speed, dir, size;
POINT coor[SNAKE_NUM][4];
POINT snake_center_coor[SNAKE_NUM], food_center_coor;
POINT food[2];
int  snake_x_tmp, snake_y_tmp, food_x_tmp, food_y_tmp;
bool food_flag, die, restart;
int Functime_tmp, Functime = 33;
int windows;
//ö��
enum DIR {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

//��ʾ������
void drawString(const  char* str) {
	static  int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) { // ����ǵ�һ�ε��ã�ִ�г�ʼ��
						// Ϊÿһ��ASCII�ַ�����һ����ʾ�б�
		isFirstCall = 0;

		// ����MAX_CHAR����������ʾ�б���
		lists = glGenLists(MAX_CHAR);

		// ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}


//ˢ������
void myPoints(int value) {
	switch (dir)
	{
	case UP:

		coor[0][0].y += speed;
		coor[0][1].y += speed;
		break;
	case DOWN:
		coor[0][0].y -= speed;
		coor[0][1].y -= speed;

		break;
	case LEFT:
		coor[0][0].x -= speed;
		coor[0][1].x -= speed;
		break;
	case RIGHT:
		coor[0][0].x = coor[0][0].x + speed;
		coor[0][1].x = coor[0][1].x + speed;
		break;
	default:
		break;
	}
	for (int i = size; i > 0; i--)
	{

		coor[i][0].x = coor[i - 1][0].x;
		coor[i][0].y = coor[i - 1][0].y;
		coor[i][1].x = coor[i - 1][1].x;
		coor[i][1].y = coor[i - 1][1].y;
	}

	if (!die) {
		glutTimerFunc(8, myPoints, 1);
		//glutSetWindow(mainWindow);
		//glutPostRedisplay();
	}
	//Sleep(200);



}
void myKeyBorad(unsigned char key, int x, int y) {

	switch (key) {

	case 'w':
	case 'W':
	case 72:
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


	//glutSetWindow(mainWindow);
	//glutPostRedisplay();


}
//----------------------------------------------------
void display_string() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2f(0.0f, 0.0f);
	drawString("You die ");

	glutSwapBuffers();
}
//-----------------------------------------------------
void snake_die() {
	if (snake_center_coor[0].x >= 300 + 20 || snake_center_coor[0].x <= -100 + 20 || snake_center_coor[0].y >= 300 || snake_center_coor[0].y <= -100) {
		//display_string();
		die = true;
	}
}


void Calculate_center_coor() {
	if (!die) {
		for (int i = 0; i <= size; i++) {
			snake_x_tmp = coor[i][1].x + coor[i][0].x;
			snake_y_tmp = coor[i][1].y + coor[i][0].y;
			snake_center_coor[i].x = snake_x_tmp / 2;
			snake_center_coor[i].y = snake_y_tmp / 2;
			//----------------------------------//
			food_x_tmp = food[1].x + food[0].x;
			food_y_tmp = food[1].y + food[0].y;
			food_center_coor.x = food_x_tmp / 2;
			food_center_coor.y = food_y_tmp / 2;
		}

	}


}


void menufunc(int data) {

	switch (data) {
	case 1:
		speed = 0;
		break;
	case 2:
		speed = 2;
		break;
	case 3:
		exit(0);
		break;
	case 4:
		restart = true;
		glutDestroyWindow(windows);

		break;

	}

}


void Food() {

	food[0].x = rand() % 200;
	food[0].y = food[0].x;
	food[1].x = food[0].x + 20;
	food[1].y = food[0].y + 20;
	food_flag = true;
	Calculate_center_coor();
	for (int i = 0; i < size; i++) {
		if (snake_center_coor[i].x >= food_center_coor.x - 20 && snake_center_coor[i].x <= food_center_coor.x + 20 && snake_center_coor[i].y >= food_center_coor.y - 20 && snake_center_coor[i].y <= food_center_coor.y + 20) {
			Food();
			printf("---------------------����ʳ�������غϣ���������ʳ�����\n-----------");
		}
	}
}
void Eat_food() {


	if (food_flag && snake_center_coor[0].x >= food_center_coor.x - 10 && snake_center_coor[0].x <= food_center_coor.x + 10 && snake_center_coor[0].y >= food_center_coor.y - 10 && snake_center_coor[0].y <= food_center_coor.y + 10)
	{
		food_flag = false;
		printf("--------------------------�Ե�ʳ���ˣ���������ǰ�߳���%d--------------��ǰʱ��%d-----------\n", size, Functime);
		size++;

	}
	if (!food_flag) {
		Food();
	}
}
void show_myPoints(void)
{

	if (!die) {
		Calculate_center_coor();
		snake_die();
		Eat_food();
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0, 0.0, 1.0);
		glPointSize(1);
		glRectf(coor[0][0].x, coor[0][0].y, coor[0][1].x, coor[0][1].y);
		glColor3f(0.6, 0.5, 0.2);
		for (int i = 1; i <= size; i++) {
			glRectf(coor[i][0].x, coor[i][0].y, coor[i][1].x, coor[i][1].y);
		}
		if (food_flag) {
			glColor3f(1.0, 0.0, 1.0);
			glRectf(food[0].x, food[0].y, food[1].x, food[1].y);

		}
		glutSwapBuffers();
		printf("��ǰ��ͷ��������%d    %d    \n", snake_center_coor[0].x, snake_center_coor[0].y);
		printf("��ǰʳ����������%d    %d    \n", food_center_coor.x, food_center_coor.y);

	}
	if (die) {
		printf("���Ѿ�����\n");
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		gluOrtho2D(-10, 30, -10, 30);
		glColor3f(1.0f, 0.0f, 0.0f);

		glRasterPos2f(125.0f, 165.0f);
		drawString("You die");

		glutSwapBuffers();

	}
	glutPostRedisplay();

}
void init()
{
	restart = false;
	size = 10;
	speed = 2;
	dir = RIGHT;
	die = false;
	srand(GetTickCount64());
	coor[0][0].x = 0;
	coor[0][0].y = 0;//��һ��(0.0)
	coor[0][1].x = 10;
	coor[0][1].y = 10;//������(10,10)

	for (int i = 1; i < size; i++) {
		coor[i][0].x = coor[i - 1][0].x - speed;
		coor[i][1].x = coor[i - 1][1].x - speed;
		coor[i][0].y = coor[i - 1][0].y;
		coor[i][1].y = coor[i - 1][1].y;
	}
	Food();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 300, -100, 300);

}

void a() {

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowPosition(300, 100);

	glutInitWindowSize(800, 800);
	int  mainWindow = glutCreateWindow("̰����");
	windows = glutGetWindow();
	init();
	glutCreateMenu(menufunc);
	glutAddMenuEntry("pause", 1);


	glutAddMenuEntry("continue", 2);

	glutAddMenuEntry("exit", 3);
	glutAddMenuEntry("restart", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(show_myPoints);
	glutTimerFunc(200, myPoints, 1);
	//glutIdleFunc(show_myPoints);
	glutKeyboardFunc(myKeyBorad);
	if (!die) {
		glutMainLoop();
	}



}

int main(int argc, char** argv) {
	printf("wsad���Ʒ����Ҽ���ʾ�˵�--------����������Ϸ\n");
	Sleep(5000);

	glutInit(&argc, argv);
	restart = false;
	std::thread t1(a);
	t1.join();
	//std::atomic::wait();
	while (!die) {

	}

}




