#include "raylib.h"
#include "StopScreen.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "game.h"
#include "Game Over.h"
#include "PreScreen.h"

Game::PreScreen::PreScreen() {
    // Your screen initialization code here...

    background = LoadTexture("assets/graphics/background.png");
    story = LoadTexture("assets/graphics/story.png");

}

Game::PreScreen::~PreScreen() {
    // Your screen cleanup code here...
}


void Game::PreScreen::ProcessInput() {
    // Your process input code here...

    if (IsKeyPressed(KEY_M)) currentScreen = Game::GameScreen::getInstance();



}

void Game::PreScreen::Update() {
    // Your update game code here...
}

void Game::PreScreen::Draw() {
    // Your drawing code here...
    ClearBackground(RAYWHITE);

    DrawTexture(background, 0, 0, WHITE);

    DrawTexture(story, 0, 0, WHITE);



  //  DrawText("SpaceGame", 25, 200, 100, YELLOW);
  
    DrawText("Press M to continue", 70, 880, 45, LIGHTGRAY);
}
