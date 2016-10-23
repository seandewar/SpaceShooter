#pragma once

#include "AliveEntity.h"
#include "PlayerEntity.h"


//Entity class for the suicide missle enemy.
class MissileEnemyEntity :
	public AliveEntity
{
public:
	MissileEnemyEntity(sf::Texture& texture, sf::Vector2f pos, EntityManager* _entityManager, EntityId _playerId, std::vector<sf::Texture>* explosions, 
		std::vector<sf::Texture>* enemyDeadTextures);
	virtual ~MissileEnemyEntity();

	void UpdateDeathAnimation(sf::Time elapsedTime);
	void Update(sf::Time elapsedTime, double timeDeltaMilliseconds);
	void Draw(sf::Time elapsedTime, sf::RenderWindow& window);

	void FacePosition(sf::Vector2f targetPos, double timeDeltaMilliseconds);
	void FacePlayer(double timeDeltaMilliseconds);

	void OnCollision(Entity& entity);
	void OnDeath();

	float GetRotation() const;

private:
	EntityManager* entityManagerPntr;
	EntityId playerId;

	std::vector<sf::Texture>* enemyDeadTexturesPntr;
	std::vector<sf::Texture>::iterator enemyDeadTexturesIt;
	sf::Time nextDeathFrame;

	std::vector<sf::Texture>* explosionTextures;
	
	float speed;
	float rotation;
};

