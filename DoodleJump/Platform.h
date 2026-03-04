#pragma once
#include "IEntity.h"

enum class PlatformType {
	NORMAL,
	BOOST  // платформа с ускорением
};

struct Platform : public IEntity {
	PlatformType type = PlatformType::NORMAL;

	Platform(float x, float y, const char* path, PlatformType t = PlatformType::NORMAL) {
		type = t;
		setSpritePicture(path);
		setCoordinates(Coordinates(x, y));
	}

	Platform(int x, int y, const char* path, PlatformType t = PlatformType::NORMAL)
		: Platform(static_cast<float>(x), static_cast<float>(y), path, t) {
	}

	~Platform() = default;

	PlatformType getType() { return type; }

	void collide(IEntity* other) override {}
};