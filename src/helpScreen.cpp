#include "raylib.h"

#include "MenuScreen.h"
#include "GameScreen.h"
#include "game.h"
#include "helpScreen.h"

Game::helpScreen::helpScreen() {
    // Your screen initialization code here...

    background = LoadTexture("assets/graphics/background.png");
    help = LoadTexture("assets/graphics/help.png");

}

Game::helpScreen::~helpScreen() {
    // Your screen cleanup code here...
}


void Game::helpScreen::ProcessInput() {
    // Your process input code here...

    if (IsKeyPressed(KEY_I)) currentScreen = Game::MenuScreen::getInstance();



}

void Game::helpScreen::Update() {
    // Your update game code here...
}

void Game::helpScreen::Draw() {
    // Your drawing code here...
    ClearBackground(RAYWHITE);

    DrawTexture(background, 0, 0, WHITE);

    DrawTexture(help, 0, 0, WHITE);



    //  DrawText("SpaceGame", 25, 200, 100, YELLOW);

    DrawText("Press [I] to go back", 70, 880, 45, LIGHTGRAY);
}
