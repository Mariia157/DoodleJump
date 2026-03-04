#include "IEntity.h"

Coordinates IEntity::getCentreCoordinates() {
	Coordinates pos = getCoordinates();
	return Coordinates(
		pos.x + getWidth() / 2,
		pos.y + getHeight() / 2
	);
}

// Спрайт — общая логика загрузки и отрисовки
void IEntity::setSpritePicture(const char* path) {
	if (sprite) {
		destroySprite(sprite);
		sprite = nullptr;
	}
	sprite = createSprite(path);
	if (sprite) getSpriteSize(sprite, w, h);  // автоматически обновляем размеры
}

void IEntity::reDraw() {
	if (isDead) return;  // мёртвые объекты не отрисовываются
	Coordinates pos = getCoordinates();
	if (sprite) drawSprite(sprite, pos.x, pos.y);
}
