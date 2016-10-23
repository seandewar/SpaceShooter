#pragma once

#include "Entity.h"
#include "PlayerEntity.h"


//The class for health packs.
class HealthPackEntity :
	public Entity
{
public:
	HealthPackEntity(sf::Texture* healthPackTexture, sf::Vector2f pos, sf::Vector2f _velo, int _healAmount, std::vector<sf::Texture>* healExplosion, EntityManager* entityManager);
	virtual ~HealthPackEntity();

	void Update(sf::Time elapsedTime, double timeDeltaMilliseconds);
	void Draw(sf::Time elapsedTime, sf::RenderWindow& window);

	void OnCollision(Entity& entity);

private:
	sf::Vector2f velo;
	int healAmount;
	std::vector<sf::Texture>* healExplosion;
	EntityManager* entityManagerPntr;
};

