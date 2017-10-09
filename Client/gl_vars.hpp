#ifndef GL_VARS_HPP
#define GL_VARS_HPP

#include "../Common/structures.h"
#include "gameObjectBase.hpp"
#include <vector>
#include <list>

// angle of rotation for the camera direction
extern float anglexy, anglev;
// actual vector representing the camera's direction
extern float lx, ly, lz, l2x, l2z;
// XZ position of the camera
extern float x, y, z;
extern bool gravfall;
extern bool gravjump;
// mouse positions
extern int mousex, mousey;
// window size
extern int h, w;
// current crosshair
extern struct vector3d lat;
// world objects
extern std::vector<struct vector3d> boxes;
extern bool destroyTool;

struct move_struct_s
{
    bool w;
    bool a;
    bool s;
    bool d;
    bool jump;
};
extern struct move_struct_s movement;

extern std::vector<gameObjectBase *> *nonparticles;

#endif
