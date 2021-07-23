#include "raylib.h"
#include "StopScreen.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "game.h"
#include "Game Over.h"

Game::StopScreen::StopScreen() {
    // Your screen initialization code here...

    background = LoadTexture("assets/graphics/background.png");

}

Game::StopScreen::~StopScreen() {
    // Your screen cleanup code here...
}


void Game::StopScreen::ProcessInput() {
    // Your process input code here...
   
    if (IsKeyPressed(KEY_M)) currentScreen = Game::GameScreen::getInstance();



}

void Game::StopScreen::Update() {
    // Your update game code here...
}

void Game::StopScreen::Draw() {
    // Your drawing code here...
    ClearBackground(RAYWHITE);

    DrawTexture(background, 0, 0, WHITE);





    DrawText("SpaceGame", 25, 200, 100, YELLOW);
    DrawText("Game paused", 110, 400, 60, LIGHTGRAY);
    DrawText("Press M to continue", 70, 550, 45, LIGHTGRAY);
}
