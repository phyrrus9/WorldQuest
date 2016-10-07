#ifndef INPUT_H
#define INPUT_H

void processMouseMove(int x, int y);
void processMouseClick(int button, int state, int x, int y);
void processKeys(unsigned char key, int xx, int yy);
void processSpecialKeys(int key, int xx, int yy);

#endif
