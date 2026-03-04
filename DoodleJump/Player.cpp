#include "Player.h"

void Player::setSpritePicture(const char* path) {
	IEntity::setSpritePicture(path);
	doodleW = w;
	doodleH = h;
}

void Player::move(FRSide side) {
	int sw = 0, sh = 0;
	Coordinates cur = getCoordinates();
	getScreenSize(sw, sh);
	switch (side) {
	case FRSide::RIGHT:
		setSpritePicture(spritePathRight);
		cur.x += moveSpeed;
		if (cur.x > sw) cur.x = 0;
		velocityX = moveSpeed;
		break;
	case FRSide::LEFT:
		setSpritePicture(spritePathLeft);
		cur.x -= moveSpeed;
		if (cur.x < 0) cur.x = sw;
		velocityX = -moveSpeed;
		break;
	}
	setCoordinates(cur);
}

void Player::jump() {
	if (!canJump) return;
	canJump = false;
	isUp = true;
	fallSpeed = normalJumpSpeed;
}

void Player::boostedJump() {
	if (!canJump) return;
	canJump = false;
	isUp = true;
	fallSpeed = boostJumpSpeed;  // на 300% выше
}

void Player::fall() {
	int sw, sh;
	getScreenSize(sw, sh);
	Coordinates cur = getCoordinates();
	updateImmunity();

	if (fallSpeed > 0) {
		canJump = true;
		isFall = true;
		isUp = false;
	}

	cur.y += fallSpeed;

	if (fallSpeed < 0)
		fallSpeed += 0.01f;   // гравитация на подъёме
	else
		fallSpeed += 0.005f;  // гравитация на падении

	if (cur.y >= sh - doodleH) {
		if (isImmune) {
			//при иммунитете прыгаем от пола вместо смерти
			cur.y = sh - doodleH;
			fallSpeed = normalJumpSpeed;
			canJump = false;
		}
		else {
			die();  // обычная смерть
		}
	}

	setCoordinates(cur);
}

void Player::activateImmunity() {
	isImmune = true;
	immunityTimer = IMMUNITY_DURATION;
}

void Player::updateImmunity() {
	if (!isImmune) return;
	immunityTimer -= 1.0f;
	if (immunityTimer <= 0.0f) {
		isImmune = false;
		immunityTimer = 0.0f;
	}
}

void Player::collide(IEntity* other) {
	if (!other) return;

	Platform* platform = dynamic_cast<Platform*>(other);
	Enemy* enemy = dynamic_cast<Enemy*>(other);
	ImmunityOrb* orb = dynamic_cast<ImmunityOrb*>(other);

	Hitbox hitbox;
	hitbox.setEntity(this);
	hitbox.setHitboxSize(getWidth(), getHeight());
	Coordinates pos = getCoordinates();
	hitbox.setHitboxCoordinates(static_cast<int>(pos.x), static_cast<int>(pos.y));

	if (!hitbox.onCollided(other)) return;

	if (platform) {
		if (hitbox.isCollidedAbove(other)) {
			isFall = false;
			isOnPlatform = true;

			if (platform->getType() == PlatformType::BOOST) {
				boostedJump();
			}
			else {
				jump();
			}
		}
	}
	else if (orb && !orb->getIsPickedUp()) {
		orb->pickUp();
		activateImmunity();
	}
	else if (enemy && !enemy->getIsDead()) {
		if (hitbox.isCollidedAbove(other) && isFall) {
			enemy->die();
			jump();
		}
		else {
			die();
		}
	}
}
