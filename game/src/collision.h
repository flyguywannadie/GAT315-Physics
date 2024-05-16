#pragma once
#include "raylib.h"

typedef struct ncContact ncContact_t;
typedef struct mfBody mfBody;

void CreateContacts(mfBody* bodies, ncContact_t** contacts);
ncContact_t* GenerateContact(mfBody* body1, mfBody* body2);

void SeparateContacts(ncContact_t* contacts);
void ResolveContacts(ncContact_t* contacts);