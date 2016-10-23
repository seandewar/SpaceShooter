#include "EntityManager.h"


EntityManager::EntityManager(sf::Font& debugFont) :
	nextId(0),
	drawnEntities(0),
	debug(false),
	debugFontPntr(&debugFont)
{
	std::cout << "EntityManager::EntityManager() construct" << std::endl;
}


EntityManager::~EntityManager()
{
	std::cout << "EntityManager::~EntityManager() destruct" << std::endl;

	entities.clear();
}


EntityId EntityManager::AddEntity(Entity* entity)
{
	entities[nextId] = entity;
	entities[nextId]->id = nextId;
	++nextId;

	return (nextId-1);
}


EntityManager::entityMap::iterator EntityManager::EraseEntity(entityMap::const_iterator it)
{
	delete (*it).second;
	return entities.erase(it);
}


void EntityManager::RemoveEntity(EntityId id)
{
	EraseEntity(entities.find(id));
}


Entity* EntityManager::GetEntity(EntityId id)
{
	return entities[id];
}


void EntityManager::Update(sf::Time elapsedTime, double timeDeltaMilliseconds)
{
	if(entities.size() == 0)
		return;

	//Call update on all of the entities, and handle OnDeath, OnCollide and stuff
	entityMap::iterator it = entities.begin();
	while(it != entities.end())
	{
		//If the entity is to be deleted next, delete the dynamic pointer and erase it, the get the valid it from erase.
		if((*it).second->IsToBeDeletedNext())
		{
			it = EraseEntity(it);
			continue;
		}
		
		//Loop through entities to check for collisions.
		for(entityMap::iterator it2 = entities.begin(); it2 != entities.end(); ++it2)
		{
			//Dont check for collisions with self - that's stupid.
			if(it->first == it2->first)
				continue;

			//Check for a collision.
			if(Entity::TestCollisionBetweenEntities((*it->second), (*it2->second)))
			{
				//Only fire the OnCollide of it, so we don't get duplicates (as the loop will eventually check it2).
				(*it).second->OnCollision((*it2->second));
			}
		}

		//Now check the health of the it for AliveEntity's OnDead event.
		if((*it).second->IsType("AliveEntity"))
		{
			AliveEntity* ent = static_cast<AliveEntity*>((*it).second);

			if(ent->IsDead() &&
				!ent->onDeathAlreadyTriggered)
			{
				ent->OnDeath();
				ent->onDeathAlreadyTriggered = true;
			}
			else if(ent->onDeathAlreadyTriggered &&
				!ent->IsDead())
			{
				//Reset the trigger on OnDeath. This is for a ressurection feature which might be added.
				ent->onDeathAlreadyTriggered = false;
			}
		}

		//Finally, call Update() on the entity.
		(*it).second->Update(elapsedTime, timeDeltaMilliseconds);

		++it;
	}
}


void EntityManager::Draw(sf::Time elapsedTime, sf::RenderWindow& window)
{
	if(entities.size() == 0)
		return;

	int drawn = 0;

	//Loop through all of the entities and draw them if drawable is set to true.
	for(entityMap::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		if((*it).second->drawable)
		{
			(*it).second->Draw(elapsedTime, window);
			++drawn;

			if(debug)
			{
				sf::RectangleShape rs;
				rs.setSize(sf::Vector2f((*it).second->GetBoundingRect().width, (*it).second->GetBoundingRect().height));
				rs.setPosition(sf::Vector2f(ceilf((*it).second->GetBoundingRect().left), ceilf((*it).second->GetBoundingRect().top)));
				rs.setOutlineColor(sf::Color::Red);
				rs.setFillColor(sf::Color::Transparent);
				rs.setOutlineThickness(2.0f);

				sf::Text info;
				info.setFont((*debugFontPntr));
				info.setCharacterSize(12);
				info.setPosition(sf::Vector2f((*it).second->GetBoundingRect().left, (*it).second->GetBoundingRect().top - 60.0f));
				
				std::stringstream infoText;
				infoText << "EntityId: " << (*it).second->GetEntityId() << std::endl;
				infoText << "BoundingRect Pos: (" << (*it).second->GetBoundingRect().left << ", " << (*it).second->GetBoundingRect().top << ")" << " Size: (" << (*it).second->GetBoundingRect().width << ", " << (*it).second->GetBoundingRect().height << ")" << std::endl;
				infoText << "Types: " << (*it).second->GetTypeAsString() << std::endl;

				if((*it).second->IsType("AliveEntity"))
				{
					AliveEntity* al = static_cast<AliveEntity*>((*it).second);

					infoText << std::endl << "AliveEntity Health/Maxhealth: " << al->GetHealth() << "/" << al->GetMaxHealth() << std::endl;
				}

				info.setString(infoText.str());

				window.draw(rs);
				window.draw(info);
			}
		}
	}

	drawnEntities = drawn;
}


//Returns the number of entities drawn on the last Draw() call.
int EntityManager::GetLastDrawnEntities() const
{
	return drawnEntities;
}


int EntityManager::GetEntityCount() const
{
	return entities.size();
}


void EntityManager::SetDebugMode(bool _debug)
{
	debug = _debug;
}


bool EntityManager::IsDebugMode() const
{
	return debug;
}


int EntityManager::GetParticularEntityCount(std::string type)
{
	int count = 0;

	for(entityMap::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		if((*it).second->IsType(type))
			++count;
	}

	return count;
}