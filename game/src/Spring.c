#include "Spring.h"
#include "body.h"
#include "stdlib.h"
#include "string.h"
#include <assert.h>

mfSpring_t* mfSprings = NULL;
int springCount = 0;
Vector2 mfGravity;

mfSpring_t* CreateSpring(struct mfBody* body1, struct mfBody* body2, float restlength, float k) {
	mfSpring_t* newspring;
	newspring = (mfSpring_t*)malloc(sizeof(mfSpring_t));

	assert(newspring != NULL);

	memset(newspring, 0, sizeof(mfSpring_t));

	newspring->body1 = body1;
	newspring->body2 = body2;
	newspring->restlength = restlength;
	newspring->k = k;

	return newspring;
}

void AddSpring(mfSpring_t* newspring) {
	assert(newspring);

	newspring->prev = NULL;
	newspring->next = mfSprings;

	if (mfSprings != NULL) {
		mfSprings->prev = newspring;
	}

	mfSprings = newspring;
	springCount++;
}

void DestroySpring(mfSpring_t* spring) {
	assert(spring != NULL);

	if (spring->prev != NULL) {
		spring->prev->next = spring->next;
	}

	if (spring->next != NULL) {
		spring->next->prev = spring->prev;
	}

	if (spring == mfSprings) {
		mfSprings = spring->next;
	}

	springCount--;
	free(spring);
}

void DestroyAllSprings()
{
}

void ApplySpringForce(mfSpring_t* spring)
{
	for (mfSpring_t* spring = mfSprings; spring; spring = spring->next)
	{
		Vector2 direction = Vector2Subtract(spring->body1->position, spring->body2->position);// <get direction vector from body2 to body1>
		if (direction.x == 0 && direction.y == 0) continue;

		float length = Vector2Length(direction);// <get length from direction>
		float x = length - spring->restlength;// <compute displacement from current length to resting length>;
		float force = -spring->k * x;// <compute force using product of displacement and stiffness(k)>;

		Vector2 ndirection = Vector2Normalize(direction);//<get direction normal>

		ApplyForce(spring->body1, Vector2Scale(ndirection, force), FM_FORCE);
		ApplyForce(spring->body2, Vector2Scale(Vector2Negate(ndirection), force), FM_FORCE);
	}
}
