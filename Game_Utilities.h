
#include "raylib.h"

enum GameState {
    MAIN_MENU,
    GAMEPLAY,
    RULES,
    RESUME
};

extern GameState state;
const int WindowWidth = 600;
const int WindowHeight = 600;

extern bool isQuitPressed;

extern Rectangle destRect;

extern Vector2 PlayPosi;
extern Rectangle PLAY_BUTTON;

extern Vector2 RulesPosi;
extern Rectangle RULES_BUTTON;

extern Vector2 QuitPosi;
extern Rectangle QUIT_BUTTON;

extern Vector2 BackPosi;
extern Rectangle BACK_BUTTON;

extern Vector2 ResumePosi;
extern Rectangle RESUME_BUTTON;

extern Vector2 ReturnPosi;
extern Rectangle RETURN_BUTTON;