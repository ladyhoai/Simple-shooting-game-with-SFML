#include "Animation.h"

void animation::breaker(sf::RectangleShape shape)
{
	shape1.setFillColor(sf::Color(shape.getFillColor()));
	shape1.setSize(sf::Vector2f(shape.getSize().x / 2 + 0.5f, shape.getSize().y / 2 + 0.5f));
	
	shape2.setFillColor(sf::Color(shape.getFillColor()));
	shape2.setSize(sf::Vector2f(shape.getSize().x / 2 + 0.5f, shape.getSize().y / 2 + 0.5f));

	shape1.setPosition(shape.getPosition().x, shape.getPosition().y);
	shape2.setPosition(shape.getPosition().x + 12.5f, shape.getPosition().y);

	//Store shape and offset value in a vector
	store_shape1.push_back(shape1);
	store_shape2.push_back(shape2);

	m_offset1.push_back(offset);
	m_offset2.push_back(offset);
}


void animation::RenderBreak(sf::RenderWindow* window)
{
	for (auto& i : store_shape1)
	{
		window->draw(i);
	}
	for (auto& a : store_shape2)
	{
		window->draw(a);
	}
}

//Animate enemies' death
void animation::updateBreaker(sf::RenderWindow* window)
{
	for (int i = 0; i < store_shape1.size(); i++)
	{
		//offset += 0.005f;
		//store_shape1[i].move(sf::Vector2f(0, 10.f));
		m_offset1[i] += 0.005f;
		m_shape1posx = store_shape1[i].getPosition().x + m_offset1[i];
		m_shape1posy = store_shape1[i].getPosition().y + (-pow(m_offset1[i], 4) + 50 * pow(m_offset1[i], 2) - 1 );
		store_shape1[i].setPosition(m_shape1posx, m_shape1posy);

		if (store_shape1[i].getPosition().y > window->getSize().y || store_shape1[i].getPosition().x > window->getSize().x ||
			store_shape1[i].getPosition().x < 0)
		{
			store_shape1.erase(store_shape1.begin() + i);
			m_offset1.erase(m_offset1.begin() + i);
			i--;
			//offset = 0;
		}
	}

	for (int i = 0; i < store_shape2.size(); i++)
	{
		//store_shape2[i].move(sf::Vector2f(0, 5.f));
		m_offset2[i] += 0.005f;
		m_shape2posx = store_shape2[i].getPosition().x - m_offset2[i];
		m_shape2posy = store_shape2[i].getPosition().y + (-pow(m_offset2[i], 4) + 50 * pow(m_offset2[i], 2) - 1);
		store_shape2[i].setPosition(m_shape2posx, m_shape2posy);
		if (store_shape2[i].getPosition().y > window->getSize().y || store_shape2[i].getPosition().x > window->getSize().x ||
			store_shape2[i].getPosition().x < 0)
		{
			store_shape2.erase(store_shape2.begin() + i);
			m_offset2.erase(m_offset2.begin() + i);
			i--;
		}
	}
}

//animation::animation()
//{
	//shape1.setFillColor(sf::Color(40, 32, 54));
	//shape1.setSize(sf::Vector2f(20.5f, 20.5f));
	//shape1.setOutlineThickness(1.f);
	//shape2.setFillColor(sf::Color(40, 32, 54));
	//shape2.setSize(sf::Vector2f(20.5f, 20.5f));
	//shape2.setOutlineThickness(1.f);
//}
