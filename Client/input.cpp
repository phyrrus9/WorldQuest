#include <Client/input.hpp>
#include <Client/gl_vars.hpp>
#include <Client/engine.hpp>
#include <Client/gfx.hpp>

#define GLUT_DISABLE_ATEXIT_HACK
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <Resources/Objects/permanentBlock.h>

// need to add this since C++11 is too fucking strict
// to allow meaningful functions, all probably because
// the jackasses who wrote the spec don't know how to
// do any god damn implicit pointer castings. fuck you
char* strdup (const char* s)
{
  size_t slen = strlen(s);
  char* result = (char *)malloc(slen + 1);
  if(result == NULL)
  {
    return NULL;
  }

  memcpy(result, s, slen+1);
  return result;
}

void processMouseMove(int x, int y)
{
	int deltax = mousex - x, deltay = mousey - y;
	float fraction = 0.035f;
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
				permanentBlock *block = new permanentBlock(lat);
				nonparticles->push_back(block);
				//boxes.push_back(lat);
			}
			else
			{
                for (unsigned int i = 0; i < nonparticles->size(); ++i)
                {
                    gameObjectBase *object = nonparticles->at(i);
                    if (!strcmp(object->mcstr_name, "Permanent Block") &&
                        (*object->mptr_positionX == lat.x &&
                         *object->mptr_positionY == lat.y &&
                         *object->mptr_positionZ == lat.z))
                    {
                        nonparticles->erase(nonparticles->begin() + i);
                        delete object;
                    }
                }
				/*for (unsigned int i = 0; i < boxes.size(); i++)
				{
					struct vector3d box = boxes.at(i);
					if (box.x == lat.x && box.y == lat.y && box.z == lat.z)
						boxes.erase(boxes.begin() + i);
				}*/
			}
		}
	}
}

void processDownKeys(unsigned char key, int xx, int yy)
{
	switch (key)
	{
		case 'a':
		    movement.a = true;
			break;
		case 'd':
		    movement.d = true;
			break;
		case 'w':
		    movement.w = true;
			break;
		case 's':
		    movement.s = true;
			break;
		case 'f':
			firebullet();
			break;
		case ' ':
		    movement.jump = true;
			break;
		case '`':
			destroyTool = !destroyTool;
			break;
	}
}

void processUpKeys(unsigned char key, int xx, int yy)
{
	switch (key)
	{
		case 'a':
		    movement.a = false;
			break;
		case 'd':
		    movement.d = false;
			break;
		case 'w':
		    movement.w = false;
			break;
		case 's':
		    movement.s = false;
			break;
		case ' ':
		    movement.jump = false;
			break;
	}
}

void processSpecialKeys(int key, int xx, int yy)
{
	switch (key)
	{
		case GLUT_KEY_END:
			exit(0);
	}
}
