#define GLUT_DISABLE_ATEXIT_HACK
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "gl_vars.hpp"
#include "gfx.hpp"
#include "engine.hpp"
#include "input.hpp"

int main(int argc, char **argv)
{
	w = 1024;
	h = 768;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(w, h);
	glutCreateWindow("WorldQuest");
	glutWarpPointer(w/2, h/2);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(resizeWindow);
	glutIdleFunc(idle);
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	glutPassiveMotionFunc(processMouseMove);
	glutMouseFunc(processMouseClick);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 1;
}
