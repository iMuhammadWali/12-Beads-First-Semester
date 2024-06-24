//1 == Blue bead, 3 == Selected Blue outlined, 5 == Blue can move to that place
//2 == White bead, 4 == Selected White outlined, 6 == White can move at that place
//7 to 14 == A bead can be killed at that place and yellow bead appears there

#include <iostream>
#include <fstream>;
#include "raylib.h"
#include "Assets.h"

using namespace std;

namespace GameFunctions {

    bool IsTurnWhite = false;
    const int BoardDimension = 5;
    Vector2 BeadsPositions[BoardDimension][BoardDimension] = {

        {{65.0f, 82.0f}, {182.0f, 82.0f}, {299.0f, 82.0f}, {416.0f, 82.0f}, {533.0f, 82.0f}},
        {{65.0f, 192.0f}, {182.0f, 192.0f}, {299.0f, 192.0f}, {416.0f, 192.0f}, {533.0f, 192.0f}},
        {{65.0f, 302.0f}, {182.0f, 302.0f}, {299.0f, 302.0f}, {416.0f, 302.0f}, {533.0f, 302.0f}},
        {{65.0f, 412.0f}, {182.0f, 412.0f}, {299.0f, 412.0f}, {416.0f, 412.0f}, {533.0f, 412.0f}},
        {{65.0f, 522.0f}, {182.0f, 522.0f}, {299.0f, 522.0f}, {416.0f, 522.0f}, {533.0f, 522.0f}}
    };
    int Beads[BoardDimension][BoardDimension] = { {1,1,1,1,1},{1,1,1,1,1},{1,1,0,2,2},{2,2,2,2,2} ,{2,2,2,2,2} };

    int SelectedRow = 10;       int SelectedColumn = 10;

    //------------------------------------------{ Function Prototypes }----------------------------------------------------------//

    void ReadGameAssetsFromFile() {
        //Music
        mainMenuMusic = LoadSound("./assets/mainMenuMusic.mp3");
        gameMusic = LoadSound("./assets/gameMusic.mp3");

        //Hover Sound
        buttonHover = LoadSound("./assets/buttonHover.mp3");

        weHaveAWinner = LoadSound("./assets/Winning.mp3");

        //Beads Sound
        BeadKill = LoadSound("./assets/beadkillsound.mp3");
        BeadMove = LoadSound("./assets/beadmovesound.mp3");

        //elements
        board = LoadTexture("./assets/board.png");
        mainMenu = LoadTexture("./assets/mainMenuPage.png");
        rules = LoadTexture("./assets/RulesPage.png");
        whiteWin = LoadTexture("./assets/whiteWinner.png");
        blueWin = LoadTexture("./assets/blueWinner.png");
        blueBead = LoadTexture("./assets/blueBead.png");
        whiteBead = LoadTexture("./assets/whiteBead.png");
        moveableWhite = LoadTexture("./assets/moveableWhite.png");
        moveableBlue = LoadTexture("./assets/moveableBlue.png");
        target = LoadTexture("./assets/target.png");

        // Buttons
        Return = LoadTexture("./assets/return.png");
        Quit = LoadTexture("./assets/Quit.png");
        Play = LoadTexture("./assets/Play.png");
        Rules = LoadTexture("./assets/Rules.png");
        Back = LoadTexture("./assets/Back.png");
        Resume = LoadTexture("./assets/Resume.png");

        // Textures For Showing Turn
        WTurn = LoadTexture("./assets/WhiteTurn.png");
        BTurn = LoadTexture("./assets/BluesTurn.png");

    }
    void DrawBeadsOnBoard() {
        const float beadRadius = 23.0f;

        for (int i = 0; i < BoardDimension; i++) {
            for (int j = 0; j < BoardDimension; j++) {
                if (Beads[i][j] == 1)
                    DrawTextureV(blueBead, { BeadsPositions[i][j].x - blueBead.width / 2 ,BeadsPositions[i][j].y - blueBead.height / 2 }, WHITE);

                else if (Beads[i][j] == 2)
                    DrawTextureV(whiteBead, { BeadsPositions[i][j].x - whiteBead.width / 2 ,BeadsPositions[i][j].y - whiteBead.height / 2 }, WHITE);

                else if (Beads[i][j] == 3) {
                    DrawCircleV(BeadsPositions[i][j], beadRadius, WHITE);
                    DrawTextureV(blueBead, { BeadsPositions[i][j].x - blueBead.width / 2 ,BeadsPositions[i][j].y - blueBead.height / 2 }, WHITE);
                }
                else if (Beads[i][j] == 4) {
                    DrawCircleV(BeadsPositions[i][j], beadRadius, WHITE);
                    DrawTextureV(whiteBead, { BeadsPositions[i][j].x - whiteBead.width / 2 ,BeadsPositions[i][j].y - whiteBead.height / 2 }, WHITE);
                }
                else if (Beads[i][j] == 5)
                    DrawTextureV(moveableBlue, { BeadsPositions[i][j].x - whiteBead.width / 2 ,BeadsPositions[i][j].y - whiteBead.height / 2 }, WHITE);

                else if (Beads[i][j] == 6)
                    DrawTextureV(moveableWhite, { BeadsPositions[i][j].x - whiteBead.width / 2 ,BeadsPositions[i][j].y - whiteBead.height / 2 }, WHITE);

                else if (Beads[i][j] >= 7 && Beads[i][j] <= 14)
                    DrawTextureV(target, { BeadsPositions[i][j].x - whiteBead.width / 2 ,BeadsPositions[i][j].y - whiteBead.height / 2 }, WHITE);
            }
        }
    }
    bool DisplayKillingOptions(int toKill) {
        bool canKill = false;

        if (SelectedRow > 1 && Beads[SelectedRow - 2][SelectedColumn] == 0 && Beads[SelectedRow - 1][SelectedColumn] == toKill) {
            Beads[SelectedRow - 2][SelectedColumn] = 7;
            canKill = true;
        }
        if (SelectedRow < 3 && Beads[SelectedRow + 2][SelectedColumn] == 0 && Beads[SelectedRow + 1][SelectedColumn] == toKill) {
            Beads[SelectedRow + 2][SelectedColumn] = 8;
            canKill = true;
        }
        if (SelectedColumn > 1 && Beads[SelectedRow][SelectedColumn - 2] == 0 && Beads[SelectedRow][SelectedColumn - 1] == toKill) {
            Beads[SelectedRow][SelectedColumn - 2] = 9;
            canKill = true;
        }
        if (SelectedColumn < 3 && Beads[SelectedRow][SelectedColumn + 2] == 0 && Beads[SelectedRow][SelectedColumn + 1] == toKill) {
            Beads[SelectedRow][SelectedColumn + 2] = 10;
            canKill = true;
        }
        if ((SelectedRow + SelectedColumn) % 2 == 0) {
            if (SelectedRow > 1 && SelectedColumn > 1 && Beads[SelectedRow - 2][SelectedColumn - 2] == 0 && Beads[SelectedRow - 1][SelectedColumn - 1] == toKill) {
                Beads[SelectedRow - 2][SelectedColumn - 2] = 11;
                canKill = true;
            }
            if (SelectedRow > 1 && SelectedColumn < 3 && Beads[SelectedRow - 2][SelectedColumn + 2] == 0 && Beads[SelectedRow - 1][SelectedColumn + 1] == toKill) {
                Beads[SelectedRow - 2][SelectedColumn + 2] = 12;
                canKill = true;
            }
            if (SelectedRow < 3 && SelectedColumn > 1 && Beads[SelectedRow + 2][SelectedColumn - 2] == 0 && Beads[SelectedRow + 1][SelectedColumn - 1] == toKill) {
                Beads[SelectedRow + 2][SelectedColumn - 2] = 13;
                canKill = true;
            }
            if (SelectedRow < 3 && SelectedColumn < 3 && Beads[SelectedRow + 2][SelectedColumn + 2] == 0 && Beads[SelectedRow + 1][SelectedColumn + 1] == toKill) {
                Beads[SelectedRow + 2][SelectedColumn + 2] = 14;
                canKill = true;
            }
        }
        return canKill;
    }
    void DisplayMovingOptions(int toDisplay) {

        if (SelectedRow > 0 && Beads[SelectedRow - 1][SelectedColumn] == 0) Beads[SelectedRow - 1][SelectedColumn] = toDisplay;
        if (SelectedRow < 4 && Beads[SelectedRow + 1][SelectedColumn] == 0) Beads[SelectedRow + 1][SelectedColumn] = toDisplay;
        if (SelectedColumn > 0 && Beads[SelectedRow][SelectedColumn - 1] == 0) Beads[SelectedRow][SelectedColumn - 1] = toDisplay;
        if (SelectedColumn < 4 && Beads[SelectedRow][SelectedColumn + 1] == 0) Beads[SelectedRow][SelectedColumn + 1] = toDisplay;

        if (((SelectedRow + SelectedColumn) % 2) == 0) {

            if (SelectedRow < 4 && SelectedColumn < 4 && Beads[SelectedRow + 1][SelectedColumn + 1] == 0) Beads[SelectedRow + 1][SelectedColumn + 1] = toDisplay;
            if (SelectedRow > 0 && SelectedColumn > 0 && Beads[SelectedRow - 1][SelectedColumn - 1] == 0) Beads[SelectedRow - 1][SelectedColumn - 1] = toDisplay;
            if (SelectedRow < 4 && SelectedColumn > 0 && Beads[SelectedRow + 1][SelectedColumn - 1] == 0) Beads[SelectedRow + 1][SelectedColumn - 1] = toDisplay;
            if (SelectedRow > 0 && SelectedColumn < 4 && Beads[SelectedRow - 1][SelectedColumn + 1] == 0) Beads[SelectedRow - 1][SelectedColumn + 1] = toDisplay;
        }
    }
    void DisplayAllOptions() {
        //Blue is Selected  
        if (Beads[SelectedRow][SelectedColumn] == 3) {
            DisplayMovingOptions(5);
            DisplayKillingOptions(2);
        }
        //White is Selected
        else if (Beads[SelectedRow][SelectedColumn] == 4) {
            DisplayMovingOptions(6);
            DisplayKillingOptions(1);
        }
    }
    void RemoveAllMovingOptions(int current) {

        for (int k = 0; k < BoardDimension; k++) {
            for (int l = 0; l < BoardDimension; l++) {
                if (Beads[k][l] == current || (Beads[k][l] >= 7 && Beads[k][l] <= 14))
                    Beads[k][l] = 0;
            }
        }
    }
    void UnselectBead() {

        for (int i = 0; i < BoardDimension; i++) {
            for (int j = 0; j < BoardDimension; j++) {
                if (Beads[i][j] == 3)
                    Beads[i][j] = 1;
                if (Beads[i][j] == 4)
                    Beads[i][j] = 2;

                if (Beads[i][j] >= 5 && Beads[i][j] <= 14)
                    Beads[i][j] = 0;
            }
        }
    }
    void SelectBead(int i, int j) {
        UnselectBead();

        if (Beads[i][j] == 1 && !IsTurnWhite)     Beads[i][j] = 3;
        else if (Beads[i][j] == 2 && IsTurnWhite) Beads[i][j] = 4;

        SelectedRow = i;
        SelectedColumn = j;
    }
    void ExecuteSimpleMove(int i, int j) {

        PlaySound(BeadMove);

        SelectedRow = 10;   SelectedColumn = 10;

        if (IsTurnWhite) {
            RemoveAllMovingOptions(6);
            Beads[i][j] = 2;
        }
        else if (!IsTurnWhite) {
            Beads[i][j] = 1;
            RemoveAllMovingOptions(5);
        }
        IsTurnWhite = !IsTurnWhite;
    }
    void ExecuteKillingMove(int i, int j) {

        if (Beads[i][j] == 7 && SelectedColumn - 1 >= 0)
            Beads[SelectedRow - 1][SelectedColumn] = 0;

        else if (Beads[i][j] == 8)
            Beads[SelectedRow + 1][SelectedColumn] = 0;

        else if (Beads[i][j] == 9 && SelectedColumn - 1 >= 0)
            Beads[SelectedRow][SelectedColumn - 1] = 0;

        else if (Beads[i][j] == 10)
            Beads[SelectedRow][SelectedColumn + 1] = 0;

        else if (Beads[i][j] == 11 && SelectedRow - 1 >= 0 && SelectedColumn - 1 >= 0)
            Beads[SelectedRow - 1][SelectedColumn - 1] = 0;

        else if (Beads[i][j] == 12 && SelectedRow - 1 >= 0 && (SelectedColumn + 1) < BoardDimension)
            Beads[SelectedRow - 1][SelectedColumn + 1] = 0;

        else if (Beads[i][j] == 13 && SelectedRow + 1 < BoardDimension && SelectedColumn - 1 >= 0)
            Beads[SelectedRow + 1][SelectedColumn - 1] = 0;

        else if (Beads[i][j] == 14)
            Beads[SelectedRow + 1][SelectedColumn + 1] = 0;

        PlaySound(BeadKill);
        SelectedRow = i;
        SelectedColumn = j;

        if (IsTurnWhite) {
            RemoveAllMovingOptions(6);

            if (!DisplayKillingOptions(1)) {

                SelectedRow = 10;
                SelectedColumn = 10;
                IsTurnWhite = false;
            }
            Beads[i][j] = 2;
        }
        else if (!IsTurnWhite) {
            RemoveAllMovingOptions(5);

            if (!DisplayKillingOptions(2)) {

                SelectedRow = 10;
                SelectedColumn = 10;
                IsTurnWhite = true;
            }
            Beads[i][j] = 1;
        }
    }
    void HandleBeadMoving(int i, int j) {
        Beads[SelectedRow][SelectedColumn] = 0;

        if (Beads[i][j] == 5 || Beads[i][j] == 6) {
            ExecuteSimpleMove(i, j);
        }
        else if (Beads[i][j] >= 7 && Beads[i][j] <= 14) {
            ExecuteKillingMove(i, j);
        }
    }
    void HandleMouseClick() {
        for (int i = 0; i < BoardDimension; i++) {
            for (int j = 0; j < BoardDimension; j++) {
                if (CheckCollisionPointCircle({ (float)GetMouseX(), (float)GetMouseY() }, BeadsPositions[i][j], 30)) {

                    if (Beads[i][j] <= 4) { //It means that the area of the board clicked is either a blue bead or a white one

                        SelectBead(i, j);
                        DisplayAllOptions();
                    }
                    else {
                        HandleBeadMoving(i, j);
                    }
                }
            }
        }
    }
    bool AreBeadsAbsent(int bead, int selectedBead) {
        int count = 0;
        for (int i = 0; i < BoardDimension; i++) {
            for (int j = 0; j < BoardDimension; j++) {
                if (Beads[i][j] != bead && Beads[i][j] != selectedBead)
                    count++;
            }
        }
        if (count == (BoardDimension * BoardDimension)) return true;
        return false;
    }
    int CheckGameOutcome() {

        if (!IsTurnWhite) {
            if (AreBeadsAbsent(1, 3)) {
                return 10; // White wins
            }
        }
        else if (IsTurnWhite) {
            if (AreBeadsAbsent(2, 4)) {
                return 20; // Blue wins
            }
        }
        return 0;
    }
    void RandomizeTurn() {
        srand(time(0));
        IsTurnWhite = rand() % 2;

    }
    void ResetBeadPositions() {
        Beads[0][0] = 1;
        Beads[0][1] = 1;
        Beads[0][2] = 1;
        Beads[0][3] = 1;
        Beads[0][4] = 1;
        Beads[1][0] = 1;
        Beads[1][1] = 1;
        Beads[1][2] = 1;
        Beads[1][3] = 1;
        Beads[1][4] = 1;
        Beads[2][0] = 1;
        Beads[2][1] = 1;

        Beads[2][2] = 0;

        Beads[2][3] = 2;
        Beads[2][4] = 2;
        Beads[3][0] = 2;
        Beads[3][1] = 2;
        Beads[3][2] = 2;
        Beads[3][3] = 2;
        Beads[3][4] = 2;
        Beads[4][0] = 2;
        Beads[4][1] = 2;
        Beads[4][2] = 2;
        Beads[4][3] = 2;
        Beads[4][4] = 2;
    }
    void DrawTurns() {
        if (IsTurnWhite)
            DrawTextureV(WTurn, { 200, 540 }, WHITE);
        else
            DrawTextureV(BTurn, { 200, 18 }, WHITE);
    }
    void SaveGame() {
        ofstream save;
        save.open("GameData.txt");
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                save << Beads[i][j] << ",";
            }
        }
        save << IsTurnWhite;
        save.close();
    }
    void ReadGameDataFromFile() {
        ifstream GetValues;
        GetValues.open("GameData.txt");
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                GetValues >> Beads[i][j];
                GetValues.ignore(1, ',');
            }
        }
        GetValues >> IsTurnWhite;
        UnselectBead();
    }
    void UnloadGameAssets() {
        // Unload Sounds
        UnloadSound(mainMenuMusic);
        UnloadSound(gameMusic);
        UnloadSound(buttonHover);
        UnloadSound(weHaveAWinner);
        UnloadSound(BeadKill);
        UnloadSound(BeadMove);

        // Unload Textures
        UnloadTexture(board);
        UnloadTexture(mainMenu);
        UnloadTexture(rules);
        UnloadTexture(whiteWin);
        UnloadTexture(blueWin);
        UnloadTexture(blueBead);
        UnloadTexture(whiteBead);
        UnloadTexture(moveableWhite);
        UnloadTexture(moveableBlue);
        UnloadTexture(target);
        UnloadTexture(Return);
        UnloadTexture(Quit);
        UnloadTexture(Play);
        UnloadTexture(Rules);
        UnloadTexture(Back);
        UnloadTexture(Resume);
        UnloadTexture(WTurn);
        UnloadTexture(BTurn);
    }
}