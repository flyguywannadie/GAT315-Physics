#pragma once

typedef struct mfSpring {
	struct mfBody* body1;
	struct mfBody* body2;
	float restlength;
	float k; //stiffness

	struct mfSpring* next;
	struct mfSpring* prev;

} mfSpring_t;

extern mfSpring_t* mfSprings;

mfSpring_t* CreateSpring(struct mfBody* body1, struct mfBody* body2, float restlength, float k);
void AddSpring(mfSpring_t* body);
void DestroySpring(mfSpring_t* body);
void DestroyAllSprings();

void ApplySpringForce(mfSpring_t* spring);
