#pragma once

#include "Screen.h"


namespace Game {
    class PreScreen : public Screen {
    private:
        PreScreen();
        Texture2D background;
        Texture2D story;

    public:
        static Screen* getInstance() {
            static PreScreen instance;
            return &instance;
        }

        PreScreen(PreScreen const&) = delete;

        void operator=(PreScreen const&) = delete;

        ~PreScreen();

        void ProcessInput() override;

        void Update() override;

        void Draw() override;
    };
}
