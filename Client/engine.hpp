#ifndef ENGINE_HPP
#define ENGINE_HPP

/* acceleration, based on 9.81m/s/s and 0.838u/m */
#define ACCEL 8.22

bool moveTo(float tx, float ty, float tz);
void gravity(void);
bool colliding(float x, float y, float z, float newosize = 0);
void idle(void);

#endif
