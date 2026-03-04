#include "Environment.h"

bool isPressed = false;

FRKey currentKey;

void Environment::setBackgroundPicture(const char* path) {
    if (backgroundSprite != nullptr) {
        destroySprite(backgroundSprite);
    }
    backgroundSprite = createSprite(path);  // только загрузка
    // Растягиваем на весь экран
    if (backgroundSprite != nullptr) {
        int w, h;
        getScreenSize(w, h);
        setSpriteSize(backgroundSprite, w, h);  
    }
    std::cout << "background set" << std::endl;
}

void Environment::drawBackground() {
    if (backgroundSprite != nullptr) {
        drawSprite(backgroundSprite, 0, 0);  // отрисовка отдельно
        //std::cout << "background drown" << std::endl;
    }
}
