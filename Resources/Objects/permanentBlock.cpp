#include "permanentBlock.h"
#define GLUT_DISABLE_ATEXIT_HACK
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>

permanentBlock::permanentBlock(struct vector3d position) : gameObjectBase("Permanent Block")
{
    this->m_pro_position = position;
    printf("\t box at %.3f %.3f %.3f\n",
           *this->mptr_positionX,
           *this->mptr_positionY,
           *this->mptr_positionZ);
    this->m_pro_size = { 1, 1, 1};
    this->m_pro_mass = 99999; // make it seriously dense
}

permanentBlock::~permanentBlock()
{
}

void permanentBlock::mfnc_load()
{
    vector3d box = this->m_pro_position;
    glTranslatef(box.x, box.y, box.z);
    glColor3f(0,0,0);
    glutWireCube(1);
    glColor3f(0.5f, 0.1f, 0.4f);
    glutSolidCube(0.99);
}
