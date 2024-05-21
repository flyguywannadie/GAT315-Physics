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

#define EDITOR_DATA(data) TextFormat("%0.2f", data), &data

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
    mfeditorData.GravityScaleValue = 1.0f;
    mfeditorData.BodyTypeDropdownEditMode = false;
    mfeditorData.BodyTypeDropdownActive = 0;
    mfeditorData.StiffnessValue = 1.0f;
    mfeditorData.RestLengthValue = 3.0f;
    mfeditorData.TimeStepValue = 50.0f;
    mfeditorData.GravityValue = -1.0f;
    bool ResetButtonPressed = false;
    bool SimulateToggleActive = true;
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
        GuiSliderBar((Rectangle) { mfeditorData.anchor01.x + 112,  mfeditorData.anchor01.y + 120, 120, 16 }, "Mass Max", EDITOR_DATA(mfeditorData.MassmaxValue), 5, 10);
        GuiSliderBar((Rectangle) {  mfeditorData.anchor01.x + 112,  mfeditorData.anchor01.y + 96, 120, 16 }, "Mass Min", EDITOR_DATA(mfeditorData.MassminValue), 0, 10);
        GuiGroupBox((Rectangle) { mfeditorData.anchor01.x + 16,  mfeditorData.anchor01.y + 40, 232, 200 }, "Body");
        GuiGroupBox((Rectangle) { mfeditorData.anchor01.x + 16,  mfeditorData.anchor01.y + 256, 232, 112 }, "World");
        GuiSliderBar((Rectangle) {  mfeditorData.anchor01.x + 112,  mfeditorData.anchor01.y + 144, 120, 16 }, "Damping", EDITOR_DATA(mfeditorData.DampingValue), 0, 10);
        GuiSliderBar((Rectangle) {  mfeditorData.anchor01.x + 112,  mfeditorData.anchor01.y + 168, 120, 16 }, "Gravity Scale", EDITOR_DATA(mfeditorData.GravityScaleValue), 0, 100);
        GuiSliderBar((Rectangle) {  mfeditorData.anchor01.x + 112,  mfeditorData.anchor01.y + 192, 120, 16 }, "Stiffness (k)", EDITOR_DATA(mfeditorData.StiffnessValue), 0, 20);
        GuiSliderBar((Rectangle) { mfeditorData.anchor01.x + 112, mfeditorData.anchor01.y + 216, 120, 16 }, "Rest Length", EDITOR_DATA(mfeditorData.RestLengthValue), 0, 10);
        GuiSliderBar((Rectangle) { mfeditorData.anchor01.x + 112, mfeditorData.anchor01.y + 360, 120, 16 }, "Time Step", EDITOR_DATA(mfeditorData.TimeStepValue), 0, 100);
        GuiSlider((Rectangle) { mfeditorData.anchor01.x + 112, mfeditorData.anchor01.y + 336, 120, 16 }, "Gravity", EDITOR_DATA(mfeditorData.GravityValue), -10, 10);
        GuiSlider((Rectangle) { mfeditorData.anchor01.x + 112, mfeditorData.anchor01.y + 312, 120, 16 }, "Gravitation", EDITOR_DATA(mfeditorData.GravitationValue), -20, 20);
        mfeditorData.ResetButtonPressed = GuiButton((Rectangle) { mfeditorData.anchor01.x + 16, mfeditorData.anchor01.y + 584, 88, 32 }, "Reset");
        GuiToggle((Rectangle) { mfeditorData.anchor01.x + 160, mfeditorData.anchor01.y + 584, 88, 32 }, "Simulate", & mfeditorData.SimulateToggleActive);
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
    DrawLine((int)screen.x, (int)screen.y, (int)position.x, (int)position.y, YELLOW);
}