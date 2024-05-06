#include "world.h"
#include "body.h"
#include "stdlib.h"
#include "string.h"
#include <assert.h>

mfBody* mfBodies = NULL;
int mfBodyCount = 0;
Vector2 mfGravity;

mfBody* CreateBody() {
	mfBody* newbody;
	newbody = (mfBody*)malloc(sizeof(mfBody));

	assert(newbody != NULL);

	memset(newbody, 0, sizeof(mfBody));

	newbody->prev = NULL;
	newbody->next = mfBodies;

	if (mfBodies != NULL) {
		mfBodies->prev = newbody;
	}

	mfBodies = newbody;
	mfBodyCount++;

	return newbody;
}

void DestroyBody(mfBody* body) {
	assert(body != NULL);

	if (body->prev != NULL) {
		body->prev->next = body->next;
	}

	if (body->next != NULL) {
		body->next->prev = body->prev;
	}

	if (body == mfBodies) {
		mfBodies = body->next;
	}

	mfBodyCount--;
	free(body);
}