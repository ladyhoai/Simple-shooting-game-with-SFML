#include "Game.h"
#define PRINT this->window->
#define DELETE_HEALTH this->healthbar.pop_back();

//private function
void Game::Initvariable()
{
	this->window = nullptr;
	this->pointcount = 0;
	
	//game logic
	this->points = 0;
	this->enemySpawnTimerMax = 7.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;

	this->bulletSpawnTimerMax = 4.f;
	this->bulletSpawnTimer = this->bulletSpawnTimerMax;
	this->maxbullet = 15;
	
	this->maxEnemies = 40;
	//this->mouseHeld = false;
	this->maxHealth = 5;

}

void Game::Initwindow()
{
	this->videoMode.height = 800;
	this->videoMode.width = 1400;
	this->window = new sf::RenderWindow(this->videoMode, "The Dick", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::InitFont()
{
	if (!this->font.loadFromFile("font/Comfortaa-VariableFont_wght.ttf"))
	{
		std::cout << "Failed to load font\n";
	}
}

void Game::InitText()
{
	
	this->uiTest.setFont(this->font);
	this->uiTest.setCharacterSize(50);
	this->uiTest.setFillColor(sf::Color(94, 115, 102));
	this->uiTest.setString("NONE");
	this->uiTest.setStyle(sf::Text::Bold);
	
	uiTest.setPosition(this->window->getSize().x / 2.f - this->uiTest.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->uiTest.getGlobalBounds().height / 2.f);


	this->gameOver.setFont(this->font);
	this->gameOver.setCharacterSize(50);
	this->gameOver.setFillColor(sf::Color(255, 255, 255));
	this->gameOver.setString("GAME OVER");
	this->gameOver.setStyle(sf::Text::Bold);
	
	gameOver.setPosition( this->window->getSize().x/2.f - this->gameOver.getGlobalBounds().width/2.f,
							(this->window->getSize().y/2.f - this->gameOver.getGlobalBounds().height/2.f) - 200);
}

void Game::Initenemy()
{
	this->enemyNormal.setSize(sf::Vector2f(25.f, 25.f));
	this->enemyNormal.setFillColor(sf::Color::Green);
	this->enemyNormal.setOutlineColor(sf::Color::Black);
	this->enemyNormal.setOutlineThickness(1.f);

	this->enemyEasy.setSize(sf::Vector2f(40.f, 40.f));
	this->enemyEasy.setFillColor(sf::Color(40, 32, 54));
	this->enemyEasy.setOutlineColor(sf::Color::Black);
	this->enemyEasy.setOutlineThickness(1.f);

	this->enemyHard.setSize(sf::Vector2f(15.f, 15.f));
	this->enemyHard.setFillColor(sf::Color(103, 32, 54));
	this->enemyHard.setOutlineColor(sf::Color::Black);
	this->enemyHard.setOutlineThickness(1.f);
}

void Game::InitShip()
{
	if (!texture.loadFromFile("font/sheet.png"))
		std::cout << "Image failed to load\n";
}

void Game::InitSprite()
{
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 30, 140, 300));
	sprite.setPosition(600.f, 700.f);
	sprite.setScale(0.45f, 0.45f);
}

void Game::InitBullet()
{
	this->bullet.setRadius(150);
	this->bullet.setScale(0.03f, 0.03f);
	this->bullet.setOutlineColor(sf::Color::White);
	this->bullet.setOutlineThickness(5);
}




//constructor and destructor

//constructor : Initializing objects
Game::Game()
{
	fly.openFromFile("font/mixkit-deep-cinematic-wind-hum-1177.wav");
	fly.setVolume(40.f);
	fly.setLoop(true);
	fly.play();
	this->Initvariable();
	this->Initwindow();
	this->InitFont();
	this->InitText();
	this->Initenemy();
	this->InitShip();
	this->InitSprite();
	this->InitBullet();
	this->InitHealth();
	this->InitShield();
	this->InitSound();
	lasergun.InitGun(window);
	lasergun.InitGunbullet(window);
	lasergun.InitSound();
}

Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

bool Game::restart()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && maxHealth <= 0)
	{
		lasergun.restart(window, maxbullet);
		checkRestart = 1;
		endgame = false;
		moveCondom = false;
		checkShield = false;
		sprite.setPosition(600.f, 700.f);
		shield.setPosition(rand() % window->getSize().x, -40.f);
		enemies.clear();
		bullets.clear();
		decrement_y.clear();
		points = 0;
		pointcount = 0;
		maxHealth = 5;
		speedSprite_x = 5.f;
		speedSprite_y = 5.f;
		healthbar.push_back(health);
		healthbar.push_back(health2);
		healthbar.push_back(health3);
		healthbar.push_back(health4);
		healthbar.push_back(health5);
		fly.play();
	}
	return checkRestart == 1;
}


void Game::InitHealth()
{
	health.setSize(sf::Vector2f(10.f, 10.f));
	health.setFillColor(sf::Color::Red);
	health.setOutlineColor(sf::Color(94, 115, 102));
	health.setOutlineThickness(2.f);

	health2.setSize(sf::Vector2f(10.f, 10.f));
	health2.setFillColor(sf::Color::Red);
	health2.setOutlineColor(sf::Color(94, 115, 102));
	health2.setOutlineThickness(2.f);

	health3.setSize(sf::Vector2f(10.f, 10.f));
	health3.setFillColor(sf::Color::Red);
	health3.setOutlineColor(sf::Color(94, 115, 102));
	health3.setOutlineThickness(2.f);

	health4.setSize(sf::Vector2f(10.f, 10.f));
	health4.setFillColor(sf::Color::Red);
	health4.setOutlineColor(sf::Color(94, 115, 102));
	health4.setOutlineThickness(2.f);

	health5.setSize(sf::Vector2f(10.f, 10.f));
	health5.setFillColor(sf::Color::Red);
	health5.setOutlineColor(sf::Color(94, 115, 102));
	health5.setOutlineThickness(2.f);

	this->health.setPosition(655, 470);
	this->health2.setPosition(665, 470);
	this->health3.setPosition(675, 470);
	this->health4.setPosition(685, 470);
	this->health5.setPosition(695, 470);

	healthbar.push_back(health);
	healthbar.push_back(health2);
	healthbar.push_back(health3);
	healthbar.push_back(health4);
	healthbar.push_back(health5);
}

void Game::InitShield()
{
	if (!LoadShield.loadFromFile("font/condom1.png"))
	{
		std::cout << " Can not load shield" << std::endl;
	}
	shield.setTexture(LoadShield);
	shield.setPosition(rand() % window->getSize().x, -40.f);
}

void Game::InitSound()
{
	buffer.loadFromFile("font/mixkit-quick-jump-arcade-game-239.wav");

	sound.setBuffer(buffer);
	sound.setVolume(20.f);

	buffer2.loadFromFile("font/mixkit-electronic-retro-block-hit-2185.wav");
	sound2.setBuffer(buffer2);
	sound2.setVolume(20.f);

	buffer1.loadFromFile("font/mixkit-retro-arcade-game-over-470.wav");
	sound1.setBuffer(buffer1);

	if (!getCondom.loadFromFile("font/mixkit-click-error-1110.wav"))
		std::cout << " Can not load a sound \n";
	Condom.setBuffer(getCondom);
	Condom.setVolume(20.f);
}

void Game::spawnEnemy()
{
	/*
		return void
		spawns enemies and set their color and position
		set a random position and colour
		add enemies to the vector
	*/
	this->enemyNormal.setPosition(static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemyNormal.getSize().x)), 0.f);
	this->enemyEasy.setPosition(static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemyEasy.getSize().x)), 0.f);
	this->enemyHard.setPosition(static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemyHard.getSize().x)), 0.f);
	
	int type = rand() % 3;

	switch (type)
	{
	case 1:
		this->enemies.push_back(this->enemyNormal);
		
	case 2:
		this->enemies.push_back(this->enemyEasy);
		
	case 3:
		this->enemies.push_back(this->enemyHard);		
	}
}

void Game::pollEvents()
{
	//Event polling

	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}
//Spawn Bullet
void Game::spawnBullet()
{
	this->bullet.setPosition(sprite.getPosition().x + 42, sprite.getPosition().y + 8);
	bullets.push_back(bullet);
}

void Game::updateEnemy()
{
	/*
		return void
		updates the enemy spawn timer and spawns enemies
		when the total amount of enemies is smaller than the max 
		moves enemies downward
		removes the enemies at the edge of the screen
	*/

	//updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;			
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//move and update enemies

	//check for kill (bullets hit enemies)
	

	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;
		
		//Set enemies' movement speed
		if (this->enemies[i].getFillColor() == sf::Color::Green) 
			this->enemies[i].move(0.f, speedNormal);
		if (this->enemies[i].getFillColor() == sf::Color(40, 32, 54))
			this->enemies[i].move(0.f, speedEasy);
		if (this->enemies[i].getFillColor() == sf::Color(103, 32, 54))
			this->enemies[i].move(0.f, speedHard);

		// Erase enemies and bullets if bullets hit enemies
		for (int y = 0; y < bullets.size() && !deleted; y++)
		{	
			if (this->enemies[i].getGlobalBounds().intersects(bullets[y].getGlobalBounds()))
			{
				this->bullets.erase(this->bullets.begin() + y);
				y--;
				deleted = true;
				sound.play();

				//Check enemies' health
				if (this->enemies[i].getFillColor() == sf::Color::Green)
				{
					healthNormal--;
					if (healthNormal == 0)
					{
						animation.breaker(this->enemies[i]);
						this->points += 10;
						this->enemies.erase(this->enemies.begin() + i);
						i--;
						deleted = true;
						healthNormal = 4;
					}
				}
				if (this->enemies[i].getFillColor() == sf::Color(40, 32, 54))
				{
					healthHard--;
					
					if (healthHard == 0)
					{
						animation.breaker(this->enemies[i]);
						this->points += 15;
						this->enemies.erase(this->enemies.begin() + i);
						i--;
						deleted = true;
						healthHard = 5;
					}
				}
				if (this->enemies[i].getFillColor() == sf::Color(103, 32, 54))
				{
					animation.breaker(this->enemies[i]);
					this->points += 5;
					this->enemies.erase(this->enemies.begin() + i);
					i--;
					deleted = true;
				}
			}
		}
		
		//decrease player's health if they hit enemies
		//for (size_t z = 0; z < healthbar.size() && !deleted; z++)
		//{
			if (this->enemies[i].getGlobalBounds().intersects(sprite.getGlobalBounds()) && !checkShield)
			{
				sound2.play();
				DELETE_HEALTH
				this->enemies.erase(this->enemies.begin() + i);
				i--;
				maxHealth--;
				deleted = true;
			}

		if (this->enemies[i].getGlobalBounds().intersects(sprite.getGlobalBounds()) && checkShield && !deleted)
		{
			this->enemies.erase(this->enemies.begin() + i);
			i--;
			deleted = true;
			checkShield = false;
			maxbullet = 15;
		//	pointcount = points;
		}

		if (!deleted && this->enemies[i].getPosition().y > this->window->getSize().y)
		{			
			this->enemies.erase(enemies.begin() + i);
			i--;
			deleted = true;			
		}
	}
}		
	
//Functions
void Game::update()            //All the logic behind our game, behind the scene function
{
	this->pollEvents();

	this->updateText();
	
	this->updateBullet();
	
	this->updateEnemy();

	this->updateShip();

	this->updateCondom();

	animation.updateBreaker(this->window);

	lasergun.updateGun(this->window, this->sprite, maxHealth, healthbar, checkShield, endgame, 
		points, speedSprite_x, speedSprite_y, maxbullet);

	lasergun.delete_ball(bullets, points);
}


void Game::updateText()
{
	std::stringstream ss;

	ss  << this->points;

	this->uiTest.setString(ss.str());
}

void Game::updateCondom()
{
	if (moveCondom &&!checkShield) 
		shield.move(sf::Vector2f(0.f, 1.f));
	if (pointcount + 100 <= points)
	{
		moveCondom = true;
		if (shield.getPosition().y >= window->getSize().y)
		{
			shield.setPosition(rand() % window->getSize().x, -40.f);
			moveCondom = false;
			pointcount = points;
		}
		else if (shield.getGlobalBounds().intersects(sprite.getGlobalBounds()))
		{
			Condom.play();
			shield.setPosition(rand() % window->getSize().x, -40.f);
			sprite.setTextureRect(sf::IntRect(300, 0, 180, 340));
			checkShield = true;
			moveCondom = false;
			pointcount = points;
		}
	}
}

void Game::updateShip()
{	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{	
		sprite.move(0.f, speedSprite_y);		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{	
		sprite.move(0.f, -speedSprite_y);		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{		
		sprite.move(speedSprite_x, 0.f);		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{	
		sprite.move(-speedSprite_x, 0.f);		
	}

	if (sprite.getPosition().x < 0)
		sprite.setPosition(0.f, sprite.getPosition().y);
	else if (sprite.getPosition().x + sprite.getGlobalBounds().width > 1400)
		sprite.setPosition(1400 - sprite.getGlobalBounds().width, sprite.getPosition().y);

	if (sprite.getPosition().y < 0)
		sprite.setPosition(sprite.getPosition().x, 0.f);
	else if (sprite.getPosition().y + sprite.getGlobalBounds().height > 800)
		sprite.setPosition(sprite.getPosition().x, 800 - sprite.getGlobalBounds().height);
}

void Game::updateBullet()
{
	for (int y = 0; y < this->bullets.size(); y++)
	{	
		if (!checkShield)
		{	
			sprite.setTextureRect(sf::IntRect(0, 30, 140, 300));
			this->bullets[y].move(0.f, -10.f);
			if (this->bullets[y].getPosition().y < 0)
			{
				this->bullets.erase(bullets.begin() + y);
				y--;
			}
		}

		if (checkShield)
		{
			maxbullet = 30;
			decrement_y.push_back(0.04f);
			decrement_y[y] += 0.1f;
			bullet_move_x = sprite.getPosition().x + 40.f + 200 * std::cos(decrement_y[y]);
			bullet_move_y = sprite.getPosition().y + 50.f + 200 * std::sin(decrement_y[y]);
			bullets[y].setPosition(bullet_move_x, bullet_move_y);
			if (bullets[y].getGlobalBounds().intersects(sprite.getGlobalBounds()))
			{
				decrement_y.erase(decrement_y.begin() + y);
			}
		}
		
	}
	if (bullets.size() < maxbullet)
	{
		if (bulletSpawnTimer >= bulletSpawnTimerMax)
		{
			spawnBullet();
			bulletSpawnTimer = 0.f;		
		}
		else
		{
			bulletSpawnTimer += 1.f;
		}
	}
}

void Game::condition()
{
	while (this->window->isOpen())
	{
		this->pollEvents();
		if ((maxHealth > 0 || restart()) && !endgame )
		{
			this->update();
			this->render();
		}
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiTest);
}

void Game::renderShip()
{
	PRINT draw(sprite);
}

void Game::renderEnemy()
{
	for (auto& e : this->enemies)
	{
		PRINT draw(e);		
	}
}

void Game::renderBullet()
{
	for (auto& a : this->bullets)
	{
		PRINT draw(a);
	}
}

void Game::renderHealth()
{
	for (auto& b : this->healthbar)
	{
		PRINT draw(b);
	}
}

void Game::renderCondom()
{
	PRINT draw(shield);
}


void Game::render() //visualizing all the position, points, pixels, ...
{
	/*
		return void
		-clear old frames
		-render objects
		-display frame in window
		render the game objects
	*/

	this->window->clear(sf::Color::Black);
	//draw game objects
	this->renderShip();	
	this->renderBullet();
	this->renderEnemy();
	this->renderHealth();
	this->renderText(*this->window);
	this->renderCondom();
	animation.RenderBreak(window);
	lasergun.renderGun(window);
	if (maxHealth <= 0 || endgame)
	{
		sound1.play();
		fly.pause();
		PRINT draw(gameOver);
		checkRestart = 0;
	}
	this->window->display();
}








