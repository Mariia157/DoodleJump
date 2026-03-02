
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
	float cameraOffset = 0.0f;
public:



	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		int userW = 0;
		int userH = 0;
		std::cout << "Enter window width: ";
		std::cin >> userW;
		std::cout << std::endl << "Enter window height: ";
		std::cin >> userH;
		std::cout << std::endl;
		width = userW;
		height = userH;

		fullscreen = false;
	}

	virtual bool Init() {

		doodle = new Player();
		environment = new Environment();
		// Создаём платформы
		platforms.push_back(new Platform(50, 150, "C:/data/platform.png"));
		platforms.push_back(new Platform(150, 120, "C:/data/platform.png"));
		platforms.push_back(new Platform(250, 90, "C:/data/platform.png"));

		doodle->setPlatforms(platforms);

		doodle->setPlatforms(platforms);  // передаём список
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
			doodle->setCoordinates(Coordinates(curCoordinates.x, h / 2));

			// Двигаем все платформы вниз
			for (auto* p : platforms) {
				Coordinates pos = p->getCoordinates();
				pos.y += shift;
				p->setCoordinates(pos);
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
			doodle->reDraw();

			return false;
		}
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
