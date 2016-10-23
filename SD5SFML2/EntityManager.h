#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

#include "Entity.h"
#include "EntityId.h"
#include "AliveEntity.h"


class Entity;

//Stores all the entities and manages them.
class EntityManager
{
public:
	typedef std::map<EntityId, Entity*> entityMap;

	EntityManager(sf::Font& debugFont);
	~EntityManager();

	EntityId AddEntity(Entity* entity);
	void RemoveEntity(EntityId id);

	Entity* GetEntity(EntityId id);

	void Update(sf::Time elapsedTime, double timeDeltaMilliseconds);
	void Draw(sf::Time elapsedTime, sf::RenderWindow& window);

	int GetLastDrawnEntities() const;
	int GetEntityCount() const;
	int GetParticularEntityCount(std::string type);

	void SetDebugMode(bool _debug);
	bool IsDebugMode() const;

private:
	entityMap::iterator EraseEntity(entityMap::const_iterator it);

	entityMap entities;
	EntityId nextId;

	bool debug;
	sf::Font* debugFontPntr;

	int drawnEntities;
};

