/*
#include <windows.h>
#include <gl/glut.h>

//animation.cpp

GLfloat x1 = 100.0f;
GLfloat y1 = 150.0f;
GLsizei size = 50;

GLfloat xstep = 1.06f;
GLfloat ystep = 1.06f;

GLfloat windowWidth = 300.0f;
GLfloat windowHeight = 300.0f;

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);   //清空颜色缓冲池
    glColor3f(1.0f, 0.0f, 0.0f);    //设置绘图颜色
    glRectf(x1, y1, x1 + size, y1 + size);    //绘制矩形
    glutSwapBuffers();
}

void timerFunction(int value)
{
    if (x1 > windowWidth - size || x1 < 0)
        xstep = -xstep;

    if (y1 > windowWidth - size || y1 < 0)
        ystep = -ystep;

    if (x1 > windowWidth - size)
        x1 = windowWidth - size - 1;

    if (y1 > windowHeight - size)
        y1 = windowHeight - size - 1;

    x1 += xstep;
    y1 += ystep;

    glutPostRedisplay();
    glutTimerFunc(7, timerFunction, 1);
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);    //设置显示模式
    glutInitWindowSize(windowWidth, windowHeight); //设置窗口大小
    glutInitWindowPosition(200, 200);   //设置窗口在屏幕上的位置 
    glutCreateWindow("动画"); //创建窗口并给出标题
    glutDisplayFunc(renderScene);   //注册显示窗口时回调函数renderScene
    glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0, -1.0);  //修改修剪空间的范围
    glutTimerFunc(7, timerFunction, 1);    //注册定时器
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);   //使用蓝色清空背景底
    glutMainLoop();     //消息循环（处理操作系统等的消息，例如键盘、鼠标事件等）
}
*/