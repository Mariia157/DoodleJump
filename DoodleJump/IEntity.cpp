#include "IEntity.h"

Coordinates IEntity::getCentreCoordinates() {
	Coordinates pos = getCoordinates();
	return Coordinates(
		pos.x + getWidth() / 2,
		pos.y + getHeight() / 2
	);
}

void IEntity::setSpritePicture(const char* path) {
	if (sprite) {
		destroySprite(sprite);
		sprite = nullptr;
	}
	sprite = createSprite(path);
	if (sprite) getSpriteSize(sprite, w, h);
}

void IEntity::reDraw() {
	if (isDead) return;
	Coordinates pos = getCoordinates();
	if (sprite) drawSprite(sprite, pos.x, pos.y);
}
