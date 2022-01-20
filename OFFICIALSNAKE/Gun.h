#pragma once
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>

//class for firebaall and snowball
class Laser_Gun
{
private:
	sf::Texture m_gun;
	sf::Sprite m_lasergun;
	sf::Texture m_fireball;
	sf::Sprite fireball;
	sf::Texture m_snowball;
	sf::Sprite snowball;
	sf::CircleShape gun_bullet;
	std::vector <sf::CircleShape> store_bullet;

	sf::Sound fire_hit;
	sf::Sound fire_hit_wall;
	sf::Sound snow_hit_wall;
	sf::Sound snow_hit_ship;
	sf::Sound delete_ball_sound;
	sf::SoundBuffer m_delete_ball;
	sf::SoundBuffer m_fire;
	sf::SoundBuffer m_fire_hit_wall;
	sf::SoundBuffer m_snow_hit_wall;
	sf::SoundBuffer m_snow_hit_ship;
	float m_bulletx = -20;
	float m_bullety = 15;
	
	bool makeballmove;
	bool makeSnowmove;
	bool under_slow_effect = false;

	float m_snowx = -15;
	float m_snowy = 10;

	float fireball_posx = 1.f;
	float fireball_posy = 40.f;

	float snowball_posx = 1.f;
	float snowball_posy = 40.f;

	//int m_bounce = 0;
	int point_to_escape_slowmode = 0;
	int fireball_bounce = 0;

	//unsigned int pointcount;
	unsigned int pointcount_fireball = 600;
	int pointcount_snowball = 200;
	int fireball_health = 6;
	int snowball_health = 5;
public:
	Laser_Gun();
	void InitGun(sf::RenderWindow* window);
	void InitSound();
	void renderGun(sf::RenderWindow* window);
	void InitGunbullet(sf::RenderWindow* window);
	void updateGun(sf::RenderWindow* window, sf::Sprite& ship, int& health, std::vector<sf::RectangleShape>& healthbar, 
					bool &checkShield, bool& endgame, int point, float& speed, float& speed1, int& maxBullet);
	void delete_ball(std::vector<sf::CircleShape>& bullet, int point);
	void restart(sf::RenderWindow* window, int& maxBullet);
};

