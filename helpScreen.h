#pragma once

#include "Screen.h"


namespace Game {
    class helpScreen : public Screen {
    private:
        helpScreen();
        Texture2D background;
        Texture2D help;

    public:
        static Screen* getInstance() {
            static helpScreen instance;
            return &instance;
        }

        helpScreen(helpScreen const&) = delete;

        void operator=(helpScreen const&) = delete;

        ~helpScreen();

        void ProcessInput() override;

        void Update() override;

        void Draw() override;
    };
}
