#ifndef MACROS_H
#define MACROS_H

#define RND(q) \
		if (q - (int)q > 0.5) q = (int)q + 1;\
		else q = (int)q;

#endif
