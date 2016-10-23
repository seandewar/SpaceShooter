#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Game.h"
#include "State.h"
#include "StateVector.h"


//Handles the update and drawing of states.
class StateManager
{
public:
	StateManager(sf::Time elapsedTime);
	~StateManager();

	void Update(sf::Time elapsedTime, double timeDeltaMilliseconds);
	void Draw(sf::Time elapsedTime, sf::RenderWindow& window);

	stateVector::const_iterator InsertState(stateVector::const_iterator position, State* state);
	stateVector::iterator EraseState(stateVector::iterator position);
	void EraseAllStates();
	stateVector::const_iterator PushStateBack(State* state);
	void PopStateBack();

	stateVector::size_type GetStateCount() const;
	int GetFrameRate() const;
	double GetAverageDrawTimeMilliseconds() const;

private:
	void ResetFrameRate(sf::Time elapsedTime);
	void UpdateFrameRate(sf::Time elapsedTime);

	stateVector states;

	int fps, framesCounted;
	sf::Time timeNextFrame;
};