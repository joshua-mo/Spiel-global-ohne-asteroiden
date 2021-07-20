#include "raylib.h"

#include "GameScreen.h"
#include "GameScreen2.h"
#include "MenuScreen.h"
#include "game.h"
#include "Game Over.h"
#include "StopScreen.h"


extern int highscore;

Game::GameScreen::GameScreen() {
    // Your screen initialization code here...
    Vector2 vec = {100.0f, 100.0f};
    this->sprites.push_back(
        std::make_unique<Game::Sprite>(LoadTexture("assets/graphics/background.png"),
            vec,
            true)
    );

    //Texuren Umgebung
    background = LoadTexture("assets/graphics/background.png");
    Planet1 = LoadTexture("assets/graphics/planet1.png");
    Planet2 = LoadTexture("assets/graphics/planet2.png");
    Spaces = LoadTexture("assets/graphics/Spaces.png");
    Lives = LoadTexture("assets/graphics/Lives.png");

    
        
    


    // Load Asteroid texture
    asteroidtexture = LoadTexture("assets/graphics/asteroid.png");

    //Anzahl aktive Asteroiden 

    activeAsteroids = 2;

    //Asteroid 



    for (int i = 0; i < NUM_MAX_ASTEROIDS; i++)
    {
        asteroid[i].rect.width = 50;
        asteroid[i].rect.height = 64;
        asteroid[i].rect.x = GetRandomValue(1060, 1200);      //Spawnbereich neuer Asteroid
        asteroid[i].rect.y = GetRandomValue(0, 800);
        asteroid[i].speed.x = 3;
        asteroid[i].speed.y = 1; //Geschwindigkeit Gegner
        asteroid[i].active = true;
    }



    //Planet initialisieren
  
        planet.position.x = -175;
        planet.position.y = 500;
        planet.radius = 350;
       


    //Spieler initialisieren
    // Load player ship texture
    playerTexture = LoadTexture("assets/graphics/player.png");      

    // Spieler (Viereck) initialisieren
    player.rect.x = 250;
    player.rect.y = 800 / 2.0f;
    player.rect.width = 35;
    player.rect.height = 35;
    player.speed.x = 7;
    player.speed.y = 5;
    player.color = WHITE;


    // Bullets initialisieren

    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        bullet[i].rect.x = player.rect.x + player.rect.width / 4;               
        bullet[i].rect.y = player.rect.y + 29;                                //Bullet zentrieren
        bullet[i].rect.width = 10;
        bullet[i].rect.height = 5;
        bullet[i].speed.x = +10;
        bullet[i].speed.y = 0;
        bullet[i].active = false;
        bullet[i].color = MAROON;
    }

   


 



    // Gegner initialisieren

    // Load alien ship texture
    alienTexture = LoadTexture("assets/graphics/alien.png");
    alienTexture2 = LoadTexture("assets/graphics/Test.png");

    //Anzahl aktive Gegner 
    
        activeEnemies = 1;
        activeEnemies2 = 1;
    
  
    //Einfacher Gegner
    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {
        enemy[i].rect.width = 50;
        enemy[i].rect.height = 64;
        enemy[i].rect.x = GetRandomValue(1100, 1600);      //Spawnbereich neuer Gegner x
        enemy[i].rect.y = GetRandomValue(200, 700);
        enemy[i].speed.x = 5; 
        enemy[i].speed.y = 5; //Geschwindigkeit Gegner
        enemy[i].active = true;
    }
    //Schwerer Gegner
    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {
        enemy2[i].rect.width = 120;
        enemy2[i].rect.height = 128;
        enemy2[i].rect.x = GetRandomValue(1100, 1600);
        enemy2[i].rect.y = GetRandomValue(200, 700);
        enemy2[i].speed.x = 2;
        enemy2[i].speed.y = 5; //Geschwindigkeit Gegner
        enemy2[i].active = true;
        enemy2[i].gothit = false;
    }

    //Boss initalisieren
// Load Boss ship texture
    BossMonster = LoadTexture("assets/graphics/BossSide.png");
    //Anzahl aktive Gegner 

    activeBoss = 1;

    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {
        Boss[i].rect.width = 128;
        Boss[i].rect.height = 128;
        Boss[i].rect.x = 700;
        Boss[i].rect.y = 400;
        Boss[i].speed.x = 2;
        Boss[i].speed.y = 5; //Geschwindigkeit Gegner
        Boss[i].active = true;
        Boss[i].gothit = false;
    }





  }


Game::GameScreen::~GameScreen() {
    // Your screen cleanup code here...
    UnloadTexture(sprites[0]->texture);
    UnloadTexture(background);
    UnloadTexture(playerTexture);
    UnloadTexture(alienTexture);
    UnloadTexture(alienTexture2);
    UnloadTexture(Lives);
    UnloadTexture(Spaces);
}


void Game::GameScreen::ProcessInput() {
    // Your process input code here...
    if (IsKeyPressed(KEY_M)) currentScreen = Game::StopScreen::getInstance();
    //SWAP
    if (IsKeyPressed(KEY_TAB)) currentScreen = Game::GameScreen2::getInstance();
    // Spieler bewegen (links-rechts)
    if (IsKeyDown(KEY_DOWN))
        player.rect.y += player.speed.y;
    if (IsKeyDown(KEY_UP))
        player.rect.y -= player.speed.y;

   //Boss initalisieren
    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {
        Boss[i].rect.width = 128;
        Boss[i].rect.height = 128;
        Boss[i].rect.x = 700;
        Boss[i].rect.y = 400;
        Boss[i].speed.x = 2;
        Boss[i].speed.y = 5; //Geschwindigkeit Gegner
        Boss[i].active = true;
        Boss[i].gothit = false;
    }



}

void Game::GameScreen::Update() {
    // Your update game code here...

 if ((player.rect.y + 43) >= 800) player.rect.y = 800 - 43;           //Spieler an Wänden einschränken
    else if (player.rect.y <= -10) player.rect.y = -10;
 if ((player.rect.y) <= 200) player.rect.y = 200 + 1;

 // Boss Verhalten(Spawnverhalten)
 for (int i = 0; i < activeBoss || i < activeBoss; i++)
 {
     if (Boss[i].active)
     {
         Boss[i].rect.y -= Boss[i].speed.y;
     }

 }


 // Asteroid Verhalten(Spawnverhalten)
 for (int i = 0; i < activeAsteroids; i++)
 {
     if (asteroid[i].active)
     {
         asteroid[i].rect.x -= asteroid[i].speed.x;
         asteroid[i].rect.y += asteroid[i].speed.y;



         if (CheckCollisionRecs(player.rect, asteroid[i].rect))
         {
             player.lives--;
             asteroid[i].rect.x = GetRandomValue(1060, 1200);      //Spawnbereich neuer Asteroid
             asteroid[i].rect.y = GetRandomValue(0, 800);

         }
     }
     if (asteroid[i].rect.x <= -50 || asteroid[i].rect.y >= 1050) //asteroid über Screen hinaus
     {
         asteroid[i].rect.x = GetRandomValue(1060, 1200);      //Spawnbereich neuer Asteroid
         asteroid[i].rect.y = GetRandomValue(0, 800);
     }

 }


 //Bullets
 if (IsKeyPressed(KEY_SPACE)) {

    


     for (int i = 0; i < NUM_SHOOTS; i++)
     {
         if (!bullet[i].active)
         { 
                // Movement
                 bullet[i].rect.x += bullet[i].speed.x;

                 bullet[i].rect.x = player.rect.x + player.rect.width / 4;
                 bullet[i].rect.y = player.rect.y + 29;
             bullet[i].active = true;
           
             break;

            
         }
     }
 }



 // Shoot logic
 for (int i = 0; i < NUM_SHOOTS; i++)
 {
     if (bullet[i].active)
     {
         // Movement
         bullet[i].rect.x += bullet[i].speed.x;

         // Kollision mit enemy
         for (int j = 0; j < activeEnemies || j < activeEnemies2;  j++)
         {
             if (enemy[j].active || enemy2[j].active)
             {
                 if (CheckCollisionRecs(bullet[i].rect, enemy[j].rect))
                 {
                     bullet[i].active = false;
                     enemy[j].rect.x = GetRandomValue(1100, 1600);      //Spawnbereich neuer Gegner x
                     enemy[j].rect.y = GetRandomValue(200, 736);     //Spawnbereich neuer Gegner y
                     highscore++;
                  
               

                 
                 }

                 if (enemy2[j].gothit == true)
                 {

                     if (CheckCollisionRecs(bullet[i].rect, enemy2[j].rect))
                     {
                         bullet[i].active = false;
                         enemy2[j].rect.x = GetRandomValue(1100, 1600);      //Spawnbereich neuer Gegner x
                         enemy2[j].rect.y = GetRandomValue(200, 672);     //Spawnbereich neuer Gegner y
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

                 if (bullet[i].rect.x >= 1000) //Bullet über Screen hinaus
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
                     enemy[j].rect.x = GetRandomValue(1020, 2000);      //Spawnbereich neuer Gegner x
                     enemy[j].rect.y = GetRandomValue(200, 736);     //Spawnbereich neuer Gegner y
                 }
                 if (CheckCollisionRecs(player.rect, enemy2[j].rect))
                 {
                     player.lives--;
                     enemy2[j].rect.x = GetRandomValue(1020, 2000);      //Spawnbereich neuer Gegner x
                     enemy2[j].rect.y = GetRandomValue(200, 772);     //Spawnbereich neuer Gegner y
                 }
             }
         }

    

             
         



    
  

    // Enemy Verhalten(Spawnverhalten)
    for (int i = 0; i < activeEnemies || i < activeEnemies2; i++)
    {
        if (enemy[i].active)
        {
            enemy[i].rect.x -= enemy[i].speed.x;

            if (CheckCollisionCircleRec(planet.position, 350, enemy[i].rect))    //         //Kollision Planet mit Enemy
            {
                enemy[i].rect.x = GetRandomValue(1020, 2000);
                enemy[i].rect.y = GetRandomValue(200, 736);
                planet.landed--;

            }
        }

        if (enemy2[i].active)
        {
            enemy2[i].rect.x -= enemy2[i].speed.x;

            if (CheckCollisionCircleRec(planet.position, 350, enemy2[i].rect))    //         //Kollision Planet mit Enemy2
            {
                enemy2[i].rect.x = GetRandomValue(1020, 2000);
                enemy2[i].rect.y = GetRandomValue(200, 672);
                planet.landed--;

            }
        }


    }
    if (highscore == 5) {
        activeEnemies = 1;
        activeEnemies2 = 1;
    }
    if (highscore == 15) {
        activeEnemies = 2;
        activeEnemies2 = 1;

    }
    if (highscore == 35) {
        activeEnemies = 3;
        activeEnemies2 = 1;

    }
    if (highscore == 45) {
        activeEnemies = 4;
        activeEnemies2 = 1;

    }
    if (highscore == 60) {
        activeEnemies = 6;
        activeEnemies2 = 2;

    }
    if (highscore == 90) {
        activeEnemies = 8;
        activeEnemies2 = 2;

    }


    if (player.lives == 0 || planet.landed == 0) {
        currentScreen = Game::GameOver::getInstance();


        player.lives = 3;
        planet.landed = 5;
        activeEnemies = 1;
        activeEnemies2 = 0;

        for (int i = 0; i < activeEnemies; i++)
        {
            if (enemy[i].active)
            {
                enemy2[i].rect.x = GetRandomValue(1020, 2000);
                enemy[i].rect.y = GetRandomValue(200, 700);
            }
        }
    }

   

}



void Game::GameScreen::Draw() {
    // Your drawing code here...
    ClearBackground(BLACK);
    //Hitbox Planet
    DrawCircleV(planet.position, planet.radius, RED);          
    //Hintergrund
    DrawTexture(background, 0, 0, WHITE); 

    //Planet1
    DrawTexture(Planet1, -480, 80, WHITE);

    //Planet2
    DrawTexture(Planet2, 800, 80, WHITE);

   
         
     //BUllet zeichnen
     for (int i = 0; i < NUM_SHOOTS; i++)
     {
         if (bullet[i].active)
             DrawRectangleRec(bullet[i].rect, bullet[i].color);
     }

     //Player zeichnen
     DrawTexture(playerTexture, player.rect.x, player.rect.y, WHITE);  

     //Asteroiden zeichnen
     for (int i = 0; i < activeAsteroids; i++)
     {
         if (asteroid[i].active)
             DrawTexture(asteroidtexture, asteroid[i].rect.x, asteroid[i].rect.y, WHITE);
     }


     //Gegner zeichnen
     for (int i = 0; i < activeEnemies; i++)
     {
         if (enemy[i].active)
             DrawTexture(alienTexture, enemy[i].rect.x, enemy[i].rect.y, WHITE);        
     }

     //Gegner2 zeichnen
     for (int i = 0; i < activeEnemies2; i++)
     {
         if (enemy2[i].active)
             DrawTexture(alienTexture2, enemy2[i].rect.x, enemy2[i].rect.y, WHITE);       
     }

     //Boss zeichnen
     for (int i = 0; i < activeEnemies2; i++)
     {
         if (Boss[i].active)
             DrawTexture(BossMonster, Boss[i].rect.x, Boss[i].rect.y, WHITE);
     }



     //Anzeigen
     DrawText(" M - pause", 70, 20, 20, LIGHTGRAY);
     DrawText(" TAB - Switch Cam", 70, 60, 20, LIGHTGRAY);
     // DrawText("Lives", 415, 180, 30, RED);
      //DrawText("Space", 415, 220, 30, DARKBLUE);
     // DrawText(TextFormat("Lives: %02i", player.lives), 425, 180, 30, RED);
     // DrawText(TextFormat("Space: %02i", planet.landed), 425, 220, 25, BLUE);
     DrawText(TextFormat("Score: %02i", highscore), 820, 25, 35, LIGHTGRAY);
     //Live Anzeige
     if (player.lives == 3) {
         DrawTexture(Lives, 900, 100, WHITE);
         DrawTexture(Lives, 930, 100, WHITE);
         DrawTexture(Lives, 960, 100, WHITE);
     }
     if (player.lives == 2) {
         DrawTexture(Lives, 930, 100, WHITE);
         DrawTexture(Lives, 960, 100, WHITE);
     }
     if (player.lives == 1) {
         DrawTexture(Lives, 960, 100, WHITE);
     }

     //Space Anzeige 
     if (planet.landed == 5) {
         DrawTexture(Spaces, 820, 65, WHITE);
         DrawTexture(Spaces, 855, 65, WHITE);
         DrawTexture(Spaces, 890, 65, WHITE);
         DrawTexture(Spaces, 925, 65, WHITE);
         DrawTexture(Spaces, 960, 65, WHITE);
     }
     if (planet.landed == 4) {        
         DrawTexture(Spaces, 855, 65, WHITE);
         DrawTexture(Spaces, 890, 65, WHITE);
         DrawTexture(Spaces, 925, 65, WHITE);
         DrawTexture(Spaces, 960, 65, WHITE);
     }
     if (planet.landed == 3) {
         DrawTexture(Spaces, 890, 65, WHITE);
         DrawTexture(Spaces, 925, 65, WHITE);
         DrawTexture(Spaces, 960, 65, WHITE);
     }
     if (planet.landed == 2) {       
         DrawTexture(Spaces, 925, 65, WHITE);
         DrawTexture(Spaces, 960, 65, WHITE);
     }
     if (planet.landed == 1) {     
         DrawTexture(Spaces, 960, 65, WHITE);
     }

     








     
}

