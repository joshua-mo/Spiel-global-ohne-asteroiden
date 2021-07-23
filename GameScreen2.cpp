#include "raylib.h"

#include "GameScreen2.h"
#include "MenuScreen.h"
#include "game.h"
#include "Game Over.h"
#include "StopScreen.h"


extern int highscore;

extern Player player;

extern int activeEnemies;

extern Enemy enemy[NUM_MAX_ENEMIES];

extern int activeEnemies2;

extern Enemy enemy2[NUM_MAX_ENEMIES];

Game::GameScreen2::GameScreen2() {
    // Your screen initialization code here...
    Vector2 vec = { 100.0f, 100.0f };
    this->sprites.push_back(
        std::make_unique<Game::Sprite>(LoadTexture("assets/graphics/background.png"),
            vec,
            true)
    );

    //Texuren Umgebung
    background = LoadTexture("assets/graphics/background2.png");
    Spaces = LoadTexture("assets/graphics/Spaces.png");
    Lives = LoadTexture("assets/graphics/Lives.png");









    //Planet initialisieren

    planet.position.x = 800 / 2;
    planet.position.y = 200 + 1175;
    planet.radius = 350;



    //Spieler initialisieren
    // Load player ship texture
    playerTexture = LoadTexture("assets/graphics/player2.png");

    //// Spieler (Viereck) initialisieren
    //player.rect.x = 800 / 2.0f;

    //player.rect.width = 35;
    //player.rect.height = 35;
    //player.speed.x = 7;
    //player.speed.y = 5;
    //player.color = WHITE;


    // Bullets initialisieren

    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        bullet[i].rect.x = player.rect.x + 29;                  //Bullet zentrieren
        bullet[i].rect.y = player.rect.y + player.rect.height / 4;
        bullet[i].rect.width = 5;
        bullet[i].rect.height = 10;
        bullet[i].speed.x = 0;
        bullet[i].speed.y = -10;
        bullet[i].active = false;
        bullet[i].color = MAROON;
    }




    // Gegner initialisieren

    // Load alien ship texture
    alienTexture = LoadTexture("assets/graphics/alien2.png");
    alienTexture2 = LoadTexture("assets/graphics/Test2.png");

    //Anzahl aktive Gegner 





    ////Schwerer Gegner
    //for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    //{
    //    enemy2[i].rect.width = 128;
    //    enemy2[i].rect.height = 120;
    //    enemy2[i].rect.x = GetRandomValue(200, 672);
    //    enemy2[i].rect.y = GetRandomValue(-1000, -20);
    //    enemy2[i].speed.x = 5;
    //    enemy2[i].speed.y = 2; //Geschwindigkeit Gegner
    //    enemy2[i].active = true;
    //    enemy2[i].gothit = false;
    //}

}


Game::GameScreen2::~GameScreen2() {
    // Your screen cleanup code here...
    UnloadTexture(sprites[0]->texture);
    UnloadTexture(background);
    UnloadTexture(playerTexture);
    UnloadTexture(alienTexture);
    UnloadTexture(alienTexture2);
    UnloadTexture(Lives);
    UnloadTexture(Spaces);
}


void Game::GameScreen2::ProcessInput() {
    // Your process input code here...
    if (IsKeyPressed(KEY_M)) currentScreen = Game::StopScreen::getInstance();

    //SWAP
    if (IsKeyPressed(KEY_TAB)) currentScreen = Game::GameScreen::getInstance();

    // Spieler bewegen (links-rechts)
    if (IsKeyDown(KEY_RIGHT))
        player.pos.w += player.speed.w;
    if (IsKeyDown(KEY_LEFT))
        player.pos.w -= player.speed.w;




}

void Game::GameScreen2::Update() {
    // Your update game code here...

   //# Spieler

      //Spieler an W�nden einschr�nken
        if ((player.rect.x + 54) >= 800) player.rect.x = 800 - 54;          
        else if (player.rect.x <= -10) player.rect.x = -10;
        if ((player.rect.x) <= 200) player.rect.x = 200 + 1;         
   

    //Bullets
    if (IsKeyPressed(KEY_SPACE)) {




        for (int i = 0; i < NUM_SHOOTS; i++)
        {
            if (!bullet[i].active)
            {
                // Movement
                bullet[i].rect.y += bullet[i].speed.y;

                bullet[i].rect.x = player.rect.x + 29;                 //Bullet zentrieren
                bullet[i].rect.y = player.rect.y + player.rect.height / 4;
                bullet[i].active = true;

                break;


            }
        }
    }

    //# Gegner 

    // Shoot logic
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        if (bullet[i].active)
        {
            // Movement
            bullet[i].rect.y += bullet[i].speed.y;

            // Kollision mit enemy
            for (int j = 0; j < activeEnemies || j < activeEnemies2; j++)
            {
                if (enemy[j].active || enemy2[j].active)
                {
                    if (CheckCollisionRecs(bullet[i].rect, enemy[j].rect))
                    {
                        bullet[i].active = false;
                        enemy[j].pos.x = GetRandomValue(200, 736);      //Spawnbereich neuer Gegner x
                        enemy[j].pos.y = GetRandomValue(0, -400);     //Spawnbereich neuer Gegner y
                        highscore++;




                    }

                    if (enemy2[j].gothit == true)
                    {

                        if (CheckCollisionRecs(bullet[i].rect, enemy2[j].rect))
                        {
                            bullet[i].active = false;
                            enemy2[j].pos.x = GetRandomValue(200, 672);      //Spawnbereich neuer Gegner x
                            enemy2[j].pos.y = GetRandomValue(-400, -130);     //Spawnbereich neuer Gegner y
                            highscore++;
                            enemy2[j].gothit = false;
                        }
                    }
                    if (CheckCollisionRecs(bullet[i].rect, enemy2[j].rect))
                    {
                        enemy2[j].gothit = true;
                        bullet[i].active = false;
                    }
                }

                if (bullet[i].rect.y <= 0) //Bullet �ber Screen hinaus
                {
                    bullet[i].active = false;
                }
            }
        }
    }





    // Spieler Kollision  mit Enemy -> verliert 1 Leben
    for (int j = 0; j < activeEnemies || j < activeEnemies2; j++)
    {
        if (enemy[j].active | enemy2[j].active)
        {
            if (CheckCollisionRecs(player.rect, enemy[j].rect))
            {
                player.lives--;
                enemy[j].pos.x = GetRandomValue(200, 736);      //Spawnbereich neuer Gegner x
                enemy[j].pos.y = GetRandomValue(0, -400);     //Spawnbereich neuer Gegner y
            }
            if (CheckCollisionRecs(player.rect, enemy2[j].rect))
            {
                player.lives--;
                enemy2[j].pos.x = GetRandomValue(200, 736);      //Spawnbereich neuer Gegner x
                enemy2[j].pos.y = GetRandomValue(0, -400);     //Spawnbereich neuer Gegner y
            }
        }
    }











    // Enemy Verhalten(Spawnverhalten)
    for (int i = 0; i < activeEnemies || i < activeEnemies2; i++)
    {
        if (enemy[i].active)
        {
            enemy[i].pos.y += enemy[i].speed.y;

            if (CheckCollisionCircleRec(planet.position, 350, enemy[i].rect))    //         //Kollision Planet mit Enemy
            {
                enemy[i].pos.x = GetRandomValue(1020, 2000);
                enemy[i].pos.y = GetRandomValue(200, 736);
                planet.landed--;

            }
        }

        if (enemy2[i].active)
        {
            enemy2[i].pos.y += enemy2[i].speed.y;

            if (CheckCollisionCircleRec(planet.position, 350, enemy2[i].rect))    //         //Kollision Planet mit Enemy2
            {
                enemy2[i].pos.x = GetRandomValue(1020, 2000);
                enemy2[i].pos.y = GetRandomValue(200, 672);
                planet.landed--;

            }
        }


    }








}



void Game::GameScreen2::Draw() {
    // Your drawing code here...
    ClearBackground(BLACK);
    //Hitbox Planet
    DrawCircleV(planet.position, planet.radius, RED);
    //Hintergrund
    DrawTexture(background, 0, 0, WHITE);


    //BUllet zeichnen
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        if (bullet[i].active)
            DrawRectangleRec(bullet[i].rect, bullet[i].color);
    }

    //Player zeichnen
    DrawTexture(playerTexture, player.pos.w, player.pos.z, WHITE);

    //Gegner zeichnen
    for (int i = 0; i < activeEnemies; i++)
    {
        if (enemy[i].active)
            DrawTexture(alienTexture, enemy[i].pos.x, enemy[i].pos.y, WHITE);
    }

    //Gegner2 zeichnen
    for (int i = 0; i < activeEnemies2; i++)
    {
        if (enemy2[i].active)
            DrawTexture(alienTexture2, enemy2[i].pos.x, enemy2[i].pos.y, WHITE);
    }



    //Anzeigen
    DrawText(" M - pause", 220, 20, 20, LIGHTGRAY);
    DrawText(" TAB - Switch Cam", 220, 60, 20, LIGHTGRAY);
    // DrawText("Lives", 415, 180, 30, RED);
     //DrawText("Space", 415, 220, 30, DARKBLUE);
    // DrawText(TextFormat("Lives: %02i", player.lives), 425, 180, 30, RED);
    // DrawText(TextFormat("Space: %02i", planet.landed), 425, 220, 25, BLUE);
    DrawText(TextFormat("Score: %02i", highscore), 225, 140, 35, LIGHTGRAY);
    //Live Anzeige
    if (player.lives == 3) {
        DrawTexture(Lives, 500, 215, WHITE);
        DrawTexture(Lives, 530, 215, WHITE);
        DrawTexture(Lives, 560, 215, WHITE);
    }
    if (player.lives == 2) {
        DrawTexture(Lives, 530, 215, WHITE);
        DrawTexture(Lives, 560, 215, WHITE);
    }
    if (player.lives == 1) {
        DrawTexture(Lives, 560, 215, WHITE);
    }

    //Space Anzeige 
    if (planet.landed == 5) {
        DrawTexture(Spaces, 420, 180, WHITE);
        DrawTexture(Spaces, 455, 180, WHITE);
        DrawTexture(Spaces, 490, 180, WHITE);
        DrawTexture(Spaces, 525, 180, WHITE);
        DrawTexture(Spaces, 560, 180, WHITE);
    }
    if (planet.landed == 4) {
        DrawTexture(Spaces, 455, 180, WHITE);
        DrawTexture(Spaces, 490, 180, WHITE);
        DrawTexture(Spaces, 525, 180, WHITE);
        DrawTexture(Spaces, 560, 180, WHITE);
    }
    if (planet.landed == 3) {
        DrawTexture(Spaces, 490, 180, WHITE);
        DrawTexture(Spaces, 525, 180, WHITE);
        DrawTexture(Spaces, 560, 180, WHITE);
    }
    if (planet.landed == 2) {
        DrawTexture(Spaces, 525, 180, WHITE);
        DrawTexture(Spaces, 560, 180, WHITE);
    }
    if (planet.landed == 1) {
        DrawTexture(Spaces, 560, 180, WHITE);
    }











}

