#pragma once
#include "raylib.h"

typedef struct mfEditorData {
    Vector2 anchor01;

    bool EditorBoxActive;
    float MassmaxValue;
    float MassminValue;
    float GravitationValue;
    float DampingValue;
    float GravityScaleValue;
    bool BodyTypeDropdownEditMode;
    int BodyTypeDropdownActive;
} mfEditorData;

extern mfEditorData mfeditorData;

extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 position);
void DrawEditor(Vector2 position);

struct mfBody* GetBodyIntersect(
    struct mfBody* bodies,
    Vector2 position
);
void DrawLineBodyToPosition(struct mfBody* body, Vector2 position);