#pragma once
#include "IEntity.h"
#include <cmath>
class Projectile :
    public IEntity
{
    float speed = 5.0f;
    float dirX = 0.0f;  // направление по X
    float dirY = -1.0f; // направление по Y
	int sw = 0, sh = 0; 
public:
public:
    Projectile(float x, float y, float targetX, float targetY, const char* path) {
        setSpritePicture(path);
        setCoordinates(Coordinates(x, y));
        getScreenSize(sw, sh);
        // Вычисление вектора направления от пули к курсору
        float dx = targetX - x;
        float dy = targetY - y;

        // Нормализация вектора чтобы скорость была одинаковой в любом направлении
        float length = std::sqrt(dx * dx + dy * dy);
        if (length > 0) {
            dirX = dx / length;
            dirY = dy / length;
        }
    }

    ~Projectile() = default;
    void move(FRSide side) override {}
    void collide(IEntity* other) override {}

    void update();

    bool isOutOfBounds();
};