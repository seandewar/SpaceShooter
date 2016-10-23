#include "WaveManager.h"


WaveManager::WaveManager(EntityManager* entityManager, EntityId playerId, sf::Texture* _enemyTexture, sf::Texture* _fireEnemyProjectileTexture, std::vector<sf::Texture>* _explosionTextures,
		std::vector<sf::Texture>* _enemyDeadTextures, sf::Texture* _healthPackTexture, std::vector<sf::Texture>* _healExplosionTexture, sf::Texture* _missileEnemy,
		std::vector<sf::Texture>* _missileDeadTextures, sf::Texture* _fireRateTexture) :
	entityManagerPntr(entityManager),
	playerId(playerId),
	enemyTexture(_enemyTexture),
	fireEnemyProjectileTexture(_fireEnemyProjectileTexture),
	explosionTextures(_explosionTextures),
	enemyDeadTextures(_enemyDeadTextures),
	healthPackTexture(_healthPackTexture),
	healExplosionTexture(_healExplosionTexture),
	missileEnemy(_missileEnemy),
	missileDeadTextures(_missileDeadTextures),
	fireRateTexture(_fireRateTexture),
	currentWave(0),
	spawnTokensThisWave(0),
	spawnTokensLeft(0),
	maxAmountOnScreenThisWave(0),
	timeSpawnTokenUsageMilliseconds(0),
	timeSpawnTokenUsageBiasMilliseconds(0),
	maxAmountOnScreenCap(50),
	timeSpawnTokenUsageCapMilliseconds(800),
	timeSpawnTokenUsageBiasCapMilliseconds(600)
{
	std::cout << "WaveManager::WaveManager() - construct" << std::endl;
}


WaveManager::~WaveManager()
{
}


void WaveManager::StartWave(int _wave, sf::Time elapsedTime)
{
	std::cout << "WaveManager::StartWave() - Changing wave to " << _wave << std::endl;

	currentWave = _wave;
	spawnTokensThisWave = spawnTokensLeft = (currentWave*5)+((int)floor((currentWave*0.75)+0.5));
	maxAmountOnScreenThisWave = 5+currentWave;

	if(maxAmountOnScreenThisWave > maxAmountOnScreenCap)
		maxAmountOnScreenThisWave = maxAmountOnScreenCap;

	timeSpawnTokenUsageMilliseconds = 2000-(currentWave*135);
	timeSpawnTokenUsageBiasMilliseconds = currentWave*40;

	if(timeSpawnTokenUsageMilliseconds < timeSpawnTokenUsageCapMilliseconds)
		timeSpawnTokenUsageMilliseconds = timeSpawnTokenUsageCapMilliseconds;
	if(timeSpawnTokenUsageBiasMilliseconds > timeSpawnTokenUsageBiasCapMilliseconds)
		timeSpawnTokenUsageBiasMilliseconds = timeSpawnTokenUsageBiasCapMilliseconds;

	std::cout << "WaveManager::StartWave() - Spawn Tokens this wave: " << spawnTokensThisWave << std::endl;
	std::cout << "WaveManager::StartWave() - Max Amount on screen this wave: " << maxAmountOnScreenThisWave << " (cap: " << maxAmountOnScreenCap << ")" << std::endl;
	std::cout << "WaveManager::StartWave() - Time Spawn Token Usage (ms): " << timeSpawnTokenUsageMilliseconds << " (cap: " << timeSpawnTokenUsageCapMilliseconds << ")" << std::endl;
	std::cout << "WaveManager::StartWave() - Time Spawn Token Usage Bias (ms): " << timeSpawnTokenUsageBiasMilliseconds << " (cap: " << timeSpawnTokenUsageBiasCapMilliseconds << ")" << std::endl;

	nextSpawnTokenUsage = elapsedTime + sf::milliseconds(4000);
}


void WaveManager::UseSpawnToken(sf::Time elapsedTime)
{
	if(currentWave >= 5)
	{
		//Roll to spawn missile or normal if wave over 3
		if(rand()%18 == 0 && spawnTokensLeft >= 2)
		{
			spawnTokensLeft -= 2;
			entityManagerPntr->AddEntity(new MissileEnemyEntity((*missileEnemy), sf::Vector2f((float)(rand()%800), -40.0f), entityManagerPntr, playerId, explosionTextures, missileDeadTextures));
		}
		else
		{
			--spawnTokensLeft;
			entityManagerPntr->AddEntity(new EnemyEntity((*enemyTexture), fireEnemyProjectileTexture, sf::Vector2f((float)(rand()%800), -40.0f), entityManagerPntr, playerId, elapsedTime, explosionTextures, enemyDeadTextures));
		}
	}
	else
	{
		--spawnTokensLeft;
		entityManagerPntr->AddEntity(new EnemyEntity((*enemyTexture), fireEnemyProjectileTexture, sf::Vector2f((float)(rand()%800), -40.0f), entityManagerPntr, playerId, elapsedTime, explosionTextures, enemyDeadTextures));
	}

	//Roll to spawn a health pack or double fire speed buff. These will not take a token.
	if(rand()%35 == 0)
	{
		entityManagerPntr->AddEntity(new HealthPackEntity(healthPackTexture, sf::Vector2f((float)(rand()%800), -30.0f), sf::Vector2f(0.0f, 0.2f), 100, healExplosionTexture, entityManagerPntr));
	}
	else if(rand()%40 == 0)
	{
		entityManagerPntr->AddEntity(new DoubleFirePackEntity(fireRateTexture, sf::Vector2f((float)(rand()%800), -30.0f), sf::Vector2f(0.0f, 0.3f), healExplosionTexture, entityManagerPntr));
	}
}


bool WaveManager::CheckEntityAmount()
{
	//-1 so we don't consider the player.
	if(entityManagerPntr->GetParticularEntityCount("AliveEntity") - 1 > maxAmountOnScreenThisWave)
		return false;

	return true;
}


void WaveManager::UpdateWave(sf::Time elapsedTime)
{
	if(spawnTokensLeft <= 0 ||
		elapsedTime < nextSpawnTokenUsage ||
		 !CheckEntityAmount())
		return;

	UseSpawnToken(elapsedTime);

	nextSpawnTokenUsage = elapsedTime + sf::milliseconds(timeSpawnTokenUsageMilliseconds-rand()%timeSpawnTokenUsageBiasMilliseconds);
}


void WaveManager::Update(sf::Time elapsedTime, double timeDeltaMilliseconds)
{
	//Wave is won
	if(spawnTokensLeft <= 0 &&
		entityManagerPntr->GetParticularEntityCount("AliveEntity") - 1 <= 0)
	{
		if(playerId != -1)
		{
			std::cout << "WaveManager::Update() - Granting " << 1000*currentWave << " score for completing wave " << currentWave << std::endl;

			static_cast<PlayerEntity*>(entityManagerPntr->GetEntity(playerId))->AddScore(1000*currentWave);
		}

		StartWave(++currentWave, elapsedTime);
	}

	UpdateWave(elapsedTime);
}


void WaveManager::SetPlayerId(EntityId _playerId) 
{
	playerId = _playerId;
}


int WaveManager::GetCurrentWave() const
{
	return currentWave;
}


int WaveManager::GetSpawnTokensThisWave() const
{
	return spawnTokensThisWave;
}


int WaveManager::GetSpawnTokensLeft() const
{
	return spawnTokensLeft;
}


int WaveManager::GetMaxAmountOnScreen() const
{
	return maxAmountOnScreenThisWave;
}