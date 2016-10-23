#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"


//Base entity class for entities with health.
class AliveEntity :
	public Entity
{
public:
	friend class EntityManager;

	AliveEntity(std::string _name);
	virtual ~AliveEntity();

	virtual void Update(sf::Time elapsedTime, double timeDeltaMilliseconds);
	virtual void Draw(sf::Time elapsedTime, sf::RenderWindow& window);

	int GetHealth() const;
	int GetMaxHealth() const;
	void SetHealth(int _health);
	void Heal(int amount);
	void Damage(int amount);

	virtual void OnDeath();

	bool IsDead() const;

protected:
	int health, maxhealth;
	bool onDeathAlreadyTriggered;
};

