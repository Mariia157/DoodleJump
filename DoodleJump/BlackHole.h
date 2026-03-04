#pragma once
#include "IEntity.h"
#include <cmath>
class BlackHole :
    public IEntity
{
    float pullStrength = 100.0f;  // сила притяжения

public:
    BlackHole(float x, float y, const char* path) {
        setSpritePicture(path);
        setCoordinates(Coordinates(x, y));
    }

    ~BlackHole() = default;
    void move(FRSide side) override {}
    void collide(IEntity* other) override {}

    // Возвращает вектор притяжения для игрока
    void applyGravity(float& playerVelX, float& playerVelY, float playerX, float playerY);

    // Проверка попадания игрока в чёрную дыру
    bool isPlayerInside(float playerX, float playerY, int playerW, int playerH);
};

