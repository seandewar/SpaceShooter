#pragma once

#include <iostream>
#include <vector>

#include "AliveEntity.h"
#include "EntityManager.h"
#include "FireProjectileEntity.h"


//The player entity class.
class PlayerEntity :
	public AliveEntity
{
public:
	PlayerEntity(sf::Texture& texture, sf::Texture* projectileTexture, sf::Vector2f pos, EntityManager* entityManager, std::vector<sf::Texture>* deathAnimation, 
		std::vector<sf::Texture>* explosions);
	virtual ~PlayerEntity();

	void Update(sf::Time elapsedTime, double timeDeltaMilliseconds);
	void Draw(sf::Time elapsedTime, sf::RenderWindow& window);

	void UpdateDeathAnimation(sf::Time elapsedTime);

	void Fire();

	void OnDeath();

	void SetScore(int _score);
	void AddScore(int amount);
	int GetScore() const;

	void AddDoubleFireTime(sf::Time elapsedTime, sf::Time time);
	bool IsDoubleFireActive() const;

	float GetSpeed() const;

private:
	void UpdateInput(sf::Time elapsedTime, double timeDeltaMilliseconds);
	void UpdatePlayableBounds(sf::Time elapsedTime, double timeDeltaMilliseconds);

	float speed;
	int score;

	EntityManager* entityManagerPntr;
	sf::Texture* projectileTexturePntr;
	sf::Time nextFire;
	sf::Time doubleFireTime;
	bool isDoubleFire;

	std::vector<sf::Texture>* explosionTextures;
	std::vector<sf::Texture>* playerDeathTextures;
	std::vector<sf::Texture>::iterator playerDeathTexturesIt;
	sf::Time nextDeathFrame;
};


