#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <random>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <thread>
/*Class that acts as the game engine*/
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "Animation.h"
#include "Gun.h"
// class for ship, bullets, enemy and shield
class Game
{
private:
	//variables
	//window

	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//mouse position
	sf::Vector2i mousePoswindow;
	sf::Vector2f mousePosView;

	//Resources
	sf::Font font;
	sf::SoundBuffer buffer;
	sf::SoundBuffer buffer1;
	sf::SoundBuffer buffer2;
	sf::SoundBuffer getCondom;
	sf::SoundBuffer move;
	sf::Music fly;
	sf::Sound sound;
	sf::Sound sound1;
	sf::Sound sound2;
	sf::Sound Condom;

	//Image
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Texture LoadShield;
	sf::Sprite shield;

	//text
	sf::Text uiTest;
	sf::Text gameOver;
	
	//Game logic
	unsigned points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	bool checkShield = false;
	bool endgame = false;
	bool moveCondom = false;

	float speedSprite_x = 5.f;
	float speedSprite_y = 5.f;
	float speedEasy = 6.f;
	float speedNormal = 8.f;
	float speedHard = 10.f;
	float ElaspedTime;
	float bulletSpawnTimer;
	float bulletSpawnTimerMax;
	int maxbullet;
	int maxHealth;
	int maxEnemies;
	int healthNormal = 2;
	int healthHard = 3;
	unsigned int pointcount;
	int checkRestart = 0; //new
	//game objects
	std::vector<sf::RectangleShape> enemies;
	std::vector<sf::CircleShape> bullets;
	std::vector<sf::RectangleShape> healthbar;
	std::vector<float> decrement_y;
	float bullet_move_x;
	float bullet_move_y;

	sf::RectangleShape enemyNormal;
	sf::RectangleShape enemyHard;
	sf::RectangleShape enemyEasy;
	sf::RectangleShape health;
	sf::RectangleShape health2;
	sf::RectangleShape health3;
	sf::RectangleShape health4;
	sf::RectangleShape health5;
	sf::CircleShape bullet;
	sf::RectangleShape shape1;
	sf::RectangleShape shape2;
	//private function
	//const bool running() const;
	void Initvariable();
	void Initwindow();
	void InitFont();
	void InitText();
	void Initenemy();
	void InitShip();
	void InitSprite();
	void InitBullet();
	void InitHealth();
	void InitShield();
	void InitSound();

public:
	//Constructors and Destructors
	Game();
	virtual ~Game();

	//Objects
	animation animation;
	Laser_Gun lasergun;
	//Accessors
	
	const bool running() const;
	bool restart(); // new

	//Function
	void spawnEnemy();
	void spawnBullet();
	void condition();
	

	void pollEvents();

	void updateEnemy();
	void update();
	
	void updateShip();
	void updateBullet();
	void updateText();
	void updateCondom();

	void renderText(sf::RenderTarget& target);
	void renderShip();
	void renderEnemy();
	void render();
	void renderBullet();
	void renderHealth();
	void renderCondom();
};

