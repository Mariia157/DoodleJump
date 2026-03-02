#pragma once
#include "IEntity.h"
class Platform : public IEntity {
    Sprite* sprite = nullptr;
    int w = 60, h = 10;  // размеры платформы

public:
    Platform(float x, float y, const char* path) {
        sprite = createSprite(path);
        getSpriteSize(sprite, w, h);
        setCoordinates(Coordinates(x, y));
    }

    // Overload that accepts integer coordinates (helps IDE/IntelliSense resolve calls with integer literals)
    Platform(int x, int y, const char* path) : Platform(static_cast<float>(x), static_cast<float>(y), path) {}

    ~Platform() { if (sprite) destroySprite(sprite); }

    int getWidth() override { return w; }
    int getHeight() override { return h; }
    void setSpritePicture(const char* path) override {
        destroySprite(sprite);
        sprite = createSprite(path);
    }
    void reDraw() override {
        Coordinates pos = getCoordinates();
        drawSprite(sprite, pos.x, pos.y);
    }

    bool onCollided(IEntity* other) override {
        Coordinates cur = getCoordinates();
        Coordinates otherPos = other->getCoordinates();

        return
            cur.x < otherPos.x + other->getWidth() &&
            cur.x + w > otherPos.x &&
            cur.y < otherPos.y + other->getHeight() &&
            cur.y + h > otherPos.y;
    }
};