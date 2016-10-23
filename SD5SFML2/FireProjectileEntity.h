#pragma once

#include "EntityManager.h"
#include "ProjectileEntity.h"
#include "AliveEntity.h"
#include "ExplosionEntity.h"


//The class for the normal laser beam attack projectile.
class FireProjectileEntity :
	public ProjectileEntity
{
public:
	FireProjectileEntity(sf::Texture& fireProjectileTexture, EntityId owner, sf::Vector2f spawn, EntityManager* entityManager, std::vector<sf::Texture>* _explosionTextures);
	virtual ~FireProjectileEntity();

	void Update(sf::Time elapsedTime, double timeDeltaMilliseconds);
	void Draw(sf::Time elapsedTime, sf::RenderWindow& window);

	void OnCollision(Entity& entity);

private:
	EntityManager* entityManagerPntr;
	std::vector<sf::Texture>* explosionTextures;
};

