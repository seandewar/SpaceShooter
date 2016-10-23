#include "AliveEntity.h"


AliveEntity::AliveEntity(std::string _name = "AliveEntity") :
	Entity(_name),
	health(0),
	maxhealth(0),
	onDeathAlreadyTriggered(false)
{
	AddType("AliveEntity");
}


AliveEntity::~AliveEntity()
{
}


void AliveEntity::Update(sf::Time elapsedTime, double timeDeltaMilliseconds)
{
	Entity::Update(elapsedTime, timeDeltaMilliseconds);
}


void AliveEntity::Draw(sf::Time elapsedTime, sf::RenderWindow& window)
{
	Entity::Draw(elapsedTime, window);
}


int AliveEntity::GetHealth() const
{
	return health;
}


int AliveEntity::GetMaxHealth() const
{
	return maxhealth;
}


void AliveEntity::SetHealth(int _health)
{
	health = _health;
}


void AliveEntity::Heal(int amount)
{
	health += amount;

	if(health > maxhealth)
		health = maxhealth;
}


void AliveEntity::Damage(int amount)
{
	health -= amount;

	if(health < 0)
		health = 0;
}


void AliveEntity::OnDeath()
{
}


bool AliveEntity::IsDead() const
{
	return (health <= 0);
}