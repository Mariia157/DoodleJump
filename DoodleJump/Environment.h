#pragma once
#include"Framework.h"
#include <iostream>
#include "Platform.h"
extern bool isPressed;
extern FRKey currentKey;


class Environment
{
    Sprite* backgroundSprite = nullptr;
    const char* backgroundPicture = "C:/data/bck@2x.png";
	Sprite* scoreSprite = nullptr;
    int score = 0;
public:

    Environment() { setBackgroundPicture(backgroundPicture); }

    void setWindowSize(int &width, int &height) {
        int userW = 0;
        int userH = 0;
        std::cout << "Enter window width: ";
        std::cin >> userW;
        std::cout << std::endl << "Enter window height: ";
        std::cin >> userH;
        std::cout << std::endl;
        width = userW;
        height = userH;
    }

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
            //std::cout << "background drown" << std::endl;
        }
    }

    void updateScore() {

        //score = ;
        
	}

    //void generatePlatforms() {
    //    int sw, sh;
    //    getScreenSize(sw, sh);

    //    // Генерируем пока верхняя платформа не выше экрана
    //    while (lastPlatformY > cameraOffset - sh) {
    //        float randX = rand() % (sw - 64);
    //        lastPlatformY -= 60.0f;  // расстояние между платформами

    //        Platform* p = new Platform(randX, lastPlatformY, "C:/data/platform.png");
    //        entities.push_back(p);
    //        platforms.push_back(p);
    //    }
    //}
    //void erasePlatforms() {
    //    int sw, sh;
    //    getScreenSize(sw, sh);

    //    platforms.erase(
    //        std::remove_if(platforms.begin(), platforms.end(),
    //            [&](Platform* p) {
    //                if (p->getCoordinates().y > sh) {
    //                    // Удаляем и из entities
    //                    entities.erase(
    //                        std::remove(entities.begin(), entities.end(), p),
    //                        entities.end()
    //                    );
    //                    delete p;
    //                    return true;
    //                }
    //                return false;
    //            }),
    //        platforms.end()
    //    );
    //}
};


