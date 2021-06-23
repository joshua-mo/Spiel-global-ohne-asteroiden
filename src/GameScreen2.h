#pragma once

#include <vector>
#include <memory>

#include "raylib.h"

#include "Screen.h"
#include "Sprite.h"
#include "math.h"
#include "Entity.h"



#define NUM_SHOOTS 50
#define NUM_MAX_ENEMIES 50
#define FIRST_WAVE 10
#define SECOND_WAVE 20
#define THIRD_WAVE 50
#define NUM_MAX_PLANETS 2



namespace Game {
    class GameScreen2 : public Screen {

    private:
        //Texturen        
        Texture2D background;
        Texture2D playerTexture;
        Texture2D alienTexture;
        Texture2D alienTexture2;
        Texture2D Lives;
        Texture2D Spaces;



    private:
        std::vector<std::unique_ptr<Sprite>> sprites;

        GameScreen2();


    public:
        static Screen* getInstance() {
            static GameScreen2 instance;
            return &instance;
        }

        GameScreen2(GameScreen2 const&) = delete;

        void operator=(GameScreen2 const&) = delete;

        ~GameScreen2();

        void ProcessInput() override;

        void Update() override;



        void Draw() override;
    };









}
