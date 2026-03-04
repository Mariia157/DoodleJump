#include "Projectile.h"

void Projectile::update() {
    Coordinates cur = getCoordinates();
    cur.x += dirX * speed;  // двигаем по X
    if (cur.x > sw) cur.x = 0;
    cur.y += dirY * speed;  // двигаем по Y
    if (cur.x < 0) cur.x = sw;
    setCoordinates(cur);
}

bool Projectile::isOutOfBounds() {
    int sw, sh;
    getScreenSize(sw, sh);
    Coordinates cur = getCoordinates();
    return cur.x < 0 || cur.x > sw || cur.y < 0 || cur.y > sh;
}
