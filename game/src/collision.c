#include "Collision.h"
#include "contact.h"
#include "body.h"
#include "mathf.h"

#include "raymath.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

bool Intersects(mfBody* body1, mfBody* body2) {
	float distance = Vector2Distance(body1->position, body2->position);
	float radius = body1->mass + body2->mass;

	return distance <= radius;
}

void CreateContacts(mfBody* bodies, ncContact_t** contacts)
{
	for (mfBody* body1 = bodies; body1; body1 = body1->next) 
	{
		for (mfBody* body2 = bodies; body2; body2 = body2->next) 
		{
			if (body1 == body2) continue;
			if (body1->type != BT_DYNAMIC && body2->type != BT_DYNAMIC) continue;

			if (Intersects(body1, body2)) 
			{
				ncContact_t* contact = GenerateContact(body1, body2);
				AddContact(contact, contacts);
			}
		}
	}
}

ncContact_t* GenerateContact(mfBody* body1, mfBody* body2)
{
	ncContact_t* contact = (ncContact_t*)malloc(sizeof(ncContact_t));
	assert(contact);

	memset(contact, 0, sizeof(ncContact_t));

	contact->body1 = body1;
	contact->body2 = body2;

	Vector2 direction = Vector2Subtract(body1->position, body2->position);
	float distance = Vector2Length(direction);
	if (distance == 0)
	{
		direction = (Vector2){ GetRandomFloatValue(-0.05f, 0.05f), GetRandomFloatValue(-0.05f, 0.05f) };
	}

	float radius = (body1->mass + body2->mass);

	contact->depth = radius - distance;
	contact->normal = Vector2Normalize(direction);
	contact->restitution = (body1->restitution + body2->restitution) * 0.5f;

	return contact;
}

void SeparateContacts(ncContact_t* contacts)
{
	for (ncContact_t* contact = contacts; contact; contact = contact->next) {
		float totalInverseMass = contact->body1->inverseMass + contact->body2->inverseMass;
		Vector2 separationVector = Vector2Scale(contact->normal, contact->depth/totalInverseMass);

		contact->body1->position = Vector2Add(contact->body1->position, Vector2Scale(separationVector, contact->body1->inverseMass));
		contact->body2->position = Vector2Add(contact->body2->position, Vector2Scale(separationVector, -contact->body2->inverseMass));
	}
}

void ResolveContacts(ncContact_t* contacts)
{
	for (ncContact_t* contact = contacts; contact; contact = contact->next) {
		Vector2 relativeVelcoity = Vector2Subtract(contact->body1->velocity, contact->body2->velocity);
		float normalVelocity = Vector2DotProduct(relativeVelcoity, contact->normal);

		if (normalVelocity > 0) continue;

		float totalInverseMagnitude = contact->body1->inverseMass + contact->body2->inverseMass;
		float impulseMagnitude = (-(1 + contact->restitution) * (normalVelocity / totalInverseMagnitude));

		Vector2 impulse = Vector2Scale(contact->normal, impulseMagnitude);
		ApplyForce(contact->body1, impulse, FM_IMPULSE);
		ApplyForce(contact->body2, Vector2Negate(impulse), FM_IMPULSE);
	}
}
