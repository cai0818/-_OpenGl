/*
* ����������л��߱���ʧ�ܣ�
* ��ȷ���õ���vs2022
* �Լ�ȷ����Ŀ���������Ͱ�����Ŀ¼����ȷ�ģ����������·������
* ���⸽��������Ҫȷ������
* ��ȷ�����еı�������x86�ģ���Ϊ�����ӵ��Ǿ�̬32λ�Ŀ��ļ�
* 64λ�ı�����������ʧ��
*/

#include <GL/freeglut.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<windows.h>
#include<conio.h>
#include <thread>
#include<math.h>
#define SNAKE_NUM 5000
#define MAX_CHAR        128
int speed, dir, size;
// �ṹ���ṩ���깦��
struct Point
{
	int x;
	int y;

	// ����==���ṩ�����ж����ĵ������Ƿ��غ�
	bool operator==(const Point& p)
	{
		if (this->x == p.x && this->y == p.y)
		{
			return true;
		}
		return false;
	}
};
Point coor[SNAKE_NUM][2];
Point snake_center_coor[SNAKE_NUM], food_center_coor;
Point food[2];

int  snake_x_tmp, snake_y_tmp, food_x_tmp, food_y_tmp;
bool food_flag, die, restart, Pause;
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
	// ���û����������ݹ���������.�����Ļ����Ͳ��ݹ�
	if (!die) {
		glutTimerFunc(8, myPoints, 1);
		//glutSetWindow(mainWindow);
		//glutPostRedisplay();
	}
	//Sleep(200);



}

//�󶨼��̣�������֮ǰ��ö�ٽ��й���
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


	


}
//----------------------------------------------------
void display_string() {
	//ָ����ɫ�����������ֵ
	glClearColor(0, 0, 0, 0);

	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);

	//����λ��
	glRasterPos2f(0.0f, 0.0f);
	drawString("You die ");
	//����������
	glutSwapBuffers();
}
//-----------------------------------------------------
void snake_die() {
	if (!Pause) {
	//�ж���ͷ����������x,y�Ƿ��ȥ�����߿�
	   if (snake_center_coor[0].x >= 300  || snake_center_coor[0].x <= -100 || snake_center_coor[0].y >= 300 || snake_center_coor[0].y <= -100) {
		//display_string();
		die = true;
	   }
	//�ж���ͷ����������x��y�Ƿ���������������غ�
	    for (int i = 2; i <= size; i++) {
		if (snake_center_coor[1]==snake_center_coor[i]) {
			die = true;
		}
	}
	}
	
}

//����ȫ������������
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

//�Ҽ��˵����ܣ���������������ȥ���в�ͬ�Ĺ���ʵ��
void menufunc(int data) {

	switch (data) {
	case 1:
		Pause = true;
		speed = 0;
		break;
	case 2:
		Pause = false;
		speed = 2;
		break;
	case 3:
		exit(0);
		break;
	case 4:
		restart = true;
		//glutDestroyWindow(windows);
		
		break;

	}

}

//ʳ������
void Food() {
	//ͨ����ʳ������ĵ�һ���x������ʳ���λ��
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

//�ж��Ƿ�Ե�ʳ��
void Eat_food() {


	if (food_flag && snake_center_coor[0].x >= food_center_coor.x - 10 && snake_center_coor[0].x <= food_center_coor.x + 10 && snake_center_coor[0].y >= food_center_coor.y - 10 && snake_center_coor[0].y <= food_center_coor.y + 10)
	{
		food_flag = false;
		printf("--------------------------�Ե�ʳ���ˣ���������ǰ�߳���%d--------------��ǰʱ��%d-----------\n", size, Functime);
		size=size+5;

	}
	//�ж�ʳ���Ƿ����
	if (!food_flag) {
		Food();
	}
}

//���ƻ���
void show_myPoints(void)
{
	
	//���ж�����û����������������ͻ����Ѿ����������֣���֮��ͨ����ÿһ�ڵ������������һ����������
	if (!die) {
		
		Calculate_center_coor();
		snake_die();
		Eat_food();
		//�����ɫ������
		glClear(GL_COLOR_BUFFER_BIT);
		//�����ߵ���ɫ
		glColor3f(0.6, 0.5, 0.2);
		//ͨ��forѭ��������һ��һ��������
		for (int i = 0; i <= size; i++) {
			glRectf(coor[i][0].x, coor[i][0].y, coor[i][1].x, coor[i][1].y);
		}
		//����ʳ��
		if (food_flag) {
			glColor3f(1.0, 0.0, 1.0);
			glRectf(food[0].x, food[0].y, food[1].x, food[1].y);

		}
		//�������ƺõ�֡������
		glutSwapBuffers();
		printf("��ǰ��ͷ��������%d    %d    \n", snake_center_coor[0].x, snake_center_coor[0].y);
		printf("��ǰʳ����������%d    %d    \n", food_center_coor.x, food_center_coor.y);

	}
	if (die) {
		printf("���Ѿ�����\n����һ������%d ��ʳ��",(size-10)/5);
		//��ձ�����ɫ
		glClearColor(0, 0, 0, 0);
		//�����ɫ������
		glClear(GL_COLOR_BUFFER_BIT);
		//�ü���ͼ��Χ
		//gluOrtho2D(-10, 30, -10, 30);
		glColor3f(1.0f, 0.0f, 0.0f);
		//���ֵ�λ��
		glRasterPos2f(125.0f, 165.0f);
		drawString("You die");
		/*��Ϊ֮ǰ�Ķ�ʱ����8msһ�μ��㣬��������Ҫ��ô��Ļ�ͼ����������33ms
		* Ҳ�����𵽽�ʡӲ����Դ��Ч����
		* 
		*/

		Sleep(33);
		//֮ǰ���������
		system("cls");

		//����������
		glutSwapBuffers();

	}

	//��ǵ�ǰ������Ҫ���»��ƣ���glutMainLoop()ѭ��ʱ����
	glutPostRedisplay();

}
//��ʼ����Ϸ
void init()
{
	restart = false;
	Pause = false;
	
	size = 10;
	speed = 2;
	dir = RIGHT;
	die = false;
	//������������Ӻ͵��Կ���ʱ���й�ϵ
	srand(GetTickCount64());
	//�ֶ������ͷ����������
	coor[0][0].x = 0;
	coor[0][0].y = 0;//��һ��(0.0)
	coor[0][1].x = 10;
	coor[0][1].y = 10;//�ڶ���(10,10)
	//������������ȫ������
	for (int i = 1; i < size; i++) {
		coor[i][0].x = coor[i - 1][0].x - speed;
		coor[i][1].x = coor[i - 1][1].x - speed;
		coor[i][0].y = coor[i - 1][0].y;
		coor[i][1].y = coor[i - 1][1].y;
	}
	//����ʳ��
	Food();
	//��RGB��1��1��1�����Ϊ������ɫ
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//���嵱ǰͶӰ����ΪͶӰ
	glMatrixMode(GL_PROJECTION);
	//����Ϊ��λ����
	glLoadIdentity();
	//��ʾ����Ĳ��У�Ҳ����ָ����Ļ�����Ӧ��ģ�����귶Χ
	gluOrtho2D(-100, 300, -100, 300);

}

void a() {
	//������ʾģʽ��RGB,˫�ػ�����
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	//��λ��������Ļ��λ��
	glutInitWindowPosition(300, 100);
	//����Ϊ����Ĵ�С
	glutInitWindowSize(800, 800);
	//��ʾ�������
	int  mainWindow = glutCreateWindow("̰����");
	/*
	*Ϊ֮ǰ���¿�ʼ�Ĵ����ṩ���ݣ�����ʧ�ܵģ�
	 */

	windows = glutGetWindow();
	init();

	//�����˵�����
	glutCreateMenu(menufunc);
	/*��������ʾ�˵��İ�ť
	* ͨ������int���ͺ�menfunc�ص����������ж���������һ��
	*/

    glutAddMenuEntry("pause", 1);


	glutAddMenuEntry("continue", 2);

	glutAddMenuEntry("exit", 3);
	glutAddMenuEntry("restart", 4);
	//�󶨲˵�������������Ҽ�
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	//������ʾ��������ʾ
	glutDisplayFunc(show_myPoints);
	//����һ����ʱ������ʱ��������õ��Ǽ�������
	glutTimerFunc(8, myPoints, 1);
	
	glutKeyboardFunc(myKeyBorad);
	if (!die) {
		glutMainLoop();
	}



}

int main(int argc, char** argv) {
	
	for (int i = 5; i > 0; i--) {
		printf("wsad���Ʒ����Ҽ���ʾ�˵�����ȥ����������--------%d��������Ϸ\n",i);
		Sleep(1000);
	}
	
	//��ʼ��glut
	glutInit(&argc, argv);
	//Ĭ�ϲ���Ҫ���¿�ʼ
	restart = false;
	//�����߳�ȥ����a
	std::thread t1(a);
	//�����̣߳�Ҳ���������߳�ȥ�������߳����н���
	t1.join();
	
	

}


