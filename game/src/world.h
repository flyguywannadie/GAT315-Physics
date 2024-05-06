#pragma once
//#include "body.h"
#include "raylib.h"

typedef struct mfBody mfBody;

extern mfBody* mfBodies;
extern int mfBodyCount;
extern Vector2 mfGravity;

mfBody* CreateBody();
void DestroyBody(mfBody* body);