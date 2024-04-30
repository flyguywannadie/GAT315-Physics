#include "body.h"
#include "mathf.h"
#include "world.h"
#include "raylib.h"
#include "raymath.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 100

int main(void)
{

	InitWindow(1280, 720, "raylib [core] example - basic window");
	SetTargetFPS(60);

	//Body* bodies = (Body*)malloc(sizeof(Body) * MAX_BODIES);
	//assert(bodies != NULL);
	//int bodyCount = 0;


	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();
		if (IsMouseButtonPressed(0)) {
			//bodies[bodyCount].position = position;
			//bodies[bodyCount].velocity = CreateVector2(GetRandomFloatValue(-5, 5), GetRandomFloatValue(-5, 5));
			//bodyCount++;
			CreateBody();
			bodies->position = position;
			bodies->velocity = CreateVector2(GetRandomFloatValue(-5, 5), GetRandomFloatValue(-5, 5));
		}

		BeginDrawing();
		ClearBackground(BLACK);
		DrawText(TextFormat("FPS: %.2f (ms %.2fms)", fps, 1000/fps), 10, 10, 20, WHITE);
		DrawText(TextFormat("FPS: %.4f", dt), 10, 30, 20, LIME);

		DrawCircle(position.x, position.y, 10, YELLOW);

		Body* body = bodies;
		while (body){
			body->position = Vector2Add(body->position, body->velocity);

			DrawCircle(body->position.x, body->position.y, 5, RED);

			body = body->next;
		}

		//DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
		EndDrawing();
	}
	CloseWindow();

	free(bodies);

	return 0;
}