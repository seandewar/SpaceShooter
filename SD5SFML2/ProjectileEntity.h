#pragma once

#include "Entity.h"
#include "EntityId.h"


//Base class for projectile entities.
class ProjectileEntity :
	public Entity
{
public:
	ProjectileEntity(std::string _name, EntityId _owner, sf::Vector2f spawn);
	virtual ~ProjectileEntity();

	virtual void Update(sf::Time elapsedTime, double timeDeltaMilliseconds);
	virtual void Draw(sf::Time elapsedTime, sf::RenderWindow& window);

	virtual void OnCollision(Entity& entity);

	EntityId GetOwner() const;

protected:
	bool TestValidCollision(Entity& entity) const;

private:
	EntityId owner;
};

