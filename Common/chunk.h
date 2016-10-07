#ifndef CHUNK_H
#define CHUNK_H

#include "structures.h"

block_t *atInChunk(chunk_t *chnk, float x, float y, float z);
bool inChunk(chunk_t *chnk, float x, float y, float z);

#endif
