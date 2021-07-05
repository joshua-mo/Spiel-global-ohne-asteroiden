#include "raylib.h"

#include "MenuScreen.h"
#include "GameScreen.h"
#include "Game Over.h"
#include "game.h"

extern int highscore;

Game::GameOver::GameOver () {
    // Your screen initialization code here...

    background = LoadTexture("assets/graphics/background.png");
    welt = LoadTexture("assets/graphics/welt.png");


}

Game::GameOver::~GameOver() {
    // Your screen cleanup code here...
}


void Game::GameOver::ProcessInput() {
    // Your process input code here...
    
    if (IsKeyPressed(KEY_ENTER))
    {
        currentScreen = Game::MenuScreen::getInstance();
        highscore = 0;
    }
}

void Game::GameOver::Update() {
    // Your update game code here...


    
}

void Game::GameOver::Draw() {
    // Your drawing code here...
    ClearBackground(RAYWHITE);
   
    DrawTexture(background, 0, 0, WHITE);
    DrawText("GAME OVER", 225, 200, 90, YELLOW);
    DrawText(TextFormat("Score: %02i", highscore), 390, 350, 50, WHITE);
    DrawText("Menu - PRESS ENTER", 300, 570, 35, LIGHTGRAY);
}
