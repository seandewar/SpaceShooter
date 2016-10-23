#pragma once

#include "Entity.h"
#include "PlayerEntity.h"


//Entity for the double fire rate power up
class DoubleFirePackEntity :
	public Entity
{
public:
	DoubleFirePackEntity(sf::Texture* healthPackTexture, sf::Vector2f pos, sf::Vector2f _velo, std::vector<sf::Texture>* fireRateExplosion, EntityManager* entityManager);
	virtual ~DoubleFirePackEntity();

	void Update(sf::Time elapsedTime, double timeDeltaMilliseconds);
	void Draw(sf::Time elapsedTime, sf::RenderWindow& window);

	void OnCollision(Entity& entity);

private:
	sf::Time _elapsedTime;
	sf::Vector2f velo;
	std::vector<sf::Texture>* fireRateExplosion;
	EntityManager* entityManagerPntr;
};

