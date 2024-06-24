#include "raylib.h"
#include "Assets.h"
#include "Game_States.h"
#include "Game_Utilities.h"
#include "Game_Functions.h"

int main() {
    InitWindow(WindowWidth, WindowHeight, "12 Beads Game!!");
    InitAudioDevice();
    SetTargetFPS(60);

    GameFunctions::ReadGameAssetsFromFile();

    PlaySound(mainMenuMusic);

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (state == MAIN_MENU)     RunMainMenu();
        
        else if (state == GAMEPLAY) RunGameplay();
        
        else if (state == RESUME)   ResumeGame();
        
        else if (state == RULES)    DisplayRulesPage();
        
        if (isQuitPressed)  break;

        EndDrawing();
    }
    GameFunctions::UnloadGameAssets();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}