#pragma once
#include "IEntity.h"
struct Platform : public IEntity {
    int w = 40, h = 10;  // размеры платформы
    Sprite* sprite = nullptr;

    Platform(float x, float y, const char* path) {
        sprite = createSprite(path);
        if (sprite) getSpriteSize(sprite, w, h);
        setCoordinates(Coordinates(x, y));
    }

    Platform(int x, int y, const char* path)
        : Platform(static_cast<float>(x), static_cast<float>(y), path) {
    }

    ~Platform() {
        if (sprite) destroySprite(sprite);
    }

    int getWidth() override { return w; }
    int getHeight() override { return h; }
    void reDraw() override {
        Coordinates curCoordinates = getCoordinates();
        if (sprite) {
            drawSprite(sprite, curCoordinates.x, curCoordinates.y);
        }
	}

    // Implement collide to satisfy IEntity's pure virtual requirement
    void collide(IEntity* other) override {
        // Platforms do not actively respond to collisions in current design
    }

};