#include "BlackHole.h"

// Возвращает вектор притяжения для игрока
void BlackHole::applyGravity(float& playerVelX, float& playerVelY, float playerX, float playerY) {
    Coordinates pos = getCentreCoordinates();

    float dx = pos.x - playerX;
    float dy = pos.y - playerY;

    // Расстояние до чёрной дыры
    float distance = std::sqrt(dx * dx + dy * dy);
    if (distance < 1.0f) distance = 1.0f;  // избегаем деления на ноль

    // Сила притяжения обратно пропорциональна расстоянию
    float force = pullStrength / (distance * distance);

    // Нормализуем вектор и применяем силу
    playerVelX += (dx / distance) * force;
    playerVelY += (dy / distance) * force;
}

// Проверка попадания игрока в чёрную дыру
bool BlackHole::isPlayerInside(float playerX, float playerY, int playerW, int playerH) {
    Coordinates pos = getCentreCoordinates();
    float dx = pos.x - (playerX + playerW / 2);
    float dy = pos.y - (playerY + playerH / 2);
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance < (getWidth() / 2);  // радиус чёрной дыры
}
