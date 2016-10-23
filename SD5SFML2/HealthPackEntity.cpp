#include "HealthPackEntity.h"


HealthPackEntity::HealthPackEntity(sf::Texture* healthPackTexture, sf::Vector2f pos, sf::Vector2f _velo, int _healAmount, std::vector<sf::Texture>* _healExplosion,
								   EntityManager* entityManager) :
	Entity("HealthPackEntity"),
	velo(_velo),
	healAmount(_healAmount),
	healExplosion(_healExplosion),
	entityManagerPntr(entityManager)
{
	AddType("HealthPackEntity");

	drawable = true;
	collidable = true;

	boundingRect.left = pos.x;
	boundingRect.top = pos.y;
	boundingRect.width = 29.0f;
	boundingRect.height = 29.0f;

	sprite.setTexture((*healthPackTexture));
}


HealthPackEntity::~HealthPackEntity()
{
}


void HealthPackEntity::Update(sf::Time elapsedTime, double timeDeltaMilliseconds)
{
	boundingRect.left += velo.x * (float)timeDeltaMilliseconds;
	boundingRect.top += velo.y * (float)timeDeltaMilliseconds;

	if(boundingRect.left < -30.0f ||
		boundingRect.left > 830.0f ||
		boundingRect.top < -50.0f ||
		boundingRect.top > 630.0f)
	{
		deleteNext = true;
	}

	Entity::Update(elapsedTime, timeDeltaMilliseconds);
}	


void HealthPackEntity::Draw(sf::Time elapsedTime, sf::RenderWindow& window)
{
	Entity::Draw(elapsedTime, window);
}

	
void HealthPackEntity::OnCollision(Entity& entity)
{
	if(entity.IsType("PlayerEntity"))
	{
		PlayerEntity* pl = static_cast<PlayerEntity*>(&entity);
			
		pl->Heal(healAmount);
		pl->AddScore(50);

		entityManagerPntr->AddEntity(new ExplosionEntity(healExplosion, sf::Vector2f(boundingRect.left - 5.0f, boundingRect.top)));

		deleteNext = true;
	}
}