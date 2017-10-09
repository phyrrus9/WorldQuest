#include "engine.hpp"
#include "../Common/structures.h"
#include "../Common/macros.h"
#include "gl_vars.hpp"

#define GLUT_DISABLE_ATEXIT_HACK
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <time.h>
#include <pthread.h>
#include <stdio.h>

struct vector3d lookingAt(bool _colliding = false);

/* gravity vars */
clock_t lastGrav = 0;
float vg=0.0f; // velocity gravity
void gravity(void)
{
    if (lastGrav != 0)
    {
        clock_t currentGrav = clock();
        float t = (double)(currentGrav - lastGrav) / (double)CLOCKS_PER_SEC; // time spent falling between ticks
        if (t < .01) return;
        float u = vg;
        float v = u + (ACCEL * t);
        v = v > 36 ? 36 : v;
        vg = v; // save it
        float d = v * t;
        float ty = y + (gravfall ? -d : gravjump ? +d : 0);
        //printf("t=%.3f u=%.3f v=%.3f d=%.3f\n", t, u, v, d);
        if (ty != y)
            moveTo(x, ty, z);
        if (!gravfall && !gravjump)
            vg = 0.0f;
    }
    lastGrav = clock();
}

bool moveTo(float tx, float ty, float tz)
{
	if (!colliding(tx, ty, tz) && !colliding(tx, ty - 1, tz) && ty >= 1)
	{
		x = tx;
		y = ty;
		z = tz;
		return true;
	}
	return false;
}

bool colliding(float x, float y, float z, float newosize)
{
	//RND(x);
	//RND(y);
	//RND(z);
	for (unsigned int i = 0; i < nonparticles->size(); ++i)
    {
        gameObjectBase *obj = nonparticles->at(i);
        //if (y == 0) return true;
        vector3d osize = obj->mfnc_restrict_size();
        if ((x >= *obj->mptr_positionX && (x + osize.x) <= *obj->mptr_positionX) &&
            (y >= *obj->mptr_positionY && (y + osize.y) <= *obj->mptr_positionY) &&
            (z >= *obj->mptr_positionZ && (z + osize.z) <= *obj->mptr_positionZ))
            return true;
        /* new object check */
        /*if ((*obj->mptr_positionX >= x && *obj->mptr_positionX <= (x + osize.x)) &&
            (*obj->mptr_positionX >= y && *obj->mptr_positionX <= (y + osize.y)) &&
            (*obj->mptr_positionX >= z && *obj->mptr_positionX <= (z + osize.z)))
            return true;*/
    }
	/*for (unsigned int i = 0; i < boxes.size(); i++)
	{
		struct vector3d box = boxes.at(i);
		if (box.x == x && box.y == y && box.z == z)
			return true;
	}*/
	return false;
}

struct vector3d lookingAt(bool _colliding)
{
	struct vector3d ret = { x, y, z };
	float dist = 0.0f;
	const float maxdist = 7.5f;
	float	mx = lx,
			my = ly,
			mz = lz;
	while (ret.y > 0 && dist < maxdist && !colliding(ret.x, ret.y, ret.z))
	{
		float tx = ret.x - mx,
			 ty = ret.y - my,
			 tz = ret.z - mz;
		if (colliding(tx, ty, tz) && !_colliding)
			break;
		ret.x = tx;
		ret.y = ty;
		ret.z = tz;
		dist = sqrt(pow((x - ret.x), 2) + pow((y - ret.y), 2) + pow((z - ret.z), 2));
	}
	//RND(ret.x);
	//RND(ret.y);
	//RND(ret.z);
	ret.accurate = dist <= maxdist;
	return ret;
}

void processMovement()
{
    float fraction = 0.016f;
	float tx = x, ty = y, tz = z;
	int numkeys = 0;
	if (movement.a) numkeys++;
	if (movement.s) numkeys++;
	if (movement.d) numkeys++;
	if (movement.w) numkeys++;
	fraction /= (float)numkeys;
    if (movement.a)
    {
        tx += cos(anglexy) * fraction;
        tz += sin(anglexy) * fraction;
    }
    if (movement.d)
    {
        tx -= cos(anglexy) * fraction;
        tz -= sin(anglexy) * fraction;
    }
    if (movement.w)
    {
        tx -= lx * fraction;
        tz -= lz * fraction;
    }
    if (movement.s)
    {
        tx += lx * fraction;
        tz += lz * fraction;
    }
    if (movement.jump)
    {
        gravjump = true;
        gravfall = false;
    }
    else
    {
        gravjump = false;
        gravfall = true;
    }
    moveTo(tx, ty, tz);
}

void idle(void)
{
    processMovement();
	gravity();
	glutPostRedisplay();
}
