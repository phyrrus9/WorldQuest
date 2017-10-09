#ifndef GAMEOBJECTBASE_H
#define GAMEOBJECTBASE_H

#include "../Common/structures.h"
#include <vector>
#include <time.h>

class gameObjectBase
{
    public:
        gameObjectBase(const char * name);
        virtual ~gameObjectBase();
        const char * mcstr_name;
        float * mptr_positionX;
        float * mptr_positionY;
        float * mptr_positionZ;
        bool m_dead; // set true when object should be deleted
        struct vector3d mfnc_restrict_move(); // returns position to move to
        struct vector3d mfnc_restrict_size(); // returns object's size vector to game engine
        virtual void mfnc_derrivedPhysics(float delta); // override method for additional (non-grav) physics
        virtual void mfnc_load(); // override method for drawing & texturizing on display
        virtual void mfnc_externcall_collide(gameObjectBase *object); // overload function with collision effects
    protected:
        float m_pro_mass;
        struct vector3d m_pro_size;
        struct vector3d m_pro_position;
        struct vector3d m_pro_velocity;
    private:
        clock_t m_pri_lastPhysCalculation;
        void m_pri_restrict_physGravity(float delta); // called by mfnc_restrict_move in preamble
};

#endif // GAMEOBJECTBASE_H
