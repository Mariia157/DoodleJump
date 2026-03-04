#pragma once
#include"Framework.h"
#include <iostream>
#include "Platform.h"
extern bool isPressed;
extern FRKey currentKey;


class Environment
{
    Sprite* backgroundSprite = nullptr;
    const char* backgroundPicture = "./data/bck@2x.png";
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

    void setBackgroundPicture(const char* path);

    void drawBackground();
};


