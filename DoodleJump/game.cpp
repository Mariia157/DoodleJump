#include <iostream>
#include "Framework.h"
#include "Player.h"
#include "IEntity.h"
#include "Environment.h"
#include <vector>
#include "Platform.h"
#include <algorithm>
#include"Projectile.h"
#include "BlackHole.h"

/* Test Framework realization */
class MyFramework : public Framework {
	Player* doodle = nullptr;
	Environment* environment;
	std::vector<Platform*> platforms;
	std::vector<IEntity*> entities;
	float lastPlatformY = 0.0f;
	float cameraOffset = 0.0f;
	int screenW = 500;
	int screenH = 600;
	int score = 0;
	float highestY = 0.0f;
	std::vector<Enemy*> enemies;
	Sprite* gameOverSprite = nullptr;
	float highestPlatformY = 0.0f;  
	bool isGameOver = false;
	std::vector<Projectile*> bullets;
	int platformsPassed = 0;
	int mouseX = 0, mouseY = 0;
	std::vector<BlackHole*> blackHoles;
	std::vector<ImmunityOrb*> orbs;
	Sprite* restartSprite = nullptr;
	int restartX = 0, restartY = 0;
	int restartW = 0, restartH = 0;

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		environment->setWindowSize(screenW, screenH);
		width = screenW;
		height = screenH;

		fullscreen = false;
	}

	virtual bool Init() {
		
		srand(time(0));
		doodle = new Player();
		environment = new Environment();
		entities.push_back(doodle);
		/// Начальные платформы
		lastPlatformY = screenH;
		for (int i = 0; i < 8; i++) {
			float randX = rand() % (screenW - 64);
			lastPlatformY -= 60.0f;
			Platform* p = new Platform(randX, lastPlatformY, "./data/platform.png");
			entities.push_back(p);
			platforms.push_back(p);
		}
		return true;
	}

	virtual void Close() {
		delete doodle;
	}

	virtual void loadRestartButton() {
		if (restartSprite) destroySprite(restartSprite);
		restartSprite = createSprite("./data/play-again-on@2x.png");
		if (restartSprite) {
			int sw, sh;
			getScreenSize(sw, sh);
			getSpriteSize(restartSprite, restartW, restartH);
			// По центру экрана
			restartX = (sw / 1.5) - (restartW / 2);
			restartY = (sh / 1.5) - (restartH / 2) + 50;
		}
	}

	virtual void restart() {
		isGameOver = false;

		for (auto* entity : entities) delete entity;
		entities.clear();
		platforms.clear();
		enemies.clear();
		blackHoles.clear();
		orbs.clear();

		score = 0;
		platformsPassed = 0;
		cameraOffset = 0.0f;
		lastPlatformY = 0.0f;
		highestPlatformY = 0.0f;

      doodle = new Player();
	
		entities.push_back(doodle);

		for (auto* b : bullets) delete b;
		bullets.clear();

		int sw, sh;
		getScreenSize(sw, sh);
		lastPlatformY = sh;
		for (int i = 0; i < 8; i++) {
			float randX = rand() % (sw - 64);
			lastPlatformY -= 75.0f;
			Platform* p = new Platform(randX, lastPlatformY, "./data/platform.png");
			entities.push_back(p);
			platforms.push_back(p);
		}
	}

	virtual void movement() {
		if (isPressed) {
			switch (currentKey) {
			case FRKey::RIGHT:
				doodle->move(FRSide::RIGHT);
				break;
			case FRKey::LEFT:
				doodle->move(FRSide::LEFT);
				break;
			default:
				break;
			}
		}
	}

	virtual void cameraMovement() {
		float highestPlatformY = 0.0f;
		int w, h;
		getScreenSize(w, h);
		Coordinates doodlePos = doodle->getCoordinates();

		// Камера двигается вверх за игроком
		if (doodlePos.y < h / 2) {
			float shift = h / 2 - doodlePos.y;
			cameraOffset += shift;

			score = static_cast<int>(cameraOffset / 10);

			// Двигаем игрока вниз
			doodle->setCoordinates(Coordinates(doodlePos.x, h / 2));

			for (auto* p : platforms) {
				Coordinates pos = p->getCoordinates();
				pos.y += shift;
				p->setCoordinates(pos);
			}
			for (auto* e : enemies) {
				Coordinates pos = e->getCoordinates();
				pos.y += shift;
				e->setCoordinates(pos);
			}

			for (auto* b : bullets) {
				Coordinates pos = b->getCoordinates();
				pos.y += shift;
				b->setCoordinates(pos);
			}

			for (auto* bh : blackHoles) {
				Coordinates pos = bh->getCoordinates();
				pos.y += shift;
				bh->setCoordinates(pos);
			}

			for (auto* orb : orbs) {
				Coordinates pos = orb->getCoordinates();
				pos.y += shift;
				orb->setCoordinates(pos);
			}

			lastPlatformY += shift;
			generatePlatforms();
			erasePlatforms();
			eraseEnemies();
			eraseBullets();
			eraseBlackHoles();
			eraseOrbs();
		}
	}
	
	virtual void applyBlackHoles() {
		Coordinates playerPos = doodle->getCoordinates();
		float velX = doodle->getVelocityX();
		float velY = doodle->getFallSpeed();

		for (auto* bh : blackHoles) {
			// Притяжение
			bh->applyGravity(velX, velY, playerPos.x, playerPos.y);

			// Смерть при попадании внутрь
			if (bh->isPlayerInside(playerPos.x, playerPos.y,
				doodle->getWidth(), doodle->getHeight())) {
				doodle->die();
			}
		}
		doodle->setVelocityX(velX);
		doodle->setFallSpeed(velY);
	}

	virtual void generatePlatforms() {
		int w, h;
		getScreenSize(w, h);
		
		highestPlatformY = h;
		for (auto* p : platforms) {
			highestPlatformY = std::min(highestPlatformY, p->getCoordinates().y);
		}
		// Генерируем пока есть место сверху
		while (highestPlatformY > 0) {
			float randX = rand() % (w - 64);
			highestPlatformY -= 100.0f;

			// 20% шанс буст платформы
			bool isBoost = rand() % 100 < 10;
			Platform* p = nullptr;

			if (isBoost) {
				p = new Platform(randX, highestPlatformY,
					"./data/platform-boost.png",
					PlatformType::BOOST);
			}
			else {
				p = new Platform(randX, highestPlatformY,
					"./data/platform.png",
					PlatformType::NORMAL);
			}

			entities.push_back(p);
			platforms.push_back(p);
			spawnEnemyOnPlatform(p);
			spawnBlackHole(highestPlatformY - 30.0f);
			spawnOrbOnPlatform(p);
		}
	}

	virtual void erasePlatforms() {
		int w, h;
		getScreenSize(w, h);

		platforms.erase(
			std::remove_if(platforms.begin(), platforms.end(),
				[&](Platform* p) {
					if (p->getCoordinates().y > h) {
						platformsPassed++;  //считаем пройденные платформы

						entities.erase(
							std::remove(entities.begin(), entities.end(), p),
							entities.end()
						);
						delete p;
						return true;
					}
					return false;
				}),
			platforms.end()
		);
	}

	virtual void spawnEnemyOnPlatform(Platform* p) {
		int sw, sh;
		getScreenSize(sw, sh);
		// Шанс появления врага 20%
		if (rand() % 100 > 20) return;

		Coordinates centre = p->getCentreCoordinates();
		int enemyW = 60;
		
		float enemyX = centre.x - (enemyW / 2);  // центр врага = центр платформы
		float enemyY = centre.y - 58.0f;                 // над платформой

		Enemy* e = new Enemy(enemyX, enemyY, "./data/enemy.png");
		entities.push_back(e);
		enemies.push_back(e);
	}

	virtual void eraseEnemies() {
		enemies.erase(
			std::remove_if(enemies.begin(), enemies.end(),
				[&](Enemy* e) {
					int sw, sh;
					getScreenSize(sw, sh);
					if (e->getCoordinates().y > sh || e->getIsDead()) {
						entities.erase(
							std::remove(entities.begin(), entities.end(), e),
							entities.end()
						);
						delete e;
						return true;
					}
					return false;
				}),
			enemies.end()
		);
	}

	virtual void spawnBlackHole(float y) {
		if (rand() % 100 > 15) return;  // 15% шанс
		int sw, sh;
		getScreenSize(sw, sh);
		float randX = rand() % (sw - 64);
		BlackHole* bh = new BlackHole(randX, y, "./data/hole.png");
		entities.push_back(bh);
		blackHoles.push_back(bh);
	}

	virtual void eraseBlackHoles() {
		int sw, sh;
		getScreenSize(sw, sh);
		blackHoles.erase(
			std::remove_if(blackHoles.begin(), blackHoles.end(),
				[&](BlackHole* bh) {
					if (bh->getCoordinates().y > sh) {
						entities.erase(
							std::remove(entities.begin(), entities.end(), bh),
							entities.end()
						);
						delete bh;
						return true;
					}
					return false;
				}),
			blackHoles.end()
		);
	}

	virtual void spawnOrbOnPlatform(Platform* p) {
		if (rand() % 100 > 5) return;  // 5% шанс

		Coordinates centre = p->getCentreCoordinates();
		ImmunityOrb* orb = new ImmunityOrb(
			centre.x,
			p->getCoordinates().y - 32.0f,  // над платформой
			"./data/immunity-orb.png"
		);
		entities.push_back(orb);
		orbs.push_back(orb);
	}

	virtual void eraseOrbs() {
		int sw, sh;
		getScreenSize(sw, sh);
		orbs.erase(
			std::remove_if(orbs.begin(), orbs.end(),
				[&](ImmunityOrb* orb) {
					if (orb->getIsPickedUp() || orb->getCoordinates().y > sh) {
						entities.erase(
							std::remove(entities.begin(), entities.end(), orb),
							entities.end()
						);
						delete orb;
						return true;
					}
					return false;
				}),
			orbs.end()
		);
	}

	virtual void collision() {
		for (auto* entity : entities) {
			if (!entity) continue;
			Player* player = dynamic_cast<Player*>(entity);
			if (player) {
				for (auto* entityOther : entities) {
					if (player == entityOther) continue;
					player->collide(entityOther);
				}
			}
		}
	}

	virtual void checkBulletsCollision() {
		for (auto* b : bullets) {
			for (auto* e : enemies) {
				if (!e->getIsDead()) {
					Hitbox hitbox;
					hitbox.setEntity(b);
					hitbox.setHitboxSize(b->getWidth(), b->getHeight());
					Coordinates pos = b->getCoordinates();
					hitbox.setHitboxCoordinates(pos.x, pos.y);
					if (hitbox.onCollided(e)) {
						e->die();
						b->die();
					}
				}
			}
			b->reDraw();
		}
	}

	virtual void eraseBullets() {
		// Удаляем пули за экраном
		bullets.erase(
			std::remove_if(bullets.begin(), bullets.end(),
				[](Projectile* b) {
					if (b->isOutOfBounds()) { delete b; return true; }
					return false;
				}),
			bullets.end()
		);
	}

	virtual void gameOver() {
		if (isGameOver) return;
		isGameOver = true;
		for (auto* entity : entities) {
			delete entity;
		}
		entities.clear();
		platforms.clear();
		enemies.clear();
		blackHoles.clear();
		orbs.clear();
		gameOverSprite = createSprite("./data/race-over.png");
		loadRestartButton();
	}

	virtual bool Tick() {
		environment->drawBackground();

		if (isGameOver) {
			if (gameOverSprite) {
				int sw, sh;
				getScreenSize(sw, sh);
				int spriteW, spriteH;
				getSpriteSize(gameOverSprite, spriteW, spriteH);
				drawSprite(gameOverSprite,
					(sw / 2) - (spriteW / 2),
					(sh / 2) - (spriteH / 2));
			}
			if (restartSprite) {
				drawSprite(restartSprite, restartX, restartY);
			}
			return false;
		}
		if (doodle->getIsDead()) {
			gameOver();
			return false;
		}

		cameraMovement();
		movement();
		applyBlackHoles();
		collision();
		doodle->fall();
		std::cout << "Score: " << score << std::endl;
		std::cout << "Platforms passed: " << platformsPassed << std::endl;
		for (auto* entity : entities) if (entity) entity->reDraw();
		for (auto* b : bullets) b->update();
		checkBulletsCollision();
		eraseBullets();
		eraseOrbs();
		doodle->reDraw();

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		mouseX = x;
		mouseY = y;
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
    if (button == FRMouseButton::LEFT && !isReleased) {
        // Проверяем попадание в кнопку рестарта
        if (isGameOver &&
            mouseX >= restartX && mouseX <= restartX + restartW &&
            mouseY >= restartY && mouseY <= restartY + restartH) {
            restart(); 
            return;
        }

        // Выстрел
        if (!isGameOver) {
            Coordinates cur = doodle->getCoordinates();
            float bulletX = cur.x + (doodle->getWidth() / 2);
            float bulletY = cur.y + (doodle->getHeight() / 2);
            bullets.push_back(new Projectile(
                bulletX, bulletY, mouseX, mouseY,
                "./data/projectile.png"
            ));
        }
    }
}

	virtual void onKeyPressed(FRKey k) {
		isPressed = true;
		currentKey = k;


	}

	virtual void onKeyReleased(FRKey k) {
		isPressed = false;
	}

	virtual const char* GetTitle() override
	{
		return "DoodleJump";
	}
};

int main(int argc, char *argv[])
{
	return run(new MyFramework);
}
