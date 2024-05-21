#include "body.h"
#include "mathf.h"
#include "world.h"
#include "Integrater.h"
#include "force.h"
#include "editor.h"
#include "render.h"
#include "spring.h"
#include "Collision.h"
#include "contact.h"

#include "raylib.h"
#include "raymath.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 100

int main(void)
{
	mfBody* selectedBody = NULL;
	mfBody* connectBody = NULL;
	ncContact_t* contacts = NULL;

	float fixedTimeStep = 1.0f / 50.0f;
	float timeAccumulator;

	InitWindow(1280, 720, "raylib [core] example - basic window");
	InitEditor();
	SetTargetFPS(60);

	// Initialize World
	mfGravity = (Vector2){ 0,-1 };
	
	int rocketSelection = 0;
	enum { creeperSize = 54 }; // this is to make instruction arrays with so that I can make custom shapes with rockets

	//Body* bodies = (Body*)malloc(sizeof(Body) * MAX_BODIES);
	//assert(bodies != NULL);
	//int bodyCount = 0;


	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		if (IsKeyPressed(KEY_Q)) {
			rocketSelection--;
		}
		if (IsKeyPressed(KEY_E)) {
			rocketSelection++;
		}
		if (IsKeyPressed(KEY_R)) {
			rocketSelection = 0;
		}	
		if (IsKeyPressed(KEY_SPACE)) {
			mfBody* body = mfBodies;
			while (body != NULL) {
				mfBody* body2 = body->next;
				DestroyBody(body);
				body = body2;
			}
		}


		Vector2 position = GetMousePosition();

		ncScreenZoom += GetMouseWheelMove() * 0.2f;
		ncScreenZoom = Clamp(ncScreenZoom, 0.1f, 10.0f);

		UpdateEditor(position);

		//bodies[bodyCount].position = position;
		//bodies[bodyCount].velocity = CreateVector2(GetRandomFloatValue(-5, 5), GetRandomFloatValue(-5, 5));
		//bodyCount++;

		selectedBody = GetBodyIntersect(mfBodies, position);
		if (selectedBody) {
			Vector2 screen = ConvertWorldToScreen(selectedBody->position);
			DrawCircleLines(screen.x, screen.y, ConvertWorldToPixel(selectedBody->mass) + 5, YELLOW);
		}

		switch (rocketSelection) {
		case 0: // Basic Firework
			if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_F)))) {
				for (int i = 0; i < 1; i++) {
					mfBody* body = CreateBody(ConvertScreenToWorld(position), mfeditorData.MassminValue, mfeditorData.BodyTypeDropdownActive);
					body->damping = mfeditorData.DampingValue;
					body->gravityScale = mfeditorData.GravityScaleValue;
					body->color = ColorFromHSV(GetRandomValue(0, 360), 1, 1);

					AddBody(body);
				}
				break;
			}
		//case 1: // Creeper Minecraft Firework
		//	if (IsMouseButtonPressed(0)) { 
		//		Vector2 creeper[creeperSize];

		//		for (int i = 0; i < creeperSize; i++) {
		//			creeper[i] = (Vector2){ 0,0 };
		//		}
		//		//  0 0 0 0       0 0 0 0
		//		creeper[0] = (Vector2){ 10, -10 };
		//		creeper[1] = (Vector2){ 8, -10 };
		//		creeper[2] = (Vector2){ 6, -10 };
		//		creeper[3] = (Vector2){ 4, -10 };
		//		creeper[4] = (Vector2){ -10, -10 };
		//		creeper[5] = (Vector2){ -8, -10 };
		//		creeper[6] = (Vector2){ -6, -10 };
		//		creeper[7] = (Vector2){ -4, -10 };
		//		//  0     0       0     0
		//		creeper[8] = (Vector2){ 10, -8 };
		//		creeper[9] = (Vector2){ 4, -8 };
		//		creeper[10] = (Vector2){ -10, -8 };
		//		creeper[11] = (Vector2){ -4, -8 };
		//		//  0     0       0     0
		//		creeper[12] = (Vector2){ 10, -6 };
		//		creeper[13] = (Vector2){ 4, -6 };
		//		creeper[14] = (Vector2){ -10, -6 };
		//		creeper[15] = (Vector2){ -4, -6 };
		//		//  0 0 0 0       0 0 0 0
		//		creeper[16] = (Vector2){ 10, -4 };
		//		creeper[17] = (Vector2){ 8, -4 };
		//		creeper[18] = (Vector2){ 6, -4 };
		//		creeper[19] = (Vector2){ 4, -4 };
		//		creeper[20] = (Vector2){ -10, -4 };
		//		creeper[21] = (Vector2){ -8, -4 };
		//		creeper[22] = (Vector2){ -6, -4 };
		//		creeper[23] = (Vector2){ -4, -4 };
		//		//        0 0 0 0 0      
		//		creeper[24] = (Vector2){ 4, -2 };
		//		creeper[25] = (Vector2){ 2, -2 };
		//		creeper[26] = (Vector2){ 0, -2 };
		//		creeper[27] = (Vector2){ -2, -2 };
		//		creeper[28] = (Vector2){ -4, -2 };
		//		//    0 0 0       0 0 0  
		//		creeper[29] = (Vector2){ -8, 0 };
		//		creeper[30] = (Vector2){ -6, 0 };
		//		creeper[31] = (Vector2){ -4, 0 };
		//		creeper[32] = (Vector2){ 4, 0 };
		//		creeper[33] = (Vector2){ 6, 0 };
		//		creeper[34] = (Vector2){ 8, 0 };
		//		//    0               0  
		//		creeper[35] = (Vector2){ -8, 2 };
		//		creeper[36] = (Vector2){ 8, 2 };
		//		//    0   0 0 0 0 0   0  
		//		creeper[37] = (Vector2){ -8, 4 };
		//		creeper[38] = (Vector2){ -4, 4 };
		//		creeper[39] = (Vector2){ -2, 4 };
		//		creeper[40] = (Vector2){ 0, 4 };
		//		creeper[41] = (Vector2){ 2, 4 };
		//		creeper[42] = (Vector2){ 4, 4 };
		//		creeper[43] = (Vector2){ 8, 4 };
		//		//    0   0       0   0  
		//		creeper[44] = (Vector2){ -8, 6 };
		//		creeper[45] = (Vector2){ -4, 6 };
		//		creeper[46] = (Vector2){ 4, 6 };
		//		creeper[47] = (Vector2){ 8, 6 };
		//		//    0 0 0       0 0 0  
		//		creeper[48] = (Vector2){ -8, 8 };
		//		creeper[49] = (Vector2){ -6, 8 };
		//		creeper[50] = (Vector2){ -4, 8 };
		//		creeper[51] = (Vector2){ 4, 8 };
		//		creeper[52] = (Vector2){ 6, 8 };
		//		creeper[53] = (Vector2){ 8, 8 };

		//		for (int i = 0; i < creeperSize; i++) {
		//			mfBody* body = CreateBody();
		//			body->position = position;
		//			//ApplyForce(body, CreateVector2(GetRandomFloatValue(-50, 50), GetRandomFloatValue(-50, 50)));
		//			body->mass = 3;
		//			body->inverseMass = 1 / body->mass;
		//			body->type = BT_DYNAMIC;
		//			body->damping = 2.5f;
		//			body->gravityScale = 1.0f;
		//			body->color = GREEN;
		//			ApplyForce(body, Vector2Scale(CreateVector2(creeper[i].x, creeper[i].y), 300), FM_IMPULSE);
		//		}
		//	}
		//		break;
		//case 2: // BLOOD SCREEN THING IDK
		//	if (IsMouseButtonDown(0)) { 
		//		for (int i = 0; i < 5; i++) {
		//			Vector2 startpos = CreateVector2(GetRandomValue(0, 1) * GetScreenWidth(), GetRandomValue(0, 1) * GetScreenHeight());

		//			if (GetRandomValue(0, 1) == 0) {
		//				startpos.x = GetRandomFloatValue(0, GetScreenWidth());
		//			}
		//			else {
		//				startpos.y = GetRandomFloatValue(0, GetScreenHeight());
		//			}

		//			mfBody* body = CreateBody();
		//			body->position = startpos;
		//			//ApplyForce(body, CreateVector2(GetRandomFloatValue(-50, 50), GetRandomFloatValue(-50, 50)));
		//			body->mass = GetRandomFloatValue(1, 5);
		//			body->inverseMass = 1 / body->mass;
		//			body->type = BT_DYNAMIC;
		//			body->damping = 2.5f;
		//			body->gravityScale = 0.1f;
		//			body->color = ColorFromHSV(GetRandomValue(0, 90), 1, 1);

		//			Vector2 forceDirection = Vector2Subtract(position, startpos);

		//			ApplyForce(body, Vector2Scale(forceDirection, (body->damping * body->mass)), FM_VELOCITY);
		//		}
		//		break;
		//	}
		//case 3: // spinning thing
		//	if (IsMouseButtonDown(0)) {
		//		mfBody* body = CreateBody();
		//		body->position = position;
		//		body->mass = 4;
		//		body->inverseMass = 1 / body->mass;
		//		body->type = BT_DYNAMIC;
		//		body->damping = 2.5f;
		//		body->gravityScale = 0.1f;
		//		body->color = ColorFromHSV(GetRandomValue(85, 90), 1, 1);

		//		ApplyForce(body, Vector2Scale(GetVector2FromAngle(mfBodyCount/6.0f), 1000 - mfBodyCount), FM_VELOCITY);
		//	}
		//	break;
		}

		// Apply Force
		//mfBody* body = mfBodies;
		//while (body) {
		//	ApplyForce(body, CreateVector2(0, 0), FM_FORCE);
		//	body = body->next;
		//}

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && selectedBody) {
			connectBody = selectedBody;
		}
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && connectBody) {
			DrawLineBodyToPosition(connectBody, position);
		}
		if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && connectBody) {
			if (selectedBody && connectBody != selectedBody) {
				mfSpring_t* spring = CreateSpring(connectBody, selectedBody, 5, 20);

				spring->restlength = mfeditorData.RestLengthValue;
				spring->k = mfeditorData.StiffnessValue;

				AddSpring(spring);
			}
		}


		timeAccumulator += dt;
		// update bodies
		while (timeAccumulator >= fixedTimeStep) {
			timeAccumulator -= fixedTimeStep;
			
			ApplyGravitation(mfBodies, mfeditorData.GravitationValue);
			ApplySpringForce(mfSprings);

			for (mfBody* body = mfBodies; body; body = body->next) {
				Step(body, dt);
			}

			// collision
			contacts = NULL;
			CreateContacts(mfBodies, &contacts);
			SeparateContacts(contacts);
			ResolveContacts(contacts);
		}

		// delete bodies
		mfBody* body = mfBodies;
		while (body != NULL) {
			mfBody* body2 = body->next;
			if (body->position.y > GetScreenHeight()) {
				DestroyBody(body);
			}
			body = body2;
		}

		// render
		BeginDrawing();
		ClearBackground(BLACK);
		// stats
		DrawText(TextFormat("FPS: %.2f (ms %.2fms)", fps, 1000/fps), 10, 10, 20, WHITE);
		DrawText(TextFormat("FPS: %.4f", dt), 10, 30, 20, LIME);
		//DrawCircle(position.x, position.y, 10, YELLOW);

		// draw bodies
		for (mfBody* body = mfBodies; body; body = body->next) {
			Vector2 screen = ConvertWorldToScreen(body->position);
			DrawCircle(screen.x, screen.y, ConvertWorldToPixel(body->mass * 0.5f), body->color);
		}
		// draw contacts
		for (ncContact_t* contact = contacts; contact; contact = contact->next) {
			Vector2 screen = ConvertWorldToScreen(contact->body1->position);
			DrawCircle(screen.x, screen.y, ConvertWorldToPixel(contact->body1->mass * 0.5f), contact->body1->color);
		}
		// draw springs
		for (mfSpring_t* spring = mfSprings; spring; spring = spring->next) {
			Vector2 screen1 = ConvertWorldToScreen(spring->body1->position);
			Vector2 screen2 = ConvertWorldToScreen(spring->body2->position);
			DrawLine(screen1.x, screen1.y, screen2.x, screen2.y, YELLOW);
		}
		//body = mfBodies;
		//while (body){
		//	DrawCircle(body->position.x, body->position.y, body->mass, RED);

		//	body = body->next;
		//}

		//DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
		DrawEditor(position);
		EndDrawing();
	}
	CloseWindow();

	free(mfBodies);

	//mfBody* body = mfBodies;
	//while (body) {
	//	DestroyBody(body);
	//	body = body->next;
	//}

	return 0;
}