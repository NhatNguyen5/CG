/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#if __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = { 0,1,4,1 };
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1() {
	// TODO: Your code here!
	
	double r = 1;
	double pi = 3.14159265358979323846;
	double angle_in_rad = pi / 5;
	double angle_in_degree = 180 / 5;
	for(int i = 0; i < 360 / angle_in_degree ; i++)
	{
		double x = cos(angle_in_rad * i) * r; // calculate x base on angle
		double y = sin(angle_in_rad * i) * r; // calculate y base on angle
	
		glPushMatrix();
		glTranslated(x, y, 0);
		glRotatef(angle_in_degree * i, 0, 0, 1);
		glutSolidTeapot(0.2);
		glPopMatrix();
	}
}

void problem2() {
	// TODO: Your code here!

	double step = 15;
	double step_d = 0.20;
	double step_inc = 0.1;
	glPushMatrix();
	glTranslated(0, -0.5, 0);
	for (double i = 1; i <= step; i++)
	{
		double x = step_d * (i - ((step + 2) / 2));
		double y = (step_d + (step_inc * i)) / ((step + 5) / 2);
		glPushMatrix();
		glTranslated(x, y + 0.1, 0);
		glScalef(1, 1 + step_inc * i, 1);
		glutSolidCube(step_d);
		glPopMatrix();
		step_inc += 0.01;
	}
	glPopMatrix();
}

void problem3() {
	// TODO: Your code here!
	int level = 6;
	double r = 0.6;
	double pi = 3.14159265358979323846;
	double angle_in_rad = 5 * pi / 4;
	double angle_in_degree = 225;
	double offset = fabs(r * sin(angle_in_rad)*2);
	double x = 0;
	double y = 0;
	for (int i = 1; i <= level; i++)
	{
		for (int j = 0; j < i; j++)
		{
			double new_x = x + offset * j;

			glPushMatrix();
			glTranslated(new_x, y + offset, 0);
			glutSolidTeapot(0.2);
			glPopMatrix();
		}
		x = x + cos(angle_in_rad) * r; // calculate x bade on angle
		y = y + sin(angle_in_rad) * r; // calculate y bade on angle
	}
}

void problem4() {
	// TODO: Your code here!
	double u = 0.5;
	double d_w_ratio = 0.5;
	double pi = 3.14159265358979323846;
	double blade_w = u * sin(pi / 4);
	double blade_d = u * sin(pi / 4) * d_w_ratio;
	double r_size = 0.2;
	double x1 = 0, y1 = 0;
	double x2 = 0, y2 = 0;
	double x3 = 0, y3 = 0;
	double t_x = 0.5, t_y = t_x/tan(pi/6);
	double t_s = 9;
	
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	//glEnable(GL_COLOR_MATERIAL);
	//double blade_l = 2*u;
	// Tri-force
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.95f, 0.95f, 0.06f);
	//glPushMatrix();
		//glTranslated(0, 0, 0); // move the whole thing
		
	glPushMatrix();
		//glTranslated(0, - t_s * t_y, 0); // center the Triforce
		glTranslated(0, - 5.5 * t_y, 0);
		glScalef(t_s, t_s, 0);
		for (int i = 0; i < 3; i++)
		{
			if (i == 0)
			{
				x1 = 0; y1 = t_y * 2;
				x2 = -t_x; y2 = t_y;
				x3 = t_x; y3 = t_y;
			}
			else if (i == 1)
			{
				x1 = -t_x; y1 = t_y;
				x2 = -2 * t_x; y2 = 0;
				x3 = 0; y3 = 0;
			}
			else
			{
				x1 = t_x; y1 = t_y;
				x2 = 0; y2 = 0;
				x3 = 2 * t_x; y3 = 0;
			}
			glPushMatrix();	
				glBegin(GL_TRIANGLES);
					glVertex2f(x1, y1);
					glVertex2f(x2, y2);
					glVertex2f(x3, y3);
				glEnd();
			glPopMatrix();
		}
	glPopMatrix();

	glPushMatrix();
		//glTranslated(0, -3, 0); // center the blade if center the Triforce
		glTranslated(0, 0.2, 0);
		//glRotated(180, 1, 0, 0);
		// The blade
		glColor3f(0.9, 0.9, 0.9);
		glPushMatrix();
			glScaled(1, 4, d_w_ratio);
			glPushMatrix();
				glRotatef(45, 0, 1, 0);
				glScaled(1, 2, 1);
				glutSolidCube(u);
			glPopMatrix();
		glPopMatrix();
		// Tip of the blade
		glPushMatrix();
			glTranslatef(0, u*4, 0);
			//glScaled(1, 3, 0.5);
			glPushMatrix();
				//glRotatef(90, 0, 1, 1);
				glScaled(blade_w, u, blade_d);
				glutSolidOctahedron();
			glPopMatrix();
		glPopMatrix();
		// Blade guard
		glColor3f(0.11, 0.25, 0.25);
		// Right guard
		glPushMatrix();
			glTranslated(0.08, -u * 4, 0);
			glScaled(2.1, 0.5, d_w_ratio + 0.2);
			glPushMatrix();
				glRotatef(45, 0, 1, 0);
				glutSolidCube(u);
			glPopMatrix();
		glPopMatrix();
		// Filling
		glPushMatrix();
			glTranslated(0, -u * 4, 0);
			glScaled(0.32, 0.5, 2 * (d_w_ratio + 0.2) * sin(pi/4));
			glutSolidCube(u);
		glPopMatrix();
		// Left guard
		glPushMatrix();
			glTranslated(-0.08, -u * 4, 0);
			glScaled(2.1, 0.5, d_w_ratio + 0.2);
			glPushMatrix();
				glRotatef(45, 0, 1, 0);
				glutSolidCube(u);
			glPopMatrix();
		glPopMatrix();
		// Handle
		glColor3f(0.93f, 0.52f, 0.26f);
		double handle_l = 0;
		for (int i = 1; i <= 5; i++)
		{
			handle_l = -u * (4 + 0.4 * i);
			glPushMatrix();
				glTranslated(0, handle_l, 0);
				glScaled(r_size, 0.5, r_size);
				glPushMatrix();
					glRotatef(90, 1, 0, 0);
					glutSolidTorus(u / 2, u, 50, 50);
				glPopMatrix();
			glPopMatrix();
			r_size = r_size - 0.01;
		}
		// Pommel
		glColor3f(0.66f, 0.71f, 0.73f);
		glPushMatrix();
			glTranslated(0, handle_l - 0.2, 0);
			glScaled(u/4, u/4, u/4);
			glPushMatrix();
				//glRotatef(45, 0, 1, 0);
				glutSolidDodecahedron();
			glPopMatrix();
		glPopMatrix();
		glColor3f(0.27f, 0.85f, 0.25f);
		// Crystal 1
		glPushMatrix();
			glTranslated(0, -u * 4, 0.25);
			//glScaled(1, 3, 0.5);
			glPushMatrix();
				//glRotatef(90, 0, 0, 1);
				glScaled(blade_w*0.2, u*0.2, blade_d*0.2);
				glutSolidOctahedron();
			glPopMatrix();
		glPopMatrix();
		// Crystal 2
		glPushMatrix();
			glTranslated(0, -u * 4, -0.25);
			//glScaled(1, 3, 0.5);
			glPushMatrix();
				//glRotatef(90, 0, 0, 1);
				glScaled(blade_w * 0.2, u * 0.2, blade_d * 0.2);
				glutSolidOctahedron();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	//glPopMatrix();
	glColor3f(1, 1, 1);
	glDisable(GL_COLOR_MATERIAL);
}

void display() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0); // x axis
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0); // y axis
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, windowWidth, windowHeight);

	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot, 0, 1, 0);

	if (curProblem == 1) problem1();
	if (curProblem == 2) problem2();
	if (curProblem == 3) problem3();
	if (curProblem == 4) problem4();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown) yRot += (x - lastPos[0]) * .1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1, (y - lastPos[1]) * .1);
	}


	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	curProblem = key - '0';
	if (key == 'q' || key == 'Q' || key == 27) {
		exit(0);
	}
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");
	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
