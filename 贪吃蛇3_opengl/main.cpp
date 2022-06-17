/*
* 如果不能运行或者编译失败，
* 请确保用的是vs2022
* 以及确保项目的链接器和包含库目录是正确的（我用了相对路径）。
* 另外附加依赖项要确保正常
* 请确保运行的编译器是x86的，因为我连接的是静态32位的库文件
* 64位的编译器会链接失败
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
// 结构体提供坐标功能
struct Point
{
	int x;
	int y;

	// 重载==，提供下面判断中心点坐标是否重合
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
//枚举
enum DIR {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

//显示文字用
void drawString(const  char* str) {
	static  int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) { // 如果是第一次调用，执行初始化
						// 为每一个ASCII字符产生一个显示列表
		isFirstCall = 0;

		// 申请MAX_CHAR个连续的显示列表编号
		lists = glGenLists(MAX_CHAR);

		// 把每个字符的绘制命令都装到对应的显示列表中
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// 调用每个字符对应的显示列表，绘制每个字符
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}


//刷新坐标
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
	// 如果没有死亡，便递归整个函数.死亡的话，就不递归
	if (!die) {
		glutTimerFunc(8, myPoints, 1);
		//glutSetWindow(mainWindow);
		//glutPostRedisplay();
	}
	//Sleep(200);



}

//绑定键盘，并且与之前的枚举进行关联
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
	//指定颜色缓冲区的清除值
	glClearColor(0, 0, 0, 0);

	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);

	//字体位置
	glRasterPos2f(0.0f, 0.0f);
	drawString("You die ");
	//交换缓冲区
	glutSwapBuffers();
}
//-----------------------------------------------------
void snake_die() {
	if (!Pause) {
	//判断蛇头的中心坐标x,y是否出去整个边框
	   if (snake_center_coor[0].x >= 300  || snake_center_coor[0].x <= -100 || snake_center_coor[0].y >= 300 || snake_center_coor[0].y <= -100) {
		//display_string();
		die = true;
	   }
	//判断蛇头的中心坐标x，y是否和蛇身中心坐标重合
	    for (int i = 2; i <= size; i++) {
		if (snake_center_coor[1]==snake_center_coor[i]) {
			die = true;
		}
	}
	}
	
}

//计算全部的中心坐标
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

//右键菜单功能，将传进来的数据去进行不同的功能实现
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

//食物生成
void Food() {
	//通过对食物坐标的第一点的x来更改食物的位置
	food[0].x = rand() % 200;
	food[0].y = food[0].x;
	food[1].x = food[0].x + 20;
	food[1].y = food[0].y + 20;
	food_flag = true;
	Calculate_center_coor();
	for (int i = 0; i < size; i++) {
		if (snake_center_coor[i].x >= food_center_coor.x - 20 && snake_center_coor[i].x <= food_center_coor.x + 20 && snake_center_coor[i].y >= food_center_coor.y - 20 && snake_center_coor[i].y <= food_center_coor.y + 20) {
			Food();
			printf("---------------------由于食物与蛇重合，重新生成食物！！！\n-----------");
		}
	}
}

//判断是否吃到食物
void Eat_food() {


	if (food_flag && snake_center_coor[0].x >= food_center_coor.x - 10 && snake_center_coor[0].x <= food_center_coor.x + 10 && snake_center_coor[0].y >= food_center_coor.y - 10 && snake_center_coor[0].y <= food_center_coor.y + 10)
	{
		food_flag = false;
		printf("--------------------------吃到食物了！！！！当前蛇长度%d--------------当前时间%d-----------\n", size, Functime);
		size=size+5;

	}
	//判断食物是否存在
	if (!food_flag) {
		Food();
	}
}

//绘制画面
void show_myPoints(void)
{
	
	//先判断蛇有没有死亡，如果死亡就绘制已经死亡的文字，反之则通过蛇每一节的两个坐标绘制一个个正方形
	if (!die) {
		
		Calculate_center_coor();
		snake_die();
		Eat_food();
		//清空颜色缓冲区
		glClear(GL_COLOR_BUFFER_BIT);
		//绘制蛇的颜色
		glColor3f(0.6, 0.5, 0.2);
		//通过for循环，绘制一个一个正方形
		for (int i = 0; i <= size; i++) {
			glRectf(coor[i][0].x, coor[i][0].y, coor[i][1].x, coor[i][1].y);
		}
		//绘制食物
		if (food_flag) {
			glColor3f(1.0, 0.0, 1.0);
			glRectf(food[0].x, food[0].y, food[1].x, food[1].y);

		}
		//交换绘制好的帧缓冲区
		glutSwapBuffers();
		printf("当前蛇头中心坐标%d    %d    \n", snake_center_coor[0].x, snake_center_coor[0].y);
		printf("当前食物中心坐标%d    %d    \n", food_center_coor.x, food_center_coor.y);

	}
	if (die) {
		printf("你已经死了\n，你一共吃了%d 个食物",(size-10)/5);
		//清空背景颜色
		glClearColor(0, 0, 0, 0);
		//清空颜色缓冲区
		glClear(GL_COLOR_BUFFER_BIT);
		//裁剪视图范围
		//gluOrtho2D(-10, 30, -10, 30);
		glColor3f(1.0f, 0.0f, 0.0f);
		//文字的位置
		glRasterPos2f(125.0f, 165.0f);
		drawString("You die");
		/*因为之前的定时器是8ms一次计算，死亡后不需要这么快的绘图，这里设置33ms
		* 也可以起到节省硬件资源的效果，
		* 
		*/

		Sleep(33);
		//之前清空命令行
		system("cls");

		//交换缓冲区
		glutSwapBuffers();

	}

	//标记当前窗口需要重新绘制，让glutMainLoop()循环时绘制
	glutPostRedisplay();

}
//初始化游戏
void init()
{
	restart = false;
	Pause = false;
	
	size = 10;
	speed = 2;
	dir = RIGHT;
	die = false;
	//设置随机数种子和电脑开机时间有关系
	srand(GetTickCount64());
	//手动设计蛇头的两个坐标
	coor[0][0].x = 0;
	coor[0][0].y = 0;//第一个(0.0)
	coor[0][1].x = 10;
	coor[0][1].y = 10;//第二个(10,10)
	//计算后续蛇身的全部坐标
	for (int i = 1; i < size; i++) {
		coor[i][0].x = coor[i - 1][0].x - speed;
		coor[i][1].x = coor[i - 1][1].x - speed;
		coor[i][0].y = coor[i - 1][0].y;
		coor[i][1].y = coor[i - 1][1].y;
	}
	//生成食物
	Food();
	//将RGB（1，1，1）设计为背景颜色
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//定义当前投影矩阵为投影
	glMatrixMode(GL_PROJECTION);
	//定义为单位矩阵
	glLoadIdentity();
	//显示画面的裁切，也就是指定屏幕区域对应的模型坐标范围
	gluOrtho2D(-100, 300, -100, 300);

}

void a() {
	//定义显示模式是RGB,双重缓冲区
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	//定位窗体在屏幕的位置
	glutInitWindowPosition(300, 100);
	//定义为窗体的大小
	glutInitWindowSize(800, 800);
	//显示窗体标题
	int  mainWindow = glutCreateWindow("贪吃蛇");
	/*
	*为之前重新开始的窗体提供数据（功能失败的）
	 */

	windows = glutGetWindow();
	init();

	//创建菜单功能
	glutCreateMenu(menufunc);
	/*下面是显示菜单的按钮
	* 通过返回int类型和menfunc回调参数进行判读按下了哪一个
	*/

    glutAddMenuEntry("pause", 1);


	glutAddMenuEntry("continue", 2);

	glutAddMenuEntry("exit", 3);
	glutAddMenuEntry("restart", 4);
	//绑定菜单呼出是用鼠标右键
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	//调用显示函数来显示
	glutDisplayFunc(show_myPoints);
	//定义一个计时器，计时器里面调用的是计算坐标
	glutTimerFunc(8, myPoints, 1);
	
	glutKeyboardFunc(myKeyBorad);
	if (!die) {
		glutMainLoop();
	}



}

int main(int argc, char** argv) {
	
	for (int i = 5; i > 0; i--) {
		printf("wsad控制方向，右键显示菜单，出去整个框框就死--------%d秒后进入游戏\n",i);
		Sleep(1000);
	}
	
	//初始化glut
	glutInit(&argc, argv);
	//默认不需要重新开始
	restart = false;
	//启动线程去调用a
	std::thread t1(a);
	//阻塞线程，也就是让主线程去等在子线程运行结束
	t1.join();
	
	

}


