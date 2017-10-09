#include "gl_vars.hpp"

// angle of rotation for the camera direction
float anglexy=0.0,anglev=0.0;
// actual vector representing the camera's direction
float lx=0.0f,ly=0.0f,lz=-1.0f,l2x=0.0f,l2z=0.0f;
// XZ position of the camera
float x=0.0f,y=1.0f,z=5.0f;
bool gravfall = false;
bool gravjump = false;
// mouse positions
int mousex = 0, mousey = 0;
// window size
int w = 1024, h = 768;
// current crosshair
struct vector3d lat;
// world objects
std::vector<struct vector3d> boxes;
bool destroyTool = false;

struct move_struct_s movement;

std::vector<gameObjectBase *> *nonparticles;
