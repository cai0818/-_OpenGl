/*
#include <GL\glut.h>
GLuint mainw, subw1, subw2, subw3;
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutSetWindow(subw1);
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glutSetWindow(subw2);
	glClearColor(0.0, 1.0, 0.0, 0.0);
	glutSetWindow(subw3);
	glClearColor(0.0, 0.0, 1.0, 0.0);
}
void mreshape(int width, int height)
{
}
void mdisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
void s1reshape(int width, int height)
{
}
void s1display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
void s2reshape(int width, int height)
{
}
void s2display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
void s3reshape(int width, int height)
{
}
void s3display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
int main(int argc, char** argv)
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(200, 200);
	glutInit(&argc, argv);

	mainw = glutCreateWindow("test");
	glutReshapeFunc(mreshape);
	glutDisplayFunc(mdisplay);
	subw1 = glutCreateSubWindow(mainw, 30, 30, 300, 300);
	glutReshapeFunc(s1reshape);
	glutDisplayFunc(s1display);
	subw2 = glutCreateSubWindow(mainw, 350, 30, 300, 300);
	glutReshapeFunc(s2reshape);
	glutDisplayFunc(s2display);
	subw3 = glutCreateSubWindow(mainw, 350, 380, 300, 300);
	glutReshapeFunc(s3reshape);
	glutDisplayFunc(s3display);

	init();

	glutMainLoop();

	return 0;
}

*/