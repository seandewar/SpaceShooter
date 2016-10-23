#include "MissileEnemyEntity.h"


MissileEnemyEntity::MissileEnemyEntity(sf::Texture& texture, sf::Vector2f pos, EntityManager* _entityManager, EntityId _playerId, std::vector<sf::Texture>* explosions, 
		std::vector<sf::Texture>* enemyDeadTextures) :
	AliveEntity("MissileEnemyEntity"),
	playerId(_playerId),
	rotation(0.0f),
	speed(1.0f),
	explosionTextures(explosions),
	enemyDeadTexturesPntr(enemyDeadTextures)
{
	AddType("MissileEnemyEntity");

	health = maxhealth = 25;
	collidable = true;
	drawable = true;

	boundingRect.left = pos.x;
	boundingRect.top = pos.y;
	boundingRect.width = 24.0f;
	boundingRect.height = 53.0f;

	sprite.setTexture(texture);
	sprite.setOrigin(12.0f, 26.5f);

	entityManagerPntr = _entityManager;

	enemyDeadTexturesIt = enemyDeadTexturesPntr->begin();
}


MissileEnemyEntity::~MissileEnemyEntity()
{
}


void MissileEnemyEntity::FacePosition(sf::Vector2f targetPos, double timeDeltaMilliseconds)
{
	sf::Vector2f pos(boundingRect.left, boundingRect.top);

	float a = targetPos.x - pos.x;
	float b = targetPos.y - pos.y;

	//Convert to degrees.
	float angle = (atan2f(b, a)*180/3.1415926f) + 90.0f;

	rotation = angle;
}


void MissileEnemyEntity::FacePlayer(double timeDeltaMilliseconds)
{
	sf::Vector2f playerPos(entityManagerPntr->GetEntity(playerId)->GetBoundingRect().left + 25.0f, entityManagerPntr->GetEntity(playerId)->GetBoundingRect().top + 25.0f);

	FacePosition(playerPos, timeDeltaMilliseconds);
}


void MissileEnemyEntity::UpdateDeathAnimation(sf::Time elapsedTime)
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


void MissileEnemyEntity::Update(sf::Time elapsedTime, double timeDeltaMilliseconds)
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
		FacePlayer(timeDeltaMilliseconds);

		//Move towards facing position
		boundingRect.left += sinf(3.1415926f*rotation/180) * 0.24f * speed * (float)timeDeltaMilliseconds;
		boundingRect.top += -cosf(3.1415926f*rotation/180) * 0.24f * speed * (float)timeDeltaMilliseconds;

		//Update the position of the sprite.
		sprite.setPosition(boundingRect.left + 12.0f, boundingRect.top + 26.5f);
		sprite.setRotation(rotation);

		//The last line is commented so Entity doesn't reset the sprite position, as it will make it off-center due to the custom origin
		//AliveEntity::Update(elapsedTime, timeDeltaMilliseconds)
	}
}


void MissileEnemyEntity::Draw(sf::Time elapsedTime, sf::RenderWindow& window)
{
	AliveEntity::Draw(elapsedTime, window);
}


void MissileEnemyEntity::OnCollision(Entity& entity)
{
	if(entity.IsType("PlayerEntity"))
	{
		//If the ship crashes into the player, punish the player by damaging 1/4 of health... ON PURPOSE!
		static_cast<AliveEntity*>(&entity)->Damage(250);
		entityManagerPntr->AddEntity(new ExplosionEntity(explosionTextures, sf::Vector2f(boundingRect.left + 17.5f, boundingRect.top + 17.5f)));

		health = 0;
	}
}


void MissileEnemyEntity::OnDeath()
{
	collidable = false;

	static_cast<PlayerEntity*>(entityManagerPntr->GetEntity(playerId))->AddScore(500);
}


float MissileEnemyEntity::GetRotation() const
{
	return rotation;
}