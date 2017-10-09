#include <windows.h>
#include <fcntl.h>
#include <stdio.h>

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

void init()
{
    nonparticles = new std::vector<gameObjectBase *>; // list to hold physics properties
}

void openconsole()
{
    AllocConsole();

    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
    FILE* hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, NULL, _IONBF, 1);
    *stdout = *hf_out;

    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
    FILE* hf_in = _fdopen(hCrt, "r");
    setvbuf(hf_in, NULL, _IONBF, 128);
    *stdin = *hf_in;
}

int main(int argc, char **argv)
{
	w = 1024;
	h = 768;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(2880 - (w/2),540 - (h/2));
	glutInitWindowSize(w, h);
	glutCreateWindow("WorldQuest Engine: Alpha");
	glutWarpPointer(w/2, h/2);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(resizeWindow);
	glutIdleFunc(idle);
	glutKeyboardFunc(processDownKeys);
	glutKeyboardUpFunc(processUpKeys);
	glutSpecialFunc(processSpecialKeys);
	glutPassiveMotionFunc(processMouseMove);
	glutMouseFunc(processMouseClick);
	glEnable(GL_DEPTH_TEST);
	glutIgnoreKeyRepeat(1);
	init(); // initialize globals
	openconsole();
	glutMainLoop();
	return 1;
}
