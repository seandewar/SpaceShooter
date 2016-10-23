#pragma once

#include <SFML/Graphics.hpp>
#include <string>


//A game state. States are used to create menus and even the gameplay itself.
class State
{
public:
	State(std::string _name);
	virtual ~State();

	virtual void Load() = 0;
	virtual void Unload() = 0;

	virtual void Update(sf::Time elapsedTime, double timeDeltaMilliseconds) = 0;
	virtual void Draw(sf::Time elapsedTime, sf::RenderWindow& window) = 0;

	std::string GetName() const;

	bool update; //Decides wether or not the StateManager will update the State. Public member var, maybe a get/set would be better... iunno.

private:
	const std::string name;
};