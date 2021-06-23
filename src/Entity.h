#pragma once
#include "raylib.h"
#include "math.h"

//Bullet Klasse 
typedef struct Bullet
{
    Rectangle rect;
    Vector2 speed;
    bool active;
    Color color;
    Texture2D texture{};
} Bullet;

//Player Klasse
typedef struct Player
{
    
    int lives = 3; //Anzahl Leben
    Rectangle rect;
    Vector2 speed;
    Color color;
} Player;

//Enemy Klasse 
typedef struct Enemy
{
    Rectangle rect;
    Vector2 speed;
    bool active;
    Color color;
    Texture2D texture{};
    bool gothit;
} Enemy;

typedef struct Planet
{
    int landed = 5; //Freier Platz
    Vector2 position;
    float radius;
    Color color;
    Texture2D texture{};
    

} Planet;

