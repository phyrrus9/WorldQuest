#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdbool.h>

#define CHUNKXZ 150
#define CHUNKY	 50

struct vector3d
{
	float x, y, z;
	bool accurate;
};

struct __block_s
{
	unsigned int blockid;
	int defense;
};

struct __chunk_s
{
	unsigned int chunkid;
	struct __block_s data[CHUNKXZ][CHUNKY][CHUNKXZ]; //X, Y, Z
	int startx;
	int starty;
	int startz;
	//blocks always go to (startx + CHUNKXZ), (starty + CHUNKY), (startz + CHUNKXZ)
};

struct __imgpixel_s
{
	unsigned char r, g, b, a;
};

typedef struct __block_s block_t;
typedef struct __chunk_s chunk_t;
typedef struct __imgpixel_s imgpixel_t;

#endif
