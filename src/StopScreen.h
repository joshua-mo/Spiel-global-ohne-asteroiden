#pragma once
#include "Screen.h"


namespace Game {
    class StopScreen : public Screen {
    private:
        StopScreen();
        Texture2D background;
       

    public:
        static Screen* getInstance() {
            static StopScreen instance;
            return &instance;
        }

        StopScreen(StopScreen const&) = delete;

        void operator=(StopScreen const&) = delete;

        ~StopScreen();

        void ProcessInput() override;

        void Update() override;

        void Draw() override;
    };
}
