#include "FireProjectileEntity.h"


FireProjectileEntity::FireProjectileEntity(sf::Texture& fireProjectileTexture, EntityId owner, sf::Vector2f spawn, EntityManager* entityManager, std::vector<sf::Texture>* _explosionTextures) :
	ProjectileEntity("FireProjectileEntity", owner, spawn),
	entityManagerPntr(entityManager),
	explosionTextures(_explosionTextures)
{
	AddType("FireProjectileEntity");

	boundingRect.width = 7.0f;
	boundingRect.height = 19.0f;

	sprite.setTexture(fireProjectileTexture);
}


FireProjectileEntity::~FireProjectileEntity()
{
}


void FireProjectileEntity::Update(sf::Time elapsedTime, double timeDeltaMilliseconds)
{
	boundingRect.top -= 0.8f * (float)timeDeltaMilliseconds;

	if(boundingRect.top < -20)
	{
		deleteNext = true;
	}

	ProjectileEntity::Update(elapsedTime, timeDeltaMilliseconds);
}


void FireProjectileEntity::Draw(sf::Time elapsedTime, sf::RenderWindow& window)
{
	ProjectileEntity::Draw(elapsedTime, window);
}


void FireProjectileEntity::OnCollision(Entity& entity)
{
	if(TestValidCollision(entity))
	{
		static_cast<AliveEntity*>(&entity)->Damage(50);
		entityManagerPntr->AddEntity(new ExplosionEntity(explosionTextures, sf::Vector2f(boundingRect.left, boundingRect.top)));

		deleteNext = true;
	}
}