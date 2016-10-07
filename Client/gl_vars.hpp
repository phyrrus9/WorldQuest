#ifndef GL_VARS_HPP
#define GL_VARS_HPP

#include "../Common/structures.h"
#include <vector>

// angle of rotation for the camera direction
extern float anglexy, anglev;
// actual vector representing the camera's direction
extern float lx, ly, lz, l2x, l2z;
// XZ position of the camera
extern float x, y, z;
extern bool gravaccel;
// mouse positions
extern int mousex, mousey;
// window size
extern int h, w;
// current crosshair
extern struct vector3d lat;
// world objects
extern std::vector<struct vector3d> boxes;
extern bool destroyTool;

#endif
