#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include <vector>
#include <cmath>

class animation
{
private:
	sf::RectangleShape shape1;
	sf::RectangleShape shape2;
	float m_shape1posx = 0;
	float m_shape1posy = 0;
	float m_shape2posx = 0;
	float m_shape2posy = 0;
	std::vector <float> m_offset1;
	std::vector <float> m_offset2;

	float offset = 0;
	std::vector<sf::RectangleShape> store_shape1;
	std::vector<sf::RectangleShape> store_shape2;

public:
	void breaker(sf::RectangleShape shape);
	void RenderBreak(sf::RenderWindow * window);
	void updateBreaker(sf::RenderWindow* window);
//	void store_shape();
	//animation();
};

