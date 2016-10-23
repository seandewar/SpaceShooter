#include "ProjectileEntity.h"


ProjectileEntity::ProjectileEntity(std::string _name, EntityId _owner, sf::Vector2f spawn) :
	Entity(_name),
	owner(_owner)
{
	AddType("ProjectileEntity");

	drawable = true;
	collidable = true;

	boundingRect.left = spawn.x;
	boundingRect.top = spawn.y;
}


ProjectileEntity::~ProjectileEntity()
{
}


void ProjectileEntity::Update(sf::Time elapsedTime, double timeDeltaMilliseconds)
{
	Entity::Update(elapsedTime, timeDeltaMilliseconds);
}


void ProjectileEntity::Draw(sf::Time elapsedTime, sf::RenderWindow& window)
{
	Entity::Draw(elapsedTime, window);
}


void ProjectileEntity::OnCollision(Entity& entity)
{
}


//Checks to see whether or not the projectile has collided with the owner (do nothing in this case), and checks wether or not
//it may have collided with another projectile or non-alive entity.
//If both of these cases are not encountered, the test will return a true value.
bool ProjectileEntity::TestValidCollision(Entity& entity) const
{
	if(entity.GetEntityId() != owner &&
		!entity.IsType("ProjectileEntity") &&
		entity.IsType("AliveEntity"))
	{
		return true;
	}

	return false;
}


EntityId ProjectileEntity::GetOwner() const
{
	return owner;
}