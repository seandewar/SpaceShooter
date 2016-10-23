#include "Entity.h"


Entity::Entity(std::string _name = "Entity") :
	name(_name),
	collidable(false),
	deleteNext(false),
	drawable(false),
	id(-1)
{
	AddType("Entity");
}


Entity::~Entity()
{
}


//Updates position of sprite to that of the boundingRect by default.
void Entity::Update(sf::Time elapsedTime, double timeDeltaMilliseconds)
{
	sprite.setPosition(boundingRect.left, boundingRect.top);
}


//Draws the sprite by default.
void Entity::Draw(sf::Time elapsedTime, sf::RenderWindow& window)
{
	window.draw(sprite);
}


//Returns the id of the entity given by an EntityManager. If -1 is returned, then an id has not been given.
EntityId Entity::GetEntityId() const
{
	return id;
}


std::string Entity::GetName() const
{
	return name;
}


//Called when the entityManager detects a collision between this entity and another.
void Entity::OnCollision(Entity& entity)
{
}


//Returns true if a collision with an entity is detected. Returns false otherwise.
bool Entity::TestCollisionBetweenEntities(Entity& entity1, Entity& entity2)
{
	if(!entity1.IsCollidable() ||
		!entity2.IsCollidable())
		return false;

	//TODO Fix this - boundingbox intersect seems to always return false...
	return (entity1.GetBoundingRect().intersects(entity2.GetBoundingRect()));
}


sf::FloatRect Entity::GetBoundingRect() const
{
	return boundingRect;
}


bool Entity::IsCollidable() const
{
	return collidable;
}


bool Entity::IsDrawable() const
{
	return drawable;
}


//Wether or not the entity will be deleted by the EntityManager next manager Update() call.
bool Entity::IsToBeDeletedNext() const
{
	return deleteNext;
}


void Entity::AddType(std::string type)
{
	types.push_back(type);
}


bool Entity::IsType(std::string type)
{
	if(types.size() == 0)
		return false;

	for(stringVector::iterator it = types.begin(); it != types.end(); ++it)
	{
		if((*it) == type)
			return true;
	}

	return false;
}


std::string Entity::GetTypeAsString()
{
	std::stringstream ret;

	for(stringVector::iterator it = types.begin(); it != types.end(); ++it)
	{
		ret << (*it) << ">";
	}

	return ret.str();
}