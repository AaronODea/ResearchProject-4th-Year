#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class NPC
{
public:
	NPC(sf::RenderWindow& t_window);
	~NPC();

	void setUpNpc();

	void Draw();
	void Update();
	void getPos();
	

private:
	sf::RenderWindow& m_window;

	//sprite Visual
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	sf::Vector2f m_position;
	sf::Vector2f m_endPosition;

	void wander();
	
	

};
