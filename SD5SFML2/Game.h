#pragma once

#include <SFML/Graphics.hpp>

#include "StateManager.h"
#include "DebugOverlayState.h"
#include "GameState.h"
#include "StateVector.h"


class StateManager;

//The main game class, handles updating, drawing and init of the game.
class Game
{
public:
	static void Run();

	static bool IsRunning();
	static bool IsExiting();

private:
	static void Load();
	static void Unload();
	static void GameLoop();
	static void Update();
	static void Draw();

	static bool running, exiting;

	static sf::RenderWindow window;
	static sf::Clock clock;
	static sf::Time elapsed;
	static sf::Time lastElapsed;

	static StateManager stateManager;

	static DebugOverlayState* debugOverlayStatePntr;
	static GameState* gameStatePntr;

	static sf::Font mainFont;
	static sf::Font courierFont;
};

