#include "input.hpp"
#include "gl_vars.hpp"
#include "engine.hpp"
#include "gfx.hpp"

#define GLUT_DISABLE_ATEXIT_HACK
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void processMouseMove(int x, int y)
{
	int deltax = mousex - x, deltay = mousey - y;
	float fraction = 0.05f;
	if (deltax == 0 && deltay == 0)
		return;
	if (abs(deltax) >= 5)
	{
		if (deltax > 0)
			anglexy -= fraction;
		else
			anglexy += fraction;
	}
	if (abs(deltay) >= 5)
	{
		if (deltay > 0)
			anglev -= fraction;
		else
			anglev += fraction;
	}
	if (anglev > 1.5) anglev = 1.5;
	if (anglev < -1.5) anglev = -1.5;
	lx = sin(anglexy)  * cos(anglev);
	ly = sin(anglev);
	lz = -cos(anglexy) * cos(anglev);
	l2x = sin(anglexy);
	l2z = -cos(anglexy);
	glutWarpPointer(512, 768/2);
	mousex = 512;
	mousey = 768/2;
}

void processMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (lat.accurate)
		{
			if (!destroyTool)
			{
				printf("Place block at %.3f, %.3f, %.3f\n", lat.x, lat.y, lat.z);
				boxes.push_back(lat);
			}
			else
			{
				for (unsigned int i = 0; i < boxes.size(); i++)
				{
					struct vector3d box = boxes.at(i);
					if (box.x == lat.x && box.y == lat.y && box.z == lat.z)
						boxes.erase(boxes.begin() + i);
				}
			}
		}
	}
}

void processKeys(unsigned char key, int xx, int yy)
{
	float fraction = 0.75f;
	float tx = x, ty = y, tz = z;
	switch (key)
	{
		case 'a':
			tx += cos(anglexy) * fraction;
			tz += sin(anglexy) * fraction;
			break;
		case 'd':
			tx -= cos(anglexy) * fraction;
			tz -= sin(anglexy) * fraction;
			break;
		case 'w':
			tx -= lx * fraction;
			tz -= lz * fraction;
			break;
		case 's':
			tx += lx * fraction;
			tz += lz * fraction;
			break;
		case 'f':
			firebullet();
			break;
		case ' ':
			if (!gravaccel)
				ty += 1.875;
			break;
		case '`':
			destroyTool = !destroyTool;
			break;
	}
	moveTo(tx, ty, tz);
}

void processSpecialKeys(int key, int xx, int yy)
{
	switch (key)
	{
		case GLUT_KEY_END:
			exit(0);
	}
}
