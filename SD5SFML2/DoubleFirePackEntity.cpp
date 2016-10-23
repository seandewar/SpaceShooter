#include "DoubleFirePackEntity.h"


DoubleFirePackEntity::DoubleFirePackEntity(sf::Texture* firePackTexture, sf::Vector2f pos, sf::Vector2f _velo, std::vector<sf::Texture>* _fireRateExplosion, 
										   EntityManager* entityManager) :
	Entity("DoubleFirePackEntity"),
	velo(_velo),
	fireRateExplosion(_fireRateExplosion),
	entityManagerPntr(entityManager)
{
	AddType("DoubleFirePackEntity");

	drawable = true;
	collidable = true;

	boundingRect.left = pos.x;
	boundingRect.top = pos.y;
	boundingRect.width = 29.0f;
	boundingRect.height = 29.0f;

	sprite.setTexture((*firePackTexture));
}


DoubleFirePackEntity::~DoubleFirePackEntity()
{
}

void DoubleFirePackEntity::Update(sf::Time elapsedTime, double timeDeltaMilliseconds)
{
	_elapsedTime = elapsedTime;

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


void DoubleFirePackEntity::Draw(sf::Time elapsedTime, sf::RenderWindow& window)
{
	Entity::Draw(elapsedTime, window);
}

	
void DoubleFirePackEntity::OnCollision(Entity& entity)
{
	if(entity.IsType("PlayerEntity"))
	{
		PlayerEntity* pl = static_cast<PlayerEntity*>(&entity);
			
		pl->AddDoubleFireTime(_elapsedTime, sf::milliseconds(10000));
		pl->AddScore(50);

		entityManagerPntr->AddEntity(new ExplosionEntity(fireRateExplosion, sf::Vector2f(boundingRect.left - 5.0f, boundingRect.top)));

		deleteNext = true;
	}
}