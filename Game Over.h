#pragma once

#include "Screen.h"

namespace Game {
    class GameOver : public Screen {
    private:
        GameOver();
        Texture2D background;
        Texture2D welt;

    public:
     

        static Screen* getInstance() {
            static GameOver instance;
            return &instance;
        }

        GameOver(GameOver const&) = delete;

        void operator=(GameOver const&) = delete;

        ~GameOver();

        void ProcessInput() override;

        void Update() override;

        void Draw() override;
    };

    
}
