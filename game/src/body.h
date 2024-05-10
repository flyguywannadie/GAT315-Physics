#pragma once
#include "raylib.h"
#include "raymath.h"

typedef enum {
	BT_DYNAMIC,
	BT_KINEMATIC,
	BT_STATIC
} mfBodyType;

typedef enum
{
	FM_FORCE,
	FM_IMPULSE,
	FM_VELOCITY
} mfForceMode;

typedef struct mfBody
{
	mfBodyType type;

	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	Vector2 force;

	float mass;
	float inverseMass; // 1 / mass (static = 0)
	float gravityScale;
	float damping;

	Color color;

	struct mfBody* next;
	struct mfBody* prev;
} mfBody;

inline void ApplyForce(mfBody* body, Vector2 force, mfForceMode forceMode) {
	if (body->type != BT_DYNAMIC) {
		return;
	}

	switch (forceMode) {
		case FM_FORCE:
			body->force = Vector2Add(body->force, force);
			break;
		case FM_IMPULSE:
			// applies a sudden change in momentum
			body->velocity = Vector2Scale(force, body->inverseMass);
			break;
		case FM_VELOCITY:
			body->velocity = force;
			break;
	}
}

inline void ClearForce(mfBody* body) {
	body->force = Vector2Zero();
}

void Step(mfBody* body, float timestep);