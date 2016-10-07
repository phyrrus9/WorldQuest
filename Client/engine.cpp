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

struct vector3d lookingAt(bool _colliding = false);

void gravity(void)
{
	float ty = y - 0.205;
	if ((gravaccel = moveTo(x, ty, z)) == false)
		moveTo(x, (int)y + 0.1f, z);
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

bool colliding(float x, float y, float z)
{
	RND(x);
	RND(y);
	RND(z);
	for (unsigned int i = 0; i < boxes.size(); i++)
	{
		struct vector3d box = boxes.at(i);
		if (box.x == x && box.y == y && box.z == z)
			return true;
	}
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
	RND(ret.x);
	RND(ret.y);
	RND(ret.z);
	ret.accurate = dist <= maxdist;
	return ret;
}

void idle(void)
{
	gravity();
	glutPostRedisplay();
}
