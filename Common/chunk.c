#include "structures.h"
#include <stdlib.h>

block_t *atInChunk(chunk_t *chnk, float x, float y, float z)
{
	const int maxx = chnk->startx + CHUNKXZ;
	const int maxy = chnk->starty + CHUNKY;
	const int maxz = chnk->startz + CHUNKXZ;
	const int tx = x;
	const int ty = y;
	const int tz = z;
	if (
			(
				(tx > maxx) ||
				(ty > maxy) ||
				(tz > maxz)
			) ||
			(
				(tx < chnk->startx) ||
				(ty < chnk->starty) ||
				(tz < chnk->startz)
			)
		) return NULL;
	return &chnk->data[tx][ty][tz];
}

bool inChunk(chunk_t *chnk, float x, float y, float z)
{
	return atInChunk(chnk, x, y, z) != NULL;
}
