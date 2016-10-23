#include "EnemyEntity.h"


EnemyEntity::EnemyEntity(sf::Texture& texture, sf::Texture* projectileTexture, sf::Vector2f pos, EntityManager* entityManager, EntityId _playerId, sf::Time elapsedTime, std::vector<sf::Texture>* explosions, std::vector<sf::Texture>* enemyDeadTextures) :
	AliveEntity("EnemyEntity"),
	playerId(_playerId),
	rotation(0.0f),
	speed(1.0f),
	explosionTextures(explosions),
	enemyDeadTexturesPntr(enemyDeadTextures)
{
	AddType("EnemyEntity");

	health = maxhealth = 100;
	collidable = true;
	drawable = true;

	boundingRect.left = pos.x;
	boundingRect.top = pos.y;
	boundingRect.width = 35.0f;
	boundingRect.height = 35.0f;

	sprite.setTexture(texture);
	sprite.setOrigin(17.5f, 17.5f);

	entityManagerPntr = entityManager;

	projectileTexturePntr = projectileTexture;

	nextFire = elapsedTime + sf::milliseconds(rand()%2500+2000);

	enemyDeadTexturesIt = enemyDeadTexturesPntr->begin();
}


EnemyEntity::~EnemyEntity()
{
}


void EnemyEntity::FacePosition(sf::Vector2f targetPos, double timeDeltaMilliseconds)
{
	sf::Vector2f pos(boundingRect.left, boundingRect.top);

	float a = targetPos.x - pos.x;
	float b = targetPos.y - pos.y;

	//Convert to degrees.
	float angle = (atan2f(b, a)*180/3.1415926f) + 90.0f;

	rotation = angle;
}


void EnemyEntity::FacePlayer(double timeDeltaMilliseconds)
{
	sf::Vector2f playerPos(entityManagerPntr->GetEntity(playerId)->GetBoundingRect().left + 25.0f, entityManagerPntr->GetEntity(playerId)->GetBoundingRect().top + 25.0f);

	FacePosition(playerPos, timeDeltaMilliseconds);
}


void EnemyEntity::UpdateDeathAnimation(sf::Time elapsedTime)
{
	if(elapsedTime < nextDeathFrame)
		return;

	if(enemyDeadTexturesIt == enemyDeadTexturesPntr->end())
	{
		drawable = false;
		deleteNext = true;
		return;
	}

	sprite.setTexture((*enemyDeadTexturesIt));
	++enemyDeadTexturesIt;

	nextDeathFrame = elapsedTime + sf::milliseconds(100);
}


void EnemyEntity::Update(sf::Time elapsedTime, double timeDeltaMilliseconds)
{
	//if(static_cast<AliveEntity*>(entityManagerPntr->GetEntity(playerId))->IsDead())
	//	return;

	if(IsDead())
	{
		UpdateDeathAnimation(elapsedTime);
	}
	else
	{
		//Face the player
		if(elapsedTime >= nextFacePlayer)
		{
			if(rand()%5 == 0)
			{
				FacePosition(sf::Vector2f((float)(rand()%800), (float)(rand()%600)), timeDeltaMilliseconds);
			}
			else
			{
				FacePlayer(timeDeltaMilliseconds);
			}

			nextFacePlayer = elapsedTime + sf::milliseconds(100+rand()%2000);
		}

		if(elapsedTime >= nextFire)
		{
			Fire();

			nextFire = elapsedTime + sf::milliseconds(rand()%2500+2000);
		}

		//Move towards facing position
		boundingRect.left += sinf(3.1415926f*rotation/180) * 0.08f * speed * (float)timeDeltaMilliseconds;
		boundingRect.top += -cosf(3.1415926f*rotation/180) * 0.08f * speed * (float)timeDeltaMilliseconds;

		//Update the position of the sprite.
		sprite.setPosition(boundingRect.left + 17.5f, boundingRect.top + 17.5f);
		sprite.setRotation(rotation);

		//The last line is commented so Entity doesn't reset the sprite position, as it will make it off-center due to the custom origin
		//AliveEntity::Update(elapsedTime, timeDeltaMilliseconds)
	}
}


void EnemyEntity::Draw(sf::Time elapsedTime, sf::RenderWindow& window)
{
	AliveEntity::Draw(elapsedTime, window);
}


void EnemyEntity::Fire()
{
	entityManagerPntr->AddEntity(new FireEnemyProjectileEntity((*projectileTexturePntr), GetEntityId(), sf::Vector2f(boundingRect.left + 17.5f, boundingRect.top + 17.5f), rotation, entityManagerPntr, explosionTextures));
}


void EnemyEntity::OnCollision(Entity& entity)
{
	if(entity.IsType("PlayerEntity"))
	{
		//If the ship crashes into the player, punish the player by damaging 1/4 of health, but blow this ship up for being n00b.
		static_cast<AliveEntity*>(&entity)->Damage(250);
		entityManagerPntr->AddEntity(new ExplosionEntity(explosionTextures, sf::Vector2f(boundingRect.left + 17.5f, boundingRect.top + 17.5f)));

		health = 0;
	}
}


void EnemyEntity::OnDeath()
{
	collidable = false;

	static_cast<PlayerEntity*>(entityManagerPntr->GetEntity(playerId))->AddScore(100);
}


float EnemyEntity::GetRotation() const
{
	return rotation;
}