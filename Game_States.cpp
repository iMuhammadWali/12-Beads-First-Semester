#include "raylib.h"
#include "Game_Utilities.h"
#include "Assets.h"
#include "Game_Functions.h"

//state MAIN_MENU
void LoadButtonDimensions() {

    PlayPosi = { 300, 255 };
    PLAY_BUTTON = { (PlayPosi.x - Play.width / 2) + 5,(PlayPosi.y - Play.height / 2) + 5, float(Play.width) , float(Play.height) };

    RulesPosi = { 300, 420 };
    RULES_BUTTON = { (RulesPosi.x - Rules.width / 2) + 5,(RulesPosi.y - Rules.height / 2) + 5,  float(Rules.width) ,  float(Rules.height) };

    QuitPosi = { 300, 500 };
    QUIT_BUTTON = { (QuitPosi.x - Quit.width / 2) + 5,(QuitPosi.y - Quit.height / 2) + 5, float(Quit.width), float(Quit.height) };

    ResumePosi = { 300, 340 };
    RESUME_BUTTON = { (ResumePosi.x - Resume.width / 2) + 5, (ResumePosi.y - Resume.height / 2) + 5, float(Resume.width) , float(Resume.height) };
}
void HandleMenuButtons() {

    DrawTexturePro(mainMenu, { 0, 0, static_cast<float>(mainMenu.width), static_cast<float>(mainMenu.height) }, destRect, { 0, 0 }, 0, WHITE);

    bool isSoundPlayed = false;
    bool MouseOnPlay = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, PLAY_BUTTON);
    bool MouseOnRules = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, RULES_BUTTON);
    bool MouseOnQuit = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, QUIT_BUTTON);
    bool MouseOnRes = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, RESUME_BUTTON);

    DrawTextureV(Play, { PlayPosi.x - Play.width / 2 ,PlayPosi.y - Play.height / 2 }, MouseOnPlay ? LIGHTGRAY : WHITE);
    DrawTextureV(Rules, { RulesPosi.x - Rules.width / 2 ,RulesPosi.y - Rules.height / 2 }, MouseOnRules ? LIGHTGRAY : WHITE);
    DrawTextureV(Quit, { QuitPosi.x - Quit.width / 2 ,QuitPosi.y - Quit.height / 2 }, MouseOnQuit ? LIGHTGRAY : WHITE);
    DrawTextureV(Resume, { ResumePosi.x - Resume.width / 2 ,ResumePosi.y - Resume.height / 2 }, MouseOnRes ? LIGHTGRAY : WHITE);

    if ((MouseOnPlay || MouseOnRules || MouseOnQuit || MouseOnRes) && !isSoundPlayed) {
        PlaySound(buttonHover);
        isSoundPlayed = true;
    }
    else if (!MouseOnPlay && !MouseOnRules && !MouseOnQuit && !MouseOnRes) {
        isSoundPlayed = false;
    }
}
void HandleMenuButtonClick() {
    int mouseX = GetMouseX();       int mouseY = GetMouseY();

    if (mouseX >= PlayPosi.x - 100 && mouseX <= PlayPosi.x + 100 && mouseY >= PlayPosi.y - 45 && mouseY <= PlayPosi.y + 45) {

        GameFunctions::ResetBeadPositions();
        PlaySound(gameMusic);
        GameFunctions::RandomizeTurn();
        state = GAMEPLAY;
        StopSound(mainMenuMusic);
    }
    if (mouseX >= ResumePosi.x - 100 && mouseX <= ResumePosi.x + 100 && mouseY >= ResumePosi.y - 45 && mouseY <= ResumePosi.y + 45)
        state = RESUME;

    if (mouseX >= RulesPosi.x - 100 && mouseX <= RulesPosi.x + 100 && mouseY >= RulesPosi.y - 45 && mouseY <= RulesPosi.y + 45)
        state = RULES;

    if (mouseX >= QuitPosi.x - 100 && mouseX <= QuitPosi.x + 100 && mouseY >= QuitPosi.y - 45 && mouseY <= QuitPosi.y + 45) {

        StopSound(mainMenuMusic);
        isQuitPressed = true;
    }
}
void RunMainMenu() {

    LoadButtonDimensions();
    HandleMenuButtons();
     
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        HandleMenuButtonClick();
    }
}

//state GAMEPLAY
void CheckWinner() {

    if (GameFunctions::CheckGameOutcome () == 10) {

        StopSound(gameMusic);

        //Draw the winning Screeen for White
        DrawTexturePro(whiteWin, { 0, 0, static_cast<float>(whiteWin.width), static_cast<float>(whiteWin.height) }, destRect, { 0, 0 }, 0, WHITE);

        if (!IsSoundPlaying(weHaveAWinner)) PlaySound(weHaveAWinner);

    }
    else if (GameFunctions::CheckGameOutcome() == 20) {

        StopSound(gameMusic);

        //Draw the winning Screeen for Blue
        DrawTexturePro(blueWin, { 0, 0, static_cast<float>(blueWin.width), static_cast<float>(blueWin.height) }, destRect, { 0, 0 }, 0, WHITE);

        if (!IsSoundPlaying(weHaveAWinner)) PlaySound(weHaveAWinner);
    }
}
void HandleSafeReturn() {

    if (IsKeyPressed(KEY_B) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

        if (IsKeyPressed(KEY_B) || CheckCollisionPointCircle({ (float)GetMouseX(),(float)GetMouseY() }, ReturnPosi, 30)) {
            GameFunctions::ResetBeadPositions();
            PlaySound(buttonHover);
            PlaySound(mainMenuMusic);

            StopSound(gameMusic);

            state = MAIN_MENU;
        }
    }
}
void HandleReturnButton() {

    ReturnPosi = { 550, 30 }; //Vector for the return button
    RETURN_BUTTON = { (ReturnPosi.x - Return.width / 2) + 5,(ReturnPosi.y - Return.height / 2) + 5, float(Return.width - 5) , float(Return.height) };

    bool isMouseOnReturn = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, RETURN_BUTTON);
    DrawTextureV(Return, { ReturnPosi.x - Return.width / 2 ,ReturnPosi.y - Return.height / 2 }, isMouseOnReturn ? LIGHTGRAY : WHITE);
    if (isMouseOnReturn) DrawText("Go Back To Main Menu", 350, 10, 15, WHITE);

}
void RunGameplay() {

    //Draw the board
    DrawTexturePro(board, { 0, 0, static_cast<float>(board.width), static_cast<float>(board.height) }, destRect, { 0, 0 }, 0, WHITE);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) GameFunctions::HandleMouseClick();

    GameFunctions::DrawBeadsOnBoard();
    GameFunctions::DrawTurns();

    CheckWinner();
    HandleReturnButton();
    GameFunctions::SaveGame();
    HandleSafeReturn();
}

//state RESUME
void ResumeGame() {

    BackPosi = { 300, 540 };
    BACK_BUTTON = { (BackPosi.x - Back.width / 2) + 5,(BackPosi.y - Back.height / 2) + 5,  float(Back.width) , float(Back.height) };

    StopSound(mainMenuMusic);

    GameFunctions::ReadGameDataFromFile();
    PlaySound(gameMusic);

    state = GAMEPLAY;
}

//state RULES
void DisplayRulesPage() {
    bool MouseOnBack = CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, BACK_BUTTON);

    DrawTexturePro(rules, { 0, 0, static_cast<float>(rules.width), static_cast<float>(rules.height) }, destRect, { 0, 0 }, 0, WHITE);
    DrawTextureV(Back, { BackPosi.x - Back.width / 2 ,BackPosi.y - Back.height / 2 }, MouseOnBack ? GRAY : WHITE);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

        int mouseX = GetMouseX();   int mouseY = GetMouseY();

        if (mouseX >= BackPosi.x - 100 && mouseX <= BackPosi.x + 100 && mouseY >= BackPosi.y - 45 && mouseY <= BackPosi.y + 45) {
            state = MAIN_MENU;
            PlaySound(buttonHover);
        }
    }
}