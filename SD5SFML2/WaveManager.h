#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include "EntityManager.h"
#include "EnemyEntity.h"
#include "MissileEnemyEntity.h"
#include "HealthPackEntity.h"
#include "DoubleFirePackEntity.h"


//Handles waves
class WaveManager
{
public:
	WaveManager(EntityManager* entityManager, EntityId playerId, sf::Texture* enemyTexture, sf::Texture* fireEnemyProjectileTexture, std::vector<sf::Texture>* explosionTextures,
		std::vector<sf::Texture>* enemyDeadTextures, sf::Texture* healthPackTexture, std::vector<sf::Texture>* healExplosionTexture, sf::Texture* missileEnemy,
		std::vector<sf::Texture>* missileDeadTextures, sf::Texture* fireRateTexture);
	~WaveManager();

	void Update(sf::Time elapsedTime, double timeDeltaMilliseconds);

	bool CheckEntityAmount();
	void UpdateWave(sf::Time elapsedTime);
	void StartWave(int wave, sf::Time elapsedTime);
	void UseSpawnToken(sf::Time elapsedTime);
	
	int GetCurrentWave() const;
	int GetSpawnTokensThisWave() const;
	int GetSpawnTokensLeft() const;

	void SetPlayerId(EntityId _playerId);

	int GetMaxAmountOnScreen() const;

private:
	int currentWave;
	int spawnTokensThisWave, spawnTokensLeft;
	int maxAmountOnScreenThisWave;
	const int maxAmountOnScreenCap;
	int timeSpawnTokenUsageMilliseconds, timeSpawnTokenUsageBiasMilliseconds;
	const int timeSpawnTokenUsageCapMilliseconds, timeSpawnTokenUsageBiasCapMilliseconds;

	sf::Time nextSpawnTokenUsage;

	EntityManager* entityManagerPntr;
	EntityId playerId;

	sf::Texture* enemyTexture;
	sf::Texture* missileEnemy;
	sf::Texture* fireEnemyProjectileTexture;
	std::vector<sf::Texture>* explosionTextures;
	std::vector<sf::Texture>* enemyDeadTextures;
	std::vector<sf::Texture>* healExplosionTexture;
	std::vector<sf::Texture>* missileDeadTextures;

	sf::Texture* healthPackTexture;
	sf::Texture* fireRateTexture;
};

