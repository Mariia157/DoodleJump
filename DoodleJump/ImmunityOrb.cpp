#include "ImmunityOrb.h"

void ImmunityOrb::reDraw() {
    if (isPickedUp) return;  // не рисуем после подбора
    Coordinates pos = getCoordinates();
    if (sprite) drawSprite(sprite, pos.x, pos.y);
}
