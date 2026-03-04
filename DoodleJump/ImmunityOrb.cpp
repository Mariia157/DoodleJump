#include "ImmunityOrb.h"

void ImmunityOrb::reDraw() {
    if (isPickedUp) return; 
    Coordinates pos = getCoordinates();
    if (sprite) drawSprite(sprite, pos.x, pos.y);
}
