
#include <iostream>
#include "Framework.h"
#include "Player.h"
#include "IEntity.h"
#include "Environment.h"
#include "Constants.h"
#include <vector>
#include "Platform.h"
#include <algorithm>

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
	Sprite* scoreSprite = nullptr;
	int score = 0;
	float highestY = 0.0f;
	std::vector<Enemy*> enemies;
	float highestPlatformY = 0.0f;  // Y самой высокой платформы
public:



	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		
		//environment->setWindowSize(width, height);
		width = 500;
		height = 600;

		fullscreen = false;
	}

	

	virtual bool Init() {

		doodle = new Player();
		environment = new Environment();
		entities.push_back(doodle);
		scoreSprite = createSprite("C:/data/top-score@2x.png");
		/// Начальные платформы
		lastPlatformY = screenH;
		for (int i = 0; i < 8; i++) {
			float randX = rand() % (screenW - 64);
			lastPlatformY -= 60.0f;
			Platform* p = new Platform(randX, lastPlatformY, "C:/data/platform.png");
			entities.push_back(p);
			platforms.push_back(p);
			
		}
		
		return true;
	}
	virtual void Close() {
		delete doodle;
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

			// Двигаем все платформы вниз
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
						
			lastPlatformY += shift;
			generatePlatforms();
			erasePlatforms();
			eraseEnemies();
		}
	}

	// В полях класса:
	

	virtual void generatePlatforms() {
		int w, h;
		getScreenSize(w, h);
		// Находим самую высокую платформу
		highestPlatformY = h;
		for (auto* p : platforms) {
			highestPlatformY = std::min(highestPlatformY, p->getCoordinates().y);
		}
		// Генерируем пока есть место сверху
		while (highestPlatformY > 0) {
			float randX = rand() % (w - 64);
			highestPlatformY -= 125.0f;

			Platform* p = new Platform(randX, highestPlatformY, "C:/data/platform.png");
			entities.push_back(p);
			platforms.push_back(p);
			spawnEnemyOnPlatform(p);
		}
	}

	virtual void erasePlatforms() {
		int w, h;
		getScreenSize(w, h);

		platforms.erase(
			std::remove_if(platforms.begin(), platforms.end(),
				[&](Platform* p) {
					if (p->getCoordinates().y > h) {
						// Удаляем и из entities
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
		
		// Шанс появления врага 30%
		if (rand() % 100 > 30) return;

		Coordinates centre = p->getCentreCoordinates();
		int enemyW = 60;
		
		float enemyX = centre.x - (enemyW / 2);  // центр врага = центр платформы
		float enemyY = centre.y - 58.0f;                 // над платформой

		Enemy* e = new Enemy(enemyX, enemyY, "C:/data/enemy.png");
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

	virtual bool Tick() {
		environment->drawBackground();

		int w, h;
		getScreenSize(w, h);
		Coordinates doodlePos = doodle->getCoordinates();
		cameraMovement();

		movement();
		collision();
		doodle->fall();

		for (auto* entity : entities) {
			if (entity) entity->reDraw();
		}
		doodle->reDraw();
		std::cout << "Score: " << score << std::endl;

		return false;
	}

		virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {

		}

		virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {

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
			return "Arcanoid";
		}
	};

int main(int argc, char *argv[])
{
	return run(new MyFramework);
}
