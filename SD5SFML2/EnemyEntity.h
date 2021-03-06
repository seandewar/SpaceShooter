#pragma once

#include "AliveEntity.h"
#include "PlayerEntity.h"
#include "EntityManager.h"
#include "FireEnemyProjectileEntity.h"


//The basic enemy entity.
class EnemyEntity :
	public AliveEntity
{
public:
	EnemyEntity(sf::Texture& texture, sf::Texture* projectileTexture, sf::Vector2f pos, EntityManager* _entityManager, EntityId _playerId, sf::Time elapsedTime, std::vector<sf::Texture>* explosions, std::vector<sf::Texture>* enemyDeadTextures);
	virtual ~EnemyEntity();

	void UpdateDeathAnimation(sf::Time elapsedTime);
	void Update(sf::Time elapsedTime, double timeDeltaMilliseconds);
	void Draw(sf::Time elapsedTime, sf::RenderWindow& window);

	void FacePosition(sf::Vector2f targetPos, double timeDeltaMilliseconds);
	void FacePlayer(double timeDeltaMilliseconds);
	void Fire();

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
	sf::Texture* projectileTexturePntr;
	sf::Time nextFire;
	
	float speed;
	float rotation;
	sf::Time nextFacePlayer;
};

