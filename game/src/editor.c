#include "editor.h"
#include "body.h"
#include "render.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

bool ncEditorActive = true;
bool ncEditorIntersect = false;

mfEditorData mfeditorData;

Rectangle editorRect;

Vector2 anchor01 = { 1000, 64 };

Texture2D cursorTexture;

bool EditorBoxActive = true;

void InitEditor()
{
    GuiLoadStyle("raygui/styles/lavanda/style_lavanda.rgs");

    Image image = LoadImage("resources/dino.PNG");
    cursorTexture = LoadTextureFromImage(image);
    UnloadImage(image);

    HideCursor();

    mfeditorData.anchor01 = (Vector2){ 792, 56 };

    mfeditorData.EditorBoxActive = true;
    mfeditorData.MassminValue = 1.0f;
    mfeditorData.MassmaxValue = 5.0f;
    mfeditorData.GravitationValue = 0.0f;
    mfeditorData.DampingValue = 1.2f;
    mfeditorData.GravityScaleValue = 0.0f;
    mfeditorData.BodyTypeDropdownEditMode = false;
    mfeditorData.BodyTypeDropdownActive = 0;
    mfeditorData.StiffnessValue = 1.0f;
    mfeditorData.RestLengthValue = 3.0f;
}

void UpdateEditor(Vector2 position)
{
    //
}

void DrawEditor(Vector2 position)
{
    if (mfeditorData.BodyTypeDropdownEditMode) GuiLock();

    if (mfeditorData.EditorBoxActive)
    {
        mfeditorData.EditorBoxActive = !GuiWindowBox((Rectangle) { mfeditorData.anchor01.x + 0, mfeditorData.anchor01.y + 0, 264, 640 }, "Editor");
        GuiSliderBar((Rectangle) { mfeditorData.anchor01.x + 112,  mfeditorData.anchor01.y + 120, 120, 16 }, "Mass Max", NULL, &  mfeditorData.MassmaxValue, 5, 10);
        GuiSliderBar((Rectangle) {  mfeditorData.anchor01.x + 112,  mfeditorData.anchor01.y + 96, 120, 16 }, "Mass Min", NULL, &  mfeditorData.MassminValue, 0, 10);
        GuiSliderBar((Rectangle) {  mfeditorData.anchor01.x + 88,  mfeditorData.anchor01.y + 272, 120, 16 }, "Gravitation", NULL, &  mfeditorData.GravitationValue, -20, 20);
        GuiGroupBox((Rectangle) { mfeditorData.anchor01.x + 16,  mfeditorData.anchor01.y + 40, 232, 200 }, "Body");
        GuiGroupBox((Rectangle) { mfeditorData.anchor01.x + 16,  mfeditorData.anchor01.y + 256, 232, 112 }, "World");
        GuiSliderBar((Rectangle) {  mfeditorData.anchor01.x + 112,  mfeditorData.anchor01.y + 144, 120, 16 }, "Damping", NULL, &  mfeditorData.DampingValue, 0, 10);
        GuiSliderBar((Rectangle) {  mfeditorData.anchor01.x + 112,  mfeditorData.anchor01.y + 168, 120, 16 }, "Gravity Scale", NULL, &  mfeditorData.GravityScaleValue, 0, 100);
        GuiSliderBar((Rectangle) {  mfeditorData.anchor01.x + 112,  mfeditorData.anchor01.y + 192, 120, 16 }, "Stiffness (k)", NULL, &  mfeditorData.StiffnessValue, 0, 20);
        GuiSliderBar((Rectangle) {  mfeditorData.anchor01.x + 112,  mfeditorData.anchor01.y + 216, 120, 16 }, "Rest Length", NULL, &  mfeditorData.RestLengthValue, 0, 10);
        if (GuiDropdownBox((Rectangle) { mfeditorData.anchor01.x + 32, mfeditorData.anchor01.y + 56, 200, 32 }, "DYNAMIC;KINEMATIC;STATIC", &  mfeditorData.BodyTypeDropdownActive,  mfeditorData.BodyTypeDropdownEditMode))  mfeditorData.BodyTypeDropdownEditMode = ! mfeditorData.BodyTypeDropdownEditMode;
    }

    DrawTexture(cursorTexture, (int)position.x - (cursorTexture.width/3), (int)position.y - (cursorTexture.height / 3), WHITE);

    GuiUnlock();
}

mfBody* GetBodyIntersect(mfBody* bodies, Vector2 position)
{
    for (mfBody* body = bodies; body; body = body->next)
    {
        Vector2 screen = ConvertWorldToScreen(body->position);
        if (CheckCollisionPointCircle(position, screen, ConvertWorldToPixel(body->mass)))
        {
            return body;
        }
    }

    return NULL;
}

void DrawLineBodyToPosition(mfBody* body, Vector2 position)
{
    Vector2 screen = ConvertWorldToScreen(body->position);
    DrawLine((int)screen.x, (int)screen.y, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, YELLOW);
}