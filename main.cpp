#include <GL/freeglut.h>
#include <cmath>

#define N 12

float t = 0.0f;

float rx = 0.0f;
float ry = 0.0f;
float dist = -50;

float Surface[N][N][3];

void Display()
{
	t += 0.1;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			Surface[i][j][1] = sinf(t + i + j) * 5;
		}
	}

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glTranslatef(0, 0, dist);
	glRotatef(40, 1, 0, 0);

	glColor3f(0.8, 0.7, 0.5);
	for (int i = 0; i < N - 1; ++i)
	{
		for (int j = 0; j < N - 1; ++j)
		{
			glBegin(GL_QUADS);
			glVertex3fv(&Surface[i][j][0]);
			glVertex3fv(&Surface[i + 1][j][0]);
			glVertex3fv(&Surface[i + 1][j + 1][0]);
			glVertex3fv(&Surface[i][j + 1][0]);
			glEnd();
		}
	}

	glPointSize(5);
	glColor3f(0, 1, 0);
	glBegin(GL_POINTS);
	for (int i = 0; i < N; ++i)
	for (int j = 0; j < N; ++j)
		glVertex3fv(&Surface[i][j][0]);
	glEnd();

	glPopMatrix();

	glPointSize(1);

	glutSwapBuffers();
}

void Resize(int w, int h)
{
	float a = (float)w / (float)h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, a, 0.1, 1000);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '+')
		dist += 10;
	if (key == '-')
		dist -= 10;
}

void Idle()
{
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Powierzchnie - wcisnij ESC aby zamknac");

	glClearColor(1, 1, 0.3, 1.0);

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			Surface[i][j][0] = (j * 10) - 60;
			Surface[i][j][2] = (i * 10) - 60;
		}
	}

	glutKeyboardFunc(Keyboard);
	glutIdleFunc(Idle);
	glutReshapeFunc(Resize);
	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}