#include "FireEnemyProjectileEntity.h"


FireEnemyProjectileEntity::FireEnemyProjectileEntity(sf::Texture& fireProjectileTexture, EntityId owner, sf::Vector2f pos, float _rotation, EntityManager* entityManager, std::vector<sf::Texture>* _explosionTextures) :
	ProjectileEntity("FireEnemyProjectileEntity", owner, pos),
	rotation(_rotation),
	entityManagerPntr(entityManager),
	explosionTextures(_explosionTextures)
{
	AddType("FireEnemyProjectileEntity");

	boundingRect.width = 12.0f;
	boundingRect.height = 12.0f;

	sprite.setTexture(fireProjectileTexture);
}


FireEnemyProjectileEntity::~FireEnemyProjectileEntity()
{
}


void FireEnemyProjectileEntity::Update(sf::Time elapsedTime, double timeDeltaMilliseconds)
{
	boundingRect.left += sinf(3.1415926f*rotation/180) * 0.15f  * (float)timeDeltaMilliseconds;
	boundingRect.top += -cosf(3.1415926f*rotation/180) * 0.15f  * (float)timeDeltaMilliseconds;

	if(boundingRect.top < -20 ||
		boundingRect.top > 620 ||
		boundingRect.left < -20 ||
		boundingRect.left > 820)
	{
		deleteNext = true;
	}

	ProjectileEntity::Update(elapsedTime, timeDeltaMilliseconds);
}


void FireEnemyProjectileEntity::Draw(sf::Time elapsedTime, sf::RenderWindow& window)
{
	ProjectileEntity::Draw(elapsedTime, window);
}


void FireEnemyProjectileEntity::OnCollision(Entity& entity)
{
	if(TestValidCollision(entity))
	{
		if(entity.IsType("PlayerEntity"))
		{
			static_cast<AliveEntity*>(&entity)->Damage(50);
			entityManagerPntr->AddEntity(new ExplosionEntity(explosionTextures, sf::Vector2f(boundingRect.left, boundingRect.top)));

			deleteNext = true;
		}
	}
}


float FireEnemyProjectileEntity::GetRotation() const
{
	return rotation;
}