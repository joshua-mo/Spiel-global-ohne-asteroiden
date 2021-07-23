#pragma once

#include "Screen.h"


namespace Game {
    class MenuScreen : public Screen {
    private:
        MenuScreen();
        Texture2D background;
        Texture2D welt;
        Texture2D start;
        Texture2D startpink;
        Texture2D quit;
        Texture2D quitpink;

    public:
        static Screen * getInstance() {
            static MenuScreen instance;
            return &instance;
        }

        MenuScreen(MenuScreen const &) = delete;

        void operator=(MenuScreen const &) = delete;

        ~MenuScreen();

        void ProcessInput() override;

        void Update() override;

        void Draw() override;
    };
}
