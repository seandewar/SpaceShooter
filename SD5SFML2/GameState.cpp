#include "GameState.h"


GameState::GameState(sf::Font& font) :
	State("GameState"),
	spaceBackgroundSpeed(0.20f),
	starSpriteSpeed(0.23f),
	starSpriteAmount(50),
	playerId(-1),
	playerSpawn(375, 550),
	entityManager(font),
	waveStarted(false),
	waveManager(nullptr),
	lastWave(0),
	doubleFireStat(false)
{
	std::cout << std::endl;
	std::cout << "GameState::GameState() Setting up game" << std::endl;
	std::cout << "GameState::spaceBackgroundSpeed " << spaceBackgroundSpeed << std::endl;
	std::cout << "GameState::starSpriteSpeed " << starSpriteSpeed << std::endl;
	std::cout << "GameState::starSpriteAmount " << starSpriteAmount << std::endl;
	std::cout << "GameState::playerSpawn (" << playerSpawn.x << ", " << playerSpawn.y << ")" << std::endl;
	std::cout << std::endl;

	gameOverBackground.setFillColor(sf::Color(0, 0, 0, 100));
	gameOverBackground.setPosition(sf::Vector2f(0, 294));
	gameOverBackground.setSize(sf::Vector2f(800, 260));

	waveUpdateText.setFont(font);
	waveUpdateText.setCharacterSize(48);
	waveUpdateText.setPosition(100, 314);

	waveUpdateBackground.setFillColor(sf::Color(0, 0, 0, 100));
	waveUpdateBackground.setPosition(sf::Vector2f(0, 294));
	waveUpdateBackground.setSize(sf::Vector2f(800, 150));

	doubleFireSprite.setPosition(610, 553);

	waveUpdateSideText.setFont(font);
	waveUpdateSideText.setCharacterSize(16);
	waveUpdateSideText.setPosition(100, 384);

	gameOverText.setFont(font);
	gameOverText.setCharacterSize(48);
	gameOverText.setString("Game Over!");
	gameOverText.setPosition(100, 314);

	gameOverStats.setFont(font);
	gameOverStats.setCharacterSize(16);
	gameOverStats.setPosition(100, 384);

	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setPosition(0, 576);

	waveText.setFont(font);
	waveText.setCharacterSize(24);
	waveText.setPosition(0, 552);

	healthText.setFont(font);
	healthText.setCharacterSize(24);
	healthText.setString("Health:");
	healthText.setPosition(500, 576);

	healthValue.setFont(font);
	healthValue.setCharacterSize(22);
	healthValue.setPosition(610, 573);

	healthBar.setOutlineColor(sf::Color::Transparent);
	healthBar.setOutlineThickness(2);
	healthBar.setPosition(605, 576);
	healthBarBorder.setOutlineColor(sf::Color::White);
	healthBarBorder.setOutlineThickness(2);
	healthBarBorder.setFillColor(sf::Color::Black);
	healthBarBorder.setPosition(605, 576);
	healthBarBorder.setSize(sf::Vector2f(193, 22));

	//Init the array containing all of the star sprites.
	starSpriteArray = new sf::Sprite[starSpriteAmount];
}


GameState::~GameState()
{
	std::cout << "GameState::~GameState()" << std::endl << std::endl;

	//Delete the star sprite array as it is dynamically allocated.
	delete [] starSpriteArray;
	starSpriteArray = nullptr;
}


void GameState::LoadBackground()
{
	std::cout << "GameState::LoadBackground() Loading background texture and init scroll" << std::endl;

	//Set the texture of the space background gradient.
	spaceTexture.loadFromFile("spacebg.png");
	spaceBackground.setTexture(spaceTexture);
	spaceBackgroundNext.setTexture(spaceTexture);

	//Set initial background positions
	spaceBackground.setPosition(0.0f, 0.0f);
	spaceBackgroundNext.setPosition(0.0f, 600.0f);
}


void GameState::UpdateWaveCount()
{
	if(waveManager == nullptr)
		waveText.setString("No wave");

	std::stringstream ss;
	ss << "Wave: " << waveManager->GetCurrentWave();

	waveText.setString(ss.str());
}


void GameState::DrawWaveCount(sf::RenderWindow& window)
{
	window.draw(waveText);
}


void GameState::UpdateBackground(sf::Time elapsedTime, double timeDeltaMilliseconds)
{
	sf::Vector2f spacePos = spaceBackground.getPosition();
	sf::Vector2f spacePosNext = spaceBackgroundNext.getPosition();

	spacePos.y += spaceBackgroundSpeed * (float)timeDeltaMilliseconds;
	spacePosNext.y += spaceBackgroundSpeed * (float)timeDeltaMilliseconds;

	if(spacePos.y > 600.0f)
	{
		spacePos.y = -600.0f + (spacePos.y - 600.0f);
	}
	if(spacePosNext.y > 600.0f)
	{
		spacePosNext.y = -600.0f + (spacePosNext.y - 600.0f);
	}

	spaceBackground.setPosition(spacePos);
	spaceBackgroundNext.setPosition(spacePosNext);
}


void GameState::DrawBackground(sf::RenderWindow& window)
{
	window.draw(spaceBackground);
	window.draw(spaceBackgroundNext);
}


void GameState::LoadStars()
{
	std::cout << "GameState::LoadStars() Loading star texture and init stars" << std::endl;

	//Set the texture of all the stars.
	starTexture.loadFromFile("star.png");
	for(int i = 0; i < starSpriteAmount; ++i)
	{
		starSpriteArray[i].setTexture(starTexture);
		starSpriteArray[i].setPosition((float)(rand()%800), (float)(rand()%620));
	}
}


void GameState::UpdateStars(sf::Time elapsedTime, double timeDeltaMilliseconds)
{
	for(int i = 0; i < starSpriteAmount; ++i)
	{
		sf::Vector2f pos = starSpriteArray[i].getPosition();
		pos.y += starSpriteSpeed * (float)timeDeltaMilliseconds;

		if(pos.y >= 620.0f)
		{
			pos.y -= 635.0f;
			pos.x = (float)(rand()%800);
		}

		starSpriteArray[i].setPosition(pos);
	}
}


void GameState::DrawStars(sf::RenderWindow& window)
{
	//Draw the stars.
	for(int i = 0; i < starSpriteAmount; ++i)
	{
		window.draw(starSpriteArray[i]);
	}
}


void GameState::LoadEnemy()
{
	std::cout << "GameState::LoadEnemy() Loading enemy textures" << std::endl;

	enemyTexture.loadFromFile("enemy.png");
	fireEnemyProjectileTexture.loadFromFile("enemyfire.png");

	sf::Texture enemyDeadTex;
	enemyDeadTex.loadFromFile("enemydead1.png");
	enemyDeadTextures.push_back(enemyDeadTex);
	enemyDeadTex.loadFromFile("enemydead2.png");
	enemyDeadTextures.push_back(enemyDeadTex);
	enemyDeadTex.loadFromFile("enemydead3.png");
	enemyDeadTextures.push_back(enemyDeadTex);
	enemyDeadTex.loadFromFile("enemydead4.png");
	enemyDeadTextures.push_back(enemyDeadTex);

	missileEnemyTexture.loadFromFile("missileenemy.png");

	enemyDeadTex.loadFromFile("missileenemydead1.png");
	missileDeadTextures.push_back(enemyDeadTex);
	enemyDeadTex.loadFromFile("missileenemydead2.png");
	missileDeadTextures.push_back(enemyDeadTex);
	enemyDeadTex.loadFromFile("missileenemydead3.png");
	missileDeadTextures.push_back(enemyDeadTex);
}


void GameState::AddEnemy(sf::Vector2f pos, sf::Time elapsedTime)
{
	entityManager.AddEntity(new EnemyEntity(enemyTexture, &fireEnemyProjectileTexture, pos, &entityManager, playerId, elapsedTime, &explosionTextures, &enemyDeadTextures));
}


void GameState::LoadExplosionEffect()
{
	std::cout << "GameState::LoadExplosionEffect() Loading explosion entity textures" << std::endl;

	sf::Texture explosionTex;
	explosionTex.loadFromFile("hit1.png");
	explosionTextures.push_back(explosionTex);
	explosionTex.loadFromFile("hit2.png");
	explosionTextures.push_back(explosionTex);
	explosionTex.loadFromFile("hit3.png");
	explosionTextures.push_back(explosionTex);
}


void GameState::LoadPlayer()
{
	std::cout << "GameState::LoadPlayer() Loading player textures." << std::endl;

	playerTexture.loadFromFile("player.png");
	fireProjectileTexture.loadFromFile("fire.png");

	sf::Texture playerDeathTex;
	playerDeathTex.loadFromFile("playerdead1.png");
	playerDeathTextures.push_back(playerDeathTex);
	playerDeathTex.loadFromFile("playerdead2.png");
	playerDeathTextures.push_back(playerDeathTex);
	playerDeathTex.loadFromFile("playerdead3.png");
	playerDeathTextures.push_back(playerDeathTex);
	playerDeathTex.loadFromFile("playerdead4.png");
	playerDeathTextures.push_back(playerDeathTex);
	playerDeathTex.loadFromFile("playerdead5.png");
	playerDeathTextures.push_back(playerDeathTex);

	healthPackTexture.loadFromFile("health.png");
	fireRateTexture.loadFromFile("attackspeed.png");

	sf::Texture healExplosionTex;
	healExplosionTex.loadFromFile("heal1.png");
	healExplosionTextures.push_back(healExplosionTex);
	healExplosionTex.loadFromFile("heal2.png");
	healExplosionTextures.push_back(healExplosionTex);
	healExplosionTex.loadFromFile("heal3.png");
	healExplosionTextures.push_back(healExplosionTex);
	healExplosionTex.loadFromFile("heal4.png");
	healExplosionTextures.push_back(healExplosionTex);
	healExplosionTex.loadFromFile("heal5.png");
	healExplosionTextures.push_back(healExplosionTex);

	doubleFireTexture.loadFromFile("doublefire.png");
	doubleFireSprite.setTexture(doubleFireTexture);
}


void GameState::AddPlayer()
{
	if(playerId != -1)
	{
		std::cerr << "GameState::AddPlayer() Error - Player already assigned (id " << playerId << "), no action taken." << std::endl;
		return;
	}

	playerId = entityManager.AddEntity(new PlayerEntity(playerTexture, &fireProjectileTexture, playerSpawn, &entityManager, &playerDeathTextures, &explosionTextures));

	std::cout << "GameState::AddPlayer() Player assigned with id " << playerId << std::endl;
}


void GameState::RemovePlayer()
{
	if(playerId == -1)
	{
		std::cerr << "GameState::RemovePlayer() Error - Player not assigned, nothing to remove. No action taken." << std::endl;
		return;
	}

	entityManager.RemoveEntity(playerId);
	playerId = -1;

	std::cout << "GameState::RemovePlayer() Player removed (id was " << playerId << ")" << std::endl;
}


void GameState::UpdateResult()
{
	AliveEntity* pl = static_cast<AliveEntity*>(entityManager.GetEntity(playerId));

	if(!pl->IsDead())
		return;

	std::stringstream ss;
	ss << "You scored " << static_cast<PlayerEntity*>(entityManager.GetEntity(playerId))->GetScore() << " points!" << std::endl;
	ss << "You got owned at wave " << waveManager->GetCurrentWave() << "." << std::endl << std::endl;
	ss << "Now close the game" << std::endl << "(because it hasn't got a menu yet)" << std::endl; "8===D";

	gameOverStats.setString(ss.str());
}


void GameState::DrawResult(sf::RenderWindow& window)
{
	AliveEntity* pl = static_cast<AliveEntity*>(entityManager.GetEntity(playerId));

	if(!pl->IsDead())
		return;

	window.draw(gameOverBackground);
	window.draw(gameOverText);
	window.draw(gameOverStats);
}


void GameState::UpdateScore()
{
	if(playerId == -1)
		return;

	std::stringstream scoreTextString;
	scoreTextString << "Score: " << static_cast<PlayerEntity*>(entityManager.GetEntity(playerId))->GetScore();

	scoreText.setString(scoreTextString.str());
}


void GameState::DrawScore(sf::RenderWindow& window)
{
	if(playerId == -1)
		return;

	window.draw(scoreText);
}


void GameState::UpdateHealth()
{
	if(playerId == -1)
		return;

	AliveEntity* pl = static_cast<AliveEntity*>(entityManager.GetEntity(playerId));
	double healthMultiple = (double)pl->GetHealth()/(double)pl->GetMaxHealth();

	healthBar.setSize(sf::Vector2f(193*(float)healthMultiple, 22));

	sf::Color healthBarColor;

	if(healthMultiple >= 0.75)
	{
		healthBarColor = sf::Color(0, 225, 0);
	}
	else if(healthMultiple >= 0.5)
	{
		healthBarColor = sf::Color(155, 200, 0);
	}
	else if(healthMultiple >= 0.25)
	{
		healthBarColor = sf::Color(155, 155, 0);
	}
	else if(healthMultiple >= 0.1)
	{
		healthBarColor = sf::Color::Red;
	}

	healthBar.setFillColor(healthBarColor);

	std::stringstream ss;
	ss << pl->GetHealth() << "/" << pl->GetMaxHealth();

	healthValue.setString(ss.str());
}


void GameState::DrawHealth(sf::RenderWindow& window)
{
	window.draw(healthText);
	window.draw(healthBarBorder);
	window.draw(healthBar);
	window.draw(healthValue);
}


void GameState::InitWaveManager()
{
	waveManager = new WaveManager(&entityManager, playerId, &enemyTexture, &fireEnemyProjectileTexture, &explosionTextures, &enemyDeadTextures, &healthPackTexture, 
		&healExplosionTextures, &missileEnemyTexture, &missileDeadTextures, &fireRateTexture);
}


void GameState::UnloadWaveManager()
{
	delete waveManager;
	waveManager = nullptr;
}

void GameState::UpdateDoubleFire()
{
	if(playerId == -1)
		return;

	doubleFireStat = static_cast<PlayerEntity*>(entityManager.GetEntity(playerId))->IsDoubleFireActive();
}


void GameState::DrawDoubleFire(sf::RenderWindow& window)
{
	if(doubleFireStat)
		window.draw(doubleFireSprite);
}


void GameState::Load()
{
	std::cout << "GameState::Load()" << std::endl;

	LoadBackground();
	LoadStars();
	LoadPlayer();
	LoadEnemy();
	LoadExplosionEffect();

	AddPlayer();
	InitWaveManager();
}


void GameState::Unload()
{
	std::cout << "GameState::Unload()" << std::endl;

	RemovePlayer();
	UnloadWaveManager();
}


void GameState::UpdateWaveUpdate(sf::Time elapsedTime)
{
	if(waveManager->GetCurrentWave() != lastWave)
	{
		lastWave = waveManager->GetCurrentWave();

		std::stringstream ss;
		ss << "Wave " << waveManager->GetCurrentWave() << " incoming!";
		waveUpdateText.setString(ss.str());

		switch(waveManager->GetCurrentWave())
		{
		case 1:
			waveUpdateSideText.setString("\"Get your pants ready!\"");
			break;
		case 2:
			waveUpdateSideText.setString("Let's tone up the difficulty a bit...");
			break;
		case 3:
			waveUpdateSideText.setString("Still easy...");
			break;
		case 4:
			waveUpdateSideText.setString("Okay, this is your last spoonfeed!");
			break;
		case 5:
			waveUpdateSideText.setString("Missile enemies now have a chance of spawning. Haha.");
			break;
		case 6:
			waveUpdateSideText.setString("This is only going to get worse...");
			break;
		case 7:
			waveUpdateSideText.setString("This is where the pace starts picking up...");
			break;
		case 8:
			waveUpdateSideText.setString("Bezza died here, will you do too?");
			break;
		case 9:
			waveUpdateSideText.setString("Feel the pressure!");
			break;
		case 10:
			waveUpdateSideText.setString("Getting tired?");
			break;
		case 11:
			waveUpdateSideText.setString("Here lies SD5, who died here with 74400 score a while ago...");
			break;
		case 12:
			waveUpdateSideText.setString("Any regrets?");
			break;
		case 13:
			waveUpdateSideText.setString("PIC rests here, with 109950 score.");
			break;
		case 14:
			waveUpdateSideText.setString("You will not survive!");
			break;
		case 15:
			waveUpdateSideText.setString("You are the puppet and I pull the strings!");
			break;
		case 16:
			waveUpdateSideText.setString("You cannot beat the system!");
			break;
		case 17:
			waveUpdateSideText.setString("There is no light at the end of this tunnel! Haha.");
			break;
		case 18:
			waveUpdateSideText.setString("I hope that you've already written your will...");
			break;
		case 19:
			waveUpdateSideText.setString("You will not win; there are no winners.");
			break;
		case 20:
			waveUpdateSideText.setString("Impressive, but worthless - you will die!");
			break;
		case 21:
			waveUpdateSideText.setString("Just you, me and my minions!");
			break;
		case 22:
			waveUpdateSideText.setString("Space is a scary place when I'm around!");
			break;
		case 23:
			waveUpdateSideText.setString("What are you hoping to achieve?");
			break;
		case 24:
			waveUpdateSideText.setString("You're writing your own death sentence.");
			break;
		case 25:
			waveUpdateSideText.setString("Your existance is finite.");
			break;
		default:
			waveUpdateSideText.setString("One wave nearer to your doom...");
			break;
		}

		timeUntilWave = elapsedTime + sf::milliseconds(3000);
	}
}


void GameState::DrawWaveUpdate(sf::Time elapsedTime, sf::RenderWindow& window)
{
	if(elapsedTime > timeUntilWave)
		return;

	window.draw(waveUpdateBackground);
	window.draw(waveUpdateText);
	window.draw(waveUpdateSideText);
}


void GameState::Update(sf::Time elapsedTime, double timeDeltaMilliseconds)
{
#ifdef _DEBUG
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1) &&
		elapsedTime >= nextF1Press)
	{
		entityManager.SetDebugMode(!entityManager.IsDebugMode());
		nextF1Press = elapsedTime + sf::milliseconds(500);
	}
#endif

	if(!waveStarted)
	{
		waveManager->StartWave(1, elapsedTime);
		waveStarted = true;
	}

	UpdateBackground(elapsedTime, timeDeltaMilliseconds);
	UpdateStars(elapsedTime, timeDeltaMilliseconds);
	waveManager->Update(elapsedTime, timeDeltaMilliseconds);
	entityManager.Update(elapsedTime, timeDeltaMilliseconds);
	UpdateScore();
	UpdateHealth();
	UpdateDoubleFire();
	UpdateWaveCount();
	UpdateWaveUpdate(elapsedTime);
	UpdateResult();
}


void GameState::Draw(sf::Time elapsedTime, sf::RenderWindow& window)
{
	DrawBackground(window);
	DrawStars(window);
	entityManager.Draw(elapsedTime, window);
	DrawScore(window);
	DrawWaveCount(window);
	DrawHealth(window);
	DrawDoubleFire(window);
	DrawWaveUpdate(elapsedTime, window);
	DrawResult(window);
}