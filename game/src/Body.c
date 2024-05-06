#include "body.h"
#include "world.h"
#include "Integrater.h"

void Step(mfBody* body, float timestep) {
	body->force = Vector2Add(body->force, Vector2Scale(Vector2Scale(mfGravity, body->gravityScale), body->mass));
	body->acceleration = Vector2Scale(body->force, body->inverseMass);
	
	ExplicitEuler(body, timestep);

	// Apply damping
	float damping = 1.0f / (1.0f + (body->damping * timestep));
	body->velocity = Vector2Scale(body->velocity, damping);

	ClearForce(body);
}
