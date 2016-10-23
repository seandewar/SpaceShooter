#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

#include "StateManager.h"
#include "State.h"


class StateManager;
class GameState;

//This state shows debug information over the game such as the frame rate.
class DebugOverlayState :
	public State
{
public:
	DebugOverlayState(StateManager* stateManager, sf::Font& font);
	~DebugOverlayState();

	void SetGameState(GameState* gameState);
	void ResetGameState();

	void Load();
	void Unload();

	void Update(sf::Time elapsedTime, double timeDeltaMilliseconds);
	void Draw(sf::Time elapsedTime, sf::RenderWindow& window);

private:
	sf::Text debugText;
	StateManager* stateManagerPntr;
	GameState* gameStatePntr;
};

