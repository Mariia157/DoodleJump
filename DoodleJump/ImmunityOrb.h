#pragma once
#include "IEntity.h"

class ImmunityOrb : public IEntity {
    bool isPickedUp = false;

public:
    ImmunityOrb(float x, float y, const char* path) {
        setSpritePicture(path);
        setCoordinates(Coordinates(x, y));
    }

    ~ImmunityOrb() = default;

    bool getIsPickedUp() { return isPickedUp; }
    void pickUp() { isPickedUp = true; }

    void reDraw() override;

    void move(FRSide side) override {}
    void collide(IEntity* other) override {}
};