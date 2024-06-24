#include"Game_Utilities.h"
#include "raylib.h"

bool isQuitPressed = false;

GameState state = MAIN_MENU;

Rectangle destRect = { 0, 0, WindowWidth, WindowHeight };

Vector2 PlayPosi;
Rectangle PLAY_BUTTON;

Vector2 RulesPosi;
Rectangle RULES_BUTTON;

Vector2 QuitPosi;
Rectangle QUIT_BUTTON;

Vector2 BackPosi;
Rectangle BACK_BUTTON;

Vector2 ResumePosi;
Rectangle RESUME_BUTTON;

Vector2 ReturnPosi;
Rectangle RETURN_BUTTON;