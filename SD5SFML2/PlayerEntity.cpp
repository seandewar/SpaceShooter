#include "PlayerEntity.h"


PlayerEntity::PlayerEntity(sf::Texture& texture, sf::Texture* projectileTexture, sf::Vector2f pos, EntityManager* entityManager, std::vector<sf::Texture>* deathAnimation, std::vector<sf::Texture>* explosions) :
	AliveEntity("PlayerEntity"),
	score(0),
	speed(1.0f),
	entityManagerPntr(entityManager),
	projectileTexturePntr(projectileTexture),
	playerDeathTextures(deathAnimation),
	explosionTextures(explosions),
	isDoubleFire(false)
{
	AddType("PlayerEntity");

	health = maxhealth = 1000;
	collidable = true;
	drawable = true;

	boundingRect.left = pos.x;
	boundingRect.top = pos.y;
	boundingRect.width = 50.0f;
	boundingRect.height = 50.0f;

	sprite.setTexture(texture);

	entityManagerPntr = entityManager;

	playerDeathTexturesIt = playerDeathTextures->begin();
}


PlayerEntity::~PlayerEntity()
{
}


void PlayerEntity::Fire()
{
	entityManagerPntr->AddEntity(new FireProjectileEntity((*projectileTexturePntr), GetEntityId(), sf::Vector2f(boundingRect.left + 8, boundingRect.top), entityManagerPntr, explosionTextures));
	entityManagerPntr->AddEntity(new FireProjectileEntity((*projectileTexturePntr), GetEntityId(), sf::Vector2f(boundingRect.left + 35, boundingRect.top), entityManagerPntr, explosionTextures));
}


bool PlayerEntity::IsDoubleFireActive() const
{
	return isDoubleFire;
}


void PlayerEntity::AddDoubleFireTime(sf::Time elapsedTime, sf::Time time)
{
	doubleFireTime = elapsedTime + time;
}


void PlayerEntity::UpdateInput(sf::Time elapsedTime, double timeDeltaMilliseconds)
{
	isDoubleFire = (elapsedTime <= doubleFireTime);

	sf::Vector2f velocity;
	velocity.x = velocity.y = 0.0f;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.y -= 0.35f;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity.y += 0.35f;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x -= 0.35f;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x += 0.35f;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if(elapsedTime >= nextFire)
		{
			Fire();

			if(!isDoubleFire)
				nextFire = elapsedTime + sf::milliseconds(333);
			else
				nextFire = elapsedTime + sf::milliseconds(167);
		}
	}

	velocity.x *= (float)timeDeltaMilliseconds;
	velocity.y *= (float)timeDeltaMilliseconds;

	velocity.x *= speed;
	velocity.y *= speed;

	boundingRect.left += velocity.x;
	boundingRect.top += velocity.y;
}


void PlayerEntity::UpdatePlayableBounds(sf::Time elapsedTime, double timeDeltaMilliseconds)
{
	if(boundingRect.left < 0)
	{
		boundingRect.left = 0;
	}
	else if(boundingRect.left > 750)
	{
		boundingRect.left = 750;
	}

	if(boundingRect.top < 0)
	{
		boundingRect.top = 0;
	}
	else if(boundingRect.top > 550)
	{
		boundingRect.top = 550;
	}
}


void PlayerEntity::UpdateDeathAnimation(sf::Time elapsedTime)
{
	if(elapsedTime < nextDeathFrame)
		return;

	if(playerDeathTexturesIt == playerDeathTextures->end())
	{
		drawable = false;
		return;
	}

	sprite.setTexture((*playerDeathTexturesIt));
	++playerDeathTexturesIt;

	nextDeathFrame = elapsedTime + sf::milliseconds(100);
}


void PlayerEntity::Update(sf::Time elapsedTime, double timeDeltaMilliseconds)
{
	if(!IsDead())
	{
		UpdateInput(elapsedTime, timeDeltaMilliseconds);
		UpdatePlayableBounds(elapsedTime, timeDeltaMilliseconds);
	}
	else
	{
		UpdateDeathAnimation(elapsedTime);
	}

	AliveEntity::Update(elapsedTime, timeDeltaMilliseconds);
}


void PlayerEntity::Draw(sf::Time elapsedTime, sf::RenderWindow& window)
{
	AliveEntity::Draw(elapsedTime, window);
}


void PlayerEntity::OnDeath()
{
	std::cout << "Player has died with " << score << " score! (PlayerEntity::OnDeath())" << std::endl;

	collidable = false;
}


void PlayerEntity::SetScore(int _score)
{
	score = _score;
}


void PlayerEntity::AddScore(int amount)
{
	score += amount;
}


int PlayerEntity::GetScore() const
{
	return score;
}


float PlayerEntity::GetSpeed() const
{
	return speed;
}