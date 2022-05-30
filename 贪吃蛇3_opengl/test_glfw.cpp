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
    glClear(GL_COLOR_BUFFER_BIT);   //�����ɫ�����
    glColor3f(1.0f, 0.0f, 0.0f);    //���û�ͼ��ɫ
    glRectf(x1, y1, x1 + size, y1 + size);    //���ƾ���
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);    //������ʾģʽ
    glutInitWindowSize(windowWidth, windowHeight); //���ô��ڴ�С
    glutInitWindowPosition(200, 200);   //���ô�������Ļ�ϵ�λ�� 
    glutCreateWindow("����"); //�������ڲ���������
    glutDisplayFunc(renderScene);   //ע����ʾ����ʱ�ص�����renderScene
    glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0, -1.0);  //�޸��޼��ռ�ķ�Χ
    glutTimerFunc(7, timerFunction, 1);    //ע�ᶨʱ��
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);   //ʹ����ɫ��ձ�����
    glutMainLoop();     //��Ϣѭ�����������ϵͳ�ȵ���Ϣ��������̡�����¼��ȣ�
}
*/