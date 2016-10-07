#include "gfx.hpp"
#include "gl_vars.hpp"
#include "../Common/macros.h"
#include "../Common/structures.h"
#include "engine.hpp"
struct vector3d lookingAt(bool _colliding);

#define GLUT_DISABLE_ATEXIT_HACK
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdio.h>

float bx, by, bz;
float blx, bly, blz, btravel;
int bc;

void renderBitmapString(float x, float y, float z, void *font, char *string);
void restorePerspectiveProjection();
void setOrthographicProjection();
void renderbullet();

void resizeWindow(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
    w = width;
    h = height;
}

void renderBitmapString(float x, float y, float z, void *font, char *string)
{
	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void restorePerspectiveProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void setOrthographicProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
}

void renderbullet()
{
	if (bx == by && by == bz && bz == 0)
		return;
	if (btravel > 100)
		return;
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(bx, by, bz);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();
	if (bc++ < 5)
		return;
	bc = 0;
	bx -= blx;
	by -= bly;
	bz -= blz;
	btravel += sqrt(pow(blx, 2) + pow(bly, 2) + pow(blz, 2));
}

void firebullet()
{
	bx = x;
	by = y;
	bz = z;
	blx = lx;
	bly = ly;
	blz = lz;
	bc = 0;
	btravel = 0;
}

void renderScene(void)
{
	char textbuf[1024];
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x+lx, y+ly,  z+lz,
				x, y, z,
			0.0f, 0.70f,  0.0f);
	// Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, -1.0f, -100.0f);
		glVertex3f(-100.0f, -1.0f,  100.0f);
		glVertex3f( 100.0f, -1.0f,  100.0f);
		glVertex3f( 100.0f, -1.0f, -100.0f);
	glEnd();
	// Draw scene
	for (unsigned int i = 0; i < boxes.size(); i++)
	{
		struct vector3d box = boxes.at(i);
		glPushMatrix();
		glTranslatef(box.x, box.y, box.z);
		glColor3f(0,0,0);
		glutWireCube(1);
		glColor3f(0.5f, 0.1f, 0.4f);
		glutSolidCube(0.99);
		glPopMatrix();
	}
	renderbullet();
	// Draw crosshair
	lat = lookingAt(destroyTool);
	glPushMatrix();
	glTranslatef(lat.x, lat.y, lat.z);
	if (!destroyTool)
		glColor3f(0.0f, 1.0f, 0.0f); //green
	else
		glColor3f(1.0f, 0.0f, 0.0f);
	if (lat.accurate)
		glutWireCube(0.99);
	glPopMatrix();
	//draw text
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	sprintf(textbuf, "X: %.3f     Y: %.3f     Z: %.3f       T: %.3f     P: %.3f", x, y, z, anglexy, anglev);
	renderBitmapString(5, 30, 0, GLUT_BITMAP_HELVETICA_12, textbuf);
	glPopMatrix();
	restorePerspectiveProjection();
	glutSwapBuffers();
}
