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
    Vector4 pos;
    Vector4 speed;
    Color color;
} Player;

//Enemy Klasse 
typedef struct Enemy
{
    Rectangle rect;
    Vector4 pos;
    Vector4 speed;
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




//// Camera type, defines a camera position/orientation in 3d space
//typedef struct Camera3D {
//    Vector3 position;       // Camera position
//    Vector3 target;         // Camera target it looks-at
//    Vector3 up;             // Camera up vector (rotation over its axis)
//    float fovy;             // Camera field-of-view apperture in Y (degrees) in perspective, used as near plane width in orthographic
//    int type;               // Camera type, defines projection type: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC
//    CameraProjection projection;
//} Camera3D;