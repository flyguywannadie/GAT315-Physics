#pragma once
#include "body.h"
#include "raylib.h"

typedef struct mfBody mfBody;

extern mfBody* mfBodies;
extern int mfBodyCount;
extern Vector2 mfGravity;

mfBody* CreateBody( Vector2 position, float mass, mfBodyType bodytype);
void AddBody(mfBody* body);
void DestroyBody(mfBody* body);
void DestroyAllBodies();