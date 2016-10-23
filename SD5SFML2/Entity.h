#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "EntityId.h" //This is so I can retrieve the EntityId type.


//Entity base class for our basic entity.
class Entity
{
public:
	friend class EntityManager; //This is so the EntityManager can change the id of any entity.

	typedef std::vector<std::string> stringVector;

	Entity(std::string _name);
	virtual ~Entity();

	virtual void Update(sf::Time elapsedTime, double timeDeltaMilliseconds);
	virtual void Draw(sf::Time elapsedTime, sf::RenderWindow& window);

	virtual void OnCollision(Entity& entity);
	static bool TestCollisionBetweenEntities(Entity& entity1, Entity& entity2);

	std::string GetName() const;
	EntityId GetEntityId() const;

	sf::FloatRect GetBoundingRect() const;

	bool IsCollidable() const;
	bool IsToBeDeletedNext() const;
	bool IsDrawable() const;

	bool IsType(std::string type);
	std::string GetTypeAsString();

protected:
	bool deleteNext;
	bool collidable;
	bool drawable;
	sf::FloatRect boundingRect;

	sf::Sprite sprite;

	void AddType(std::string type);

private:
	const std::string name;
	stringVector types;
	EntityId id;
};

