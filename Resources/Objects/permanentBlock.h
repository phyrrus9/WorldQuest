#ifndef PERMANENTBLOCK_H
#define PERMANENTBLOCK_H

#include "../../Client/gameObjectBase.hpp"

class permanentBlock : public gameObjectBase
{
    public:
        permanentBlock(struct vector3d position);
        virtual ~permanentBlock();
        void mfnc_load();
    protected:

    private:
};

#endif // PERMANENTBLOCK_H
