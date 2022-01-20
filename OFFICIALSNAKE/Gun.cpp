#include "Gun.h"

//As I see the lazer gun as inappropriate, I decided to use a cloud instead
Laser_Gun::Laser_Gun()
{
	if (!m_gun.loadFromFile("font/mysterious thing.png"))
		std::cout << "Failed to load cloud" << '\n';
	if (!m_fireball.loadFromFile("font/fireball.png"))
		std::cout << "Failed to load fireball \n";
	if (!m_snowball.loadFromFile("font/snowflake.png"))
		std::cout << "Failed to load iceball \n";
}

void Laser_Gun::InitGun(sf::RenderWindow* window)
{
	m_lasergun.setTexture(m_gun);
	m_lasergun.setPosition(window->getSize().x - 150, 0.f);
	m_lasergun.setScale(0.20f, 0.20f);
	//m_lasergun.setRotation(90);
}

void Laser_Gun::renderGun(sf::RenderWindow* window)
{
	window->draw(fireball);
	window->draw(snowball);
	window->draw(m_lasergun);
}

void Laser_Gun::InitSound()
{
	if (!m_fire.loadFromFile("font/mixkit-space-impact-774.wav"))
		std::cout << "Can not load sound \n";
	fire_hit.setBuffer(m_fire);

	if (!m_fire_hit_wall.loadFromFile("font/mixkit-video-game-mystery-alert-234.wav"))
		std::cout << "Can not load fire sound \n";
	fire_hit_wall.setBuffer(m_fire_hit_wall);

	if (!m_snow_hit_wall.loadFromFile("font/mixkit-video-game-mystery-alert-234.wav"))
		std::cout << "Can not load snow sound \n";
	snow_hit_wall.setBuffer(m_snow_hit_wall);
	snow_hit_wall.setVolume(20.f);

	if (!m_snow_hit_ship.loadFromFile("font/ice-cracking-01.wav"))
		std::cout << "Can not load sound \n";
	snow_hit_ship.setBuffer(m_snow_hit_ship);
	snow_hit_ship.setVolume(20.f);

	if (!m_delete_ball.loadFromFile("font/mixkit-cinematic-sci-fi-glitch-1022.wav"))
		std::cout << " Can not load sound \n";
	delete_ball_sound.setBuffer(m_delete_ball);
	delete_ball_sound.setVolume(20.f);
}

void Laser_Gun::InitGunbullet(sf::RenderWindow* window)
{
	fireball.setTexture(m_fireball);
	fireball.setPosition(window->getSize().x - 70.f, 40.f);
	fireball_posx = window->getSize().x - 70.f;

	snowball.setTexture(m_snowball);
	snowball.setPosition(window->getSize().x - 70.f, 32.f);
	snowball.setScale(0.85f, 0.85f);
}

void Laser_Gun::updateGun(sf::RenderWindow* window, sf::Sprite& ship, int& health, std::vector<sf::RectangleShape>& healthbar, 
							bool &checkShield, bool &endgame, int point,  float& speed, float& speed1, int& maxBullet) {
	(pointcount_fireball <= point) ? makeballmove = true : makeballmove = false;
		
	if (makeballmove){	
		fireball.move(m_bulletx, m_bullety);
		if (fireball.getPosition().x < 0 || fireball.getPosition().x > window->getSize().x - fireball.getGlobalBounds().width)
		{
			m_bulletx = -m_bulletx;
			fire_hit_wall.play();
			fireball_bounce++;
		}

		else if (fireball.getPosition().y < 0 || fireball.getPosition().y > window->getSize().y - fireball.getGlobalBounds().height)
		{
			m_bullety = -m_bullety;
			fire_hit_wall.play();
			fireball_bounce++;
		}

		if (fireball.getGlobalBounds().intersects(ship.getGlobalBounds()) && checkShield)
		{
			fire_hit.play();
			makeballmove = false;
			checkShield = false;
			fireball.setPosition(window->getSize().x - 70.f, fireball_posy);
			healthbar.pop_back();
			health--;
			pointcount_fireball = point + 400;
			fireball_health = 8;
			fireball_bounce = 0;
			maxBullet = 15;
		}
		else if (fireball.getGlobalBounds().intersects(ship.getGlobalBounds()) && !checkShield)
		{
			fire_hit.play();
			if (healthbar.size() == 1)
			{
				makeballmove = false;
				endgame = true;
				healthbar.pop_back();
				health--;
				fireball.setPosition(window->getSize().x - 70.f, fireball_posy);
			}
			else
			{
				makeballmove = false;
				fireball.setPosition(window->getSize().x - 70.f, fireball_posy);
				healthbar.pop_back(); healthbar.pop_back();
				health -= 2;
				pointcount_fireball = point + 400;
				fireball_health = 6;
				fireball_bounce = 0;
			}
		}

		else if (fireball_bounce == 12)
		{
			delete_ball_sound.play();
			makeballmove = false;
			fireball.setPosition(window->getSize().x - 70.f, fireball_posy);
			pointcount_fireball = point + 400;
			fireball_health = 8;
			fireball_bounce = 0;
		}
	}

	//make snowflake move
	(pointcount_snowball <= point) ? makeSnowmove = true : makeSnowmove = false;
		
	if (makeSnowmove)
	{
		snowball.move(m_snowx, m_snowy);
		if (snowball.getPosition().x < 0 || snowball.getPosition().x > window->getSize().x - snowball.getGlobalBounds().width)
		{
			snow_hit_wall.play();
			m_snowx = -m_snowx;
		}

		else if (snowball.getPosition().y < 0 || snowball.getPosition().y > window->getSize().y - snowball.getGlobalBounds().height)
		{
			snow_hit_wall.play();
			m_snowy = -m_snowy;
		}

		if (snowball.getGlobalBounds().intersects(ship.getGlobalBounds()) && !checkShield )
		{
			snow_hit_ship.play();
			point_to_escape_slowmode = point;
			pointcount_snowball = point + 200;
			snowball.setPosition(window->getSize().x - 70.f, 32.f);
			makeSnowmove = false;
			under_slow_effect = true;
			speed /= 2;
			speed1 /= 2;
			maxBullet = 5;
			snowball_health = 5;
		}

		else if (snowball.getGlobalBounds().intersects(ship.getGlobalBounds()) && checkShield)
		{
			snow_hit_ship.play();
			point_to_escape_slowmode = point;
			pointcount_snowball = point + 200;
			snowball.setPosition(window->getSize().x - 70.f, 32.f);
			makeSnowmove = false;
			under_slow_effect = true;
			speed /= 2;
			speed1 /= 2;
			maxBullet = 30;
			snowball_health = 5;
		}
	}

	//Escape slow effect
	if (point - point_to_escape_slowmode >= 50 && under_slow_effect)
	{
		speed *= 2;
		speed1 *= 2;
		under_slow_effect = false;
		point_to_escape_slowmode = 0;
		(checkShield) ? maxBullet = 30 : maxBullet = 15;
	}
}

void Laser_Gun::delete_ball(std::vector<sf::CircleShape>& bullet, int point)
{
	for (int i = 0; i < bullet.size() ; i++)
	{
		if (bullet[i].getGlobalBounds().intersects(fireball.getGlobalBounds()) && makeballmove)
		{
			fireball_health--;
			bullet.erase(bullet.begin() + i);
			i--;
			if (fireball_health == 0)
			{
				delete_ball_sound.play();
				fireball.setPosition(fireball_posx, fireball_posy);
				fireball_health = 6;
				pointcount_fireball = point + 400;
				makeballmove = false;
			}
		}
		if (bullet[i].getGlobalBounds().intersects(snowball.getGlobalBounds()) && makeSnowmove)
		{
			snowball_health--;
			bullet.erase(bullet.begin() + i);
			i--;
			if (snowball_health == 0)
			{
				delete_ball_sound.play();
				snowball.setPosition(fireball_posx, snowball_posy);
				snowball_health = 5;
				pointcount_snowball = point + 200;
				makeSnowmove = false;
			}
		}
	}
}

void Laser_Gun::restart(sf::RenderWindow* window, int& maxBullet)
{
	snowball.setPosition(window->getSize().x - 70.f, 32.f);
	fireball.setPosition(window->getSize().x - 70.f, 40.f);
	makeballmove = false;
	makeSnowmove = false;
	pointcount_snowball = 200;
	pointcount_fireball = 600;
	maxBullet = 15;
	snowball_health = 5;
	fireball_health = 6;
	fireball_bounce = 0;
}

