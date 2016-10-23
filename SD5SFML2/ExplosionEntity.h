#pragma once

#include "Entity.h"


//The class for explosion entities for on hit effects and such.
class ExplosionEntity :
	public Entity
{
public:
	ExplosionEntity(std::vector<sf::Texture>* explosionTextures, sf::Vector2f pos);
	virtual ~ExplosionEntity();

	void Update(sf::Time elapsedTime, double timeDeltaMilliseconds);
	void Draw(sf::Time elapsedTime, sf::RenderWindow& window);

private:
	std::vector<sf::Texture>* explosionTexturesPntr;
	std::vector<sf::Texture>::iterator explosionTexturesIt;
	sf::Time nextFrame;
};

