#pragma once
#include "IEntity.h"
#include "Hitbox.h"
#include "Framework.h"

class Enemy : public IEntity {
    Sprite* sprite = nullptr;
    int w = 0, h = 0;
	int centreX = 0, centreY = 0;
    bool isDead = false;
	Coordinates coordinates;
    int enemyW, enemyH;

public:
    Enemy(float x, float y, const char* path) {
        sprite = createSprite(path);
        if (sprite) getSpriteSize(sprite, w, h);
        setCoordinates(Coordinates(x, y));
    }

    ~Enemy() { if (sprite) destroySprite(sprite); }

    
   
    bool getIsDead() { return isDead; }
    void die() { isDead = true; }

    int getWidth() override { return w; }
    int getHeight() override { return h; }

    void reDraw() override {
        if (isDead) return;
        Coordinates pos = getCoordinates();
        if (sprite) drawSprite(sprite, pos.x, pos.y);
    }

    void move(FRSide side) override {}
    void setSpritePicture(const char* path) override {}
    void collide(IEntity* other) override {}
};

