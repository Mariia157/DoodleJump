
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
	float cameraOffset = 0.0f;
public:



	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		/*int userW = 0;
		int userH = 0;
		std::cout << "Enter window width: ";
		std::cin >> userW;
		std::cout << std::endl << "Enter window height: ";
		std::cin >> userH;
		std::cout << std::endl;
		width = userW;
		height = userH;*/
		width = 600;
		height = 800;

		fullscreen = false;
	}

	virtual bool Init() {

		doodle = new Player();
		environment = new Environment();
		// Создаём платформы
		platforms.push_back(new Platform(250, 700, "C:/data/achievements.png"));
		platforms.push_back(new Platform(300, 650, "C:/data/achievements.png"));
		platforms.push_back(new Platform(250, 90, "C:/data/achievements.png"));

		//doodle->setPlatforms(platforms);  // передаём список
		entities.push_back(doodle);
		for (auto* p : platforms) {
			entities.push_back(p);
		}
		return true;
	}

	virtual void Close() {
		delete doodle;
	}

	virtual bool Tick() {
		environment->drawBackground();
		Coordinates curCoordinates = doodle->getCoordinates();
		int w, h;
		int doodleH = doodle->getDoodleH();
		bool isFall = doodle->getIsFall();
		getScreenSize(w, h);

		// Камера двигается только вверх
		if (curCoordinates.y < h / 2) {
			float shift = h / 2 - curCoordinates.y;
			cameraOffset += shift;

			// Двигаем игрока вниз
			/*doodle->setCoordinates(Coordinates(curCoordinates.x, h / 2));*/
		}
				
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
		if (!isFall) {
			doodle->jump();

		}
		doodle->fall();
		for (auto* entity : entities) {
			if (!entity) continue;
			Player* player = static_cast<Player*>(entity);
			if (player) {
				for (auto* entityOther : entities) {
					if (player == entityOther) continue;
					if (player->onCollided(entityOther)) {
						std::cout << "Collided!" << std::endl;
					}
				}
			}
			entity->reDraw();

		}

		
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
