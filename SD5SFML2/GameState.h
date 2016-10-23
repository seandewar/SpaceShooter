#pragma once

#include <iostream>

#include "State.h"
#include "EntityManager.h"
#include "EntityId.h"
#include "PlayerEntity.h"
#include "EnemyEntity.h"
#include "WaveManager.h"


//The main game state, which handles all of the gameplay.
class GameState :
	public State
{
friend class DebugOverlayState; //So we can get information about how many entities are in play .etc for debug
friend class WaveManager; 

public:
	GameState(sf::Font& font);
	~GameState();

	void Load();
	void Unload();

	void Update(sf::Time elapsedTime, double timeDeltaMilliseconds);
	void Draw(sf::Time elapsedTime, sf::RenderWindow& window);

private:
	void LoadBackground();
	void UpdateBackground(sf::Time elapsedTime, double timeDeltaMilliseconds);
	void DrawBackground(sf::RenderWindow& window);

	void LoadStars();
	void UpdateStars(sf::Time elapsedTime, double timeDeltaMilliseconds);
	void DrawStars(sf::RenderWindow& window);

	void UpdateScore();
	void DrawScore(sf::RenderWindow& window);

	void UpdateWaveCount();
	void DrawWaveCount(sf::RenderWindow& window);

	void UpdateWaveUpdate(sf::Time elapsedTime);
	void DrawWaveUpdate(sf::Time elapsedTime, sf::RenderWindow& window);

	void UpdateResult();
	void DrawResult(sf::RenderWindow& window);

	void UpdateHealth();
	void DrawHealth(sf::RenderWindow& window);

	void UpdateDoubleFire();
	void DrawDoubleFire(sf::RenderWindow& window);

	void LoadPlayer();
	void AddPlayer();
	void RemovePlayer();

	void InitWaveManager();
	void UnloadWaveManager();

	void LoadExplosionEffect();

	void AddEnemy(sf::Vector2f pos, sf::Time elapsedTime);
	void LoadEnemy();

	EntityManager entityManager;
	WaveManager* waveManager;
	bool waveStarted;
	sf::Time nextF1Press;

	sf::RectangleShape gameOverBackground;
	sf::Text gameOverText;
	sf::Text gameOverStats;

	sf::Texture playerTexture;
	sf::Texture fireProjectileTexture;
	sf::Texture healthPackTexture;
	sf::Texture fireRateTexture;
	EntityId playerId;
	const sf::Vector2f playerSpawn;
	bool doubleFireStat;
	sf::Texture doubleFireTexture;
	sf::Sprite doubleFireSprite;

	std::vector<sf::Texture> playerDeathTextures;
	std::vector<sf::Texture> enemyDeadTextures;
	std::vector<sf::Texture> missileDeadTextures;
	std::vector<sf::Texture> explosionTextures;
	std::vector<sf::Texture> healExplosionTextures;

	sf::Text waveText;
	sf::Text waveUpdateText;
	sf::Text waveUpdateSideText;
	sf::RectangleShape waveUpdateBackground;
	int lastWave;
	sf::Time timeUntilWave;

	sf::Text scoreText;
	sf::Text healthText;
	sf::RectangleShape healthBar;
	sf::RectangleShape healthBarBorder;
	sf::Text healthValue;

	sf::Texture enemyTexture;
	sf::Texture fireEnemyProjectileTexture;
	sf::Texture missileEnemyTexture;

	sf::Texture spaceTexture;
	sf::Texture starTexture;

	sf::Sprite spaceBackground;
	sf::Sprite spaceBackgroundNext;
	const float spaceBackgroundSpeed;

	sf::Sprite* starSpriteArray;
	const float starSpriteSpeed;
	const int starSpriteAmount;
};

