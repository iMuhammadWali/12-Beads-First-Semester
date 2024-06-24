#pragma once
namespace GameFunctions {
	void DrawBeadsOnBoard();
	void HandleMouseClick();
	int CheckGameOutcome();
	void RandomizeTurn();
	void ResetBeadPositions();
	void DrawTurns();
	void SaveGame();
	void ReadGameDataFromFile();
	void ReadGameAssetsFromFile();
	void UnloadGameAssets();
}