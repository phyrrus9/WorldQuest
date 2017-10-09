#include "gameObjectBase.hpp"
#include "../Client/engine.hpp"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* begin helper proto */
struct vector3d vec_add(vector3d *, vector3d *);
struct vector3d vec_neg(vector3d *);
char* strdup (const char* s);
/* end helper proto */
gameObjectBase::gameObjectBase(const char * name)
{
    this->mcstr_name = (const char *)strdup(name);
    this->m_dead = false;
    this->mptr_positionX = &this->m_pro_position.x;
    this->mptr_positionY = &this->m_pro_position.y;
    this->mptr_positionZ = &this->m_pro_position.z;
    this->m_pri_lastPhysCalculation = 0; // init physics timer
}
gameObjectBase::~gameObjectBase()
{
    printf("Destroying object named %s from (%0.3f, %0.3f, %0.3f)",
           this->mcstr_name, this->m_pro_position.x, this->m_pro_position.y, this->m_pro_position.z);
    free((void *)this->mcstr_name);
}
struct vector3d gameObjectBase::mfnc_restrict_size()
{
    return this->m_pro_size;
}
struct vector3d gameObjectBase::mfnc_restrict_move()
{
    struct vector3d newPosition;
    float deltaT;
    clock_t currentPhysCalculation;
    newPosition = this->m_pro_position;
    if (this->m_pri_lastPhysCalculation != 0)
    {
        currentPhysCalculation = clock();
        deltaT = (double)(currentPhysCalculation - this->m_pri_lastPhysCalculation) / (double)CLOCKS_PER_SEC; // time between last physics computation
        if (deltaT < .007) return this->m_pro_position; // no useful physics computations can be done on short scales
        this->m_pri_restrict_physGravity(deltaT); // first, compute effects of gravity on object
        this->mfnc_derrivedPhysics(deltaT); // then, call chain loader for additional physics
        newPosition = vec_add(&this->m_pro_position, &this->m_pro_velocity); // calculate the movement
    }
    this->m_pri_lastPhysCalculation = clock();
    return newPosition; // data sent back to game engine to process collisions
}
void gameObjectBase::m_pri_restrict_physGravity(float delta)
{
    float u, v;
    u = this->m_pro_velocity.y; // initial velocity
    v = u + (ACCEL * delta); // velocity = velocity_initial + (accel * time) /* kinematics */
    v = v > 40 ? 40 : v; // max upward velocity
    v = v < -40 ? -40 : v; // max downward velocity
    this->m_pro_velocity.y = v; // write back into velocity vector
}
void gameObjectBase::mfnc_derrivedPhysics(float delta) { /* intentionally left blank */ }
void gameObjectBase::mfnc_load() { /* intentionally left blank */ }
void gameObjectBase::mfnc_externcall_collide(gameObjectBase *object)
{
    printf("Object named %s collided with %s at (%0.3f, %0.3f, %0.3f)",
           object->mcstr_name, this->mcstr_name,
           this->m_pro_position.x, this->m_pro_position.y, this->m_pro_position.z);
}
/* begin helper code */
struct vector3d vec_add(vector3d *a, vector3d *b)
{
    struct vector3d vec = *a;
    vec.x += b->x;
    vec.y += b->y;
    vec.z += b->z;
    return vec;
}
struct vector3d vec_neg(vector3d *a)
{
    struct vector3d vec;
    vec.x = -a->x;
    vec.y = -a->y;
    vec.z = -a->z;
    return vec;
};
/* end helper code */
