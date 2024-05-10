#include "editor.h"
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
    mfeditorData.DampingValue = 0.1f;
    mfeditorData.GravityScaleValue = 1.0f;
    mfeditorData.BodyTypeDropdownEditMode = false;
    mfeditorData.BodyTypeDropdownActive = 0;
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
        GuiSliderBar((Rectangle) { mfeditorData.anchor01.x + 112, mfeditorData.anchor01.y + 96, 120, 16 }, "Mass Min", NULL, & mfeditorData.MassminValue, 0, 10);
        GuiSliderBar((Rectangle) { mfeditorData.anchor01.x + 112, mfeditorData.anchor01.y + 120, 120, 16 }, "Mass Max", NULL, & mfeditorData.MassmaxValue, 0, 10);
        GuiSliderBar((Rectangle) { mfeditorData.anchor01.x + 112, mfeditorData.anchor01.y + 144, 120, 16 }, "Damping", NULL, & mfeditorData.DampingValue, 0, 5);
        GuiSliderBar((Rectangle) { mfeditorData.anchor01.x + 112, mfeditorData.anchor01.y + 168, 120, 16 }, "Gravity Scale", NULL, & mfeditorData.GravityScaleValue, 0, 10);
        GuiSliderBar((Rectangle) { mfeditorData.anchor01.x + 88, mfeditorData.anchor01.y + 240, 120, 16 }, "Gravitation", NULL, & mfeditorData.GravitationValue, -20, 20);
        GuiGroupBox((Rectangle) { mfeditorData.anchor01.x + 16, mfeditorData.anchor01.y + 40, 232, 168 }, "Body");
        GuiGroupBox((Rectangle) { mfeditorData.anchor01.x + 16, mfeditorData.anchor01.y + 224, 232, 112 }, "World");
        if (GuiDropdownBox((Rectangle) { mfeditorData.anchor01.x + 32, mfeditorData.anchor01.y + 56, 200, 32 }, "DYNAMIC;KINEMATIC;STATIC", & mfeditorData.BodyTypeDropdownActive, mfeditorData.BodyTypeDropdownEditMode)) mfeditorData.BodyTypeDropdownEditMode = !mfeditorData.BodyTypeDropdownEditMode;
    }

    GuiUnlock();

    DrawTexture(cursorTexture, (int)position.x - (cursorTexture.width/3), (int)position.y - (cursorTexture.height / 3), WHITE);
}
