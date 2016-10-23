#include "ExplosionEntity.h"


ExplosionEntity::ExplosionEntity(std::vector<sf::Texture>* explosionTextures, sf::Vector2f pos) :
	Entity("ExplosionEntity"),
	explosionTexturesPntr(explosionTextures)
{
	AddType("ExplosionEntity");

	drawable = true;

	boundingRect.left = pos.x;
	boundingRect.top = pos.y;

	explosionTexturesIt = explosionTexturesPntr->begin();
}


ExplosionEntity::~ExplosionEntity()
{
}


void ExplosionEntity::Update(sf::Time elapsedTime, double timeDeltaMilliseconds)
{
	if(elapsedTime < nextFrame)
		return;

	if(explosionTexturesIt == explosionTexturesPntr->end())
	{
		drawable = false;
		deleteNext = true;
		return;
	}

	sprite.setTexture((*explosionTexturesIt));
	++explosionTexturesIt;

	nextFrame = elapsedTime + sf::milliseconds(100);

	Entity::Update(elapsedTime, timeDeltaMilliseconds);
}


void ExplosionEntity::Draw(sf::Time elapsedTime, sf::RenderWindow& window)
{
	Entity::Draw(elapsedTime, window);
}