#pragma once

#include "EntityManager.h"
#include "ProjectileEntity.h"
#include "AliveEntity.h"
#include "ExplosionEntity.h"


//The projectile for basic enemy.
class FireEnemyProjectileEntity :
	public ProjectileEntity
{
public:
	FireEnemyProjectileEntity(sf::Texture& fireProjectileTexture, EntityId owner, sf::Vector2f pos, float rotation, EntityManager* entityManager, std::vector<sf::Texture>* _explosionTextures);
	virtual ~FireEnemyProjectileEntity();

	void Update(sf::Time elapsedTime, double timeDeltaMilliseconds);
	void Draw(sf::Time elapsedTime, sf::RenderWindow& window);

	void OnCollision(Entity& entity);

	float GetRotation() const;

private:
	EntityManager* entityManagerPntr;
	std::vector<sf::Texture>* explosionTextures;

	float rotation;
};

