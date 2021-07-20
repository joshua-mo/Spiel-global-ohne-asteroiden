#include "raylib.h"

#include "MenuScreen.h"
#include "GameScreen.h"
#include "GameScreen2.h"
#include "game.h"
#include "Game Over.h"
#include "PreScreen.h"
#include "helpScreen.h"

Game::MenuScreen::MenuScreen() {
    // Your screen initialization code here...

    //TExturen
    background = LoadTexture("assets/graphics/background.png");
    welt = LoadTexture("assets/graphics/welt.png");
    start = LoadTexture("assets/graphics/button/start.png");
    startpink = LoadTexture("assets/graphics/button/startpink.png");
    quit = LoadTexture("assets/graphics/button/quit.png");
    quitpink = LoadTexture("assets/graphics/button/quitpink.png");


    //Einfacher Gegner
    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {
        enemy[i].rect.width = 64;
        enemy[i].rect.height = 50;
        enemy[i].rect.x = GetRandomValue(0, 600 - 64);
        enemy[i].rect.y = GetRandomValue(-1000, -20);
        enemy[i].speed.x = 5;
        enemy[i].speed.y = 5; //Geschwindigkeit Gegner
        enemy[i].active = true;
    }
}

Game::MenuScreen::~MenuScreen() {
    // Your screen cleanup code here...
}


void Game::MenuScreen::ProcessInput() {
    // Your process input code here...

    Vector2 mouse = GetMousePosition();

    //Spiel wird gestartet
    if (IsMouseButtonPressed(0) && (mouse.x > 389) && (mouse.y > 460) && (mouse.x < 610) && (mouse.y < 530)) {
        currentScreen = Game::GameScreen::getInstance();

    }

 
    //Spiel wird beendet
    if (IsMouseButtonPressed(0) && (mouse.x > 389) && (mouse.y > 595) && (mouse.x < 610) && (mouse.y < 670)) {
        exit(0);
    }

    if (IsKeyPressed(KEY_I)) currentScreen = Game::helpScreen::getInstance();

}

void Game::MenuScreen::Update() {
    // Your update game code here...
}

void Game::MenuScreen::Draw() {
    // Your drawing code here...
    ClearBackground(RAYWHITE);

    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(start, 200, 0, WHITE);
    DrawTexture(quit, 200, 0, WHITE);


    DrawText("Exterminatus", 222, 200, 85, YELLOW);
  //  DrawText("New Game/Continue", 50, 380, 50, WHITE);
  //  DrawText("Highscore", 180, 480, 50, WHITE);
   // DrawText("Quit Game", 190, 580, 50, WHITE);

    Vector2 mouse = GetMousePosition();

    if ((mouse.x > 389) && (mouse.y > 460) && (mouse.x < 610) && (mouse.y < 530)) {
      //  DrawText("New Game/Continue", 50, 380, 50, MAGENTA);
        DrawTexture(startpink, 200, 0, WHITE);
    }


    else if ((mouse.x > 389) && (mouse.y > 595) && (mouse.x < 610) && (mouse.y < 670)) //Bereich  links nach rechts, Bereich oben nach unten
    {  
       // DrawText("Quit Game", 190, 580, 50, MAGENTA);
        DrawTexture(quitpink, 200, 0, WHITE);
    }

    DrawText("Press [I] for Info", 600, 420, 20, LIGHTGRAY);
}




