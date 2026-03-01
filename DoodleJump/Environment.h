#pragma once
#include"Framework.h"
#include <iostream>
extern bool isPressed;
extern FRKey currentKey;



class Environment
{
    Sprite* backgroundSprite = nullptr;
    const char* backgroundPicture = "C:/data/bck.png";
public:

    Environment() { setBackgroundPicture(backgroundPicture); }

    void setBackgroundPicture(const char* path) {
        if (backgroundSprite != nullptr) {
            destroySprite(backgroundSprite);
        }
        backgroundSprite = createSprite(path);  // только загрузка
        std::cout << "background set" << std::endl;
    }

    void drawBackground() {
        if (backgroundSprite != nullptr) {
            drawSprite(backgroundSprite, 0, 0);  // отрисовка отдельно
            std::cout << "background drown" << std::endl;
        }
    }
};


