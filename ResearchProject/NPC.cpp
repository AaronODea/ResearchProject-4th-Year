#include "NPC.h"


NPC::NPC(sf::RenderWindow& t_window):
m_window(t_window)
{
}

NPC::~NPC()
{
}

void NPC::Draw()
{
	m_window.draw(m_sprite);
}

void NPC::Update()
{
	wander();
}

void NPC::getPos()
{

	//std::cout << m_endPosition.x << "," << m_endPosition.y << std::endl;
}

void NPC::wander()
{
	if ((std::sqrt((m_endPosition.x - m_position.x) * (m_endPosition.x - m_position.x)+(m_endPosition.y - m_position.y) * (m_endPosition.y - m_position.y)))  <= 20)
	{
		m_endPosition = sf::Vector2f(rand() % m_window.getSize().x, rand() % m_window.getSize().y);
	}

	if (m_position.x >= m_endPosition.x) { m_position.x -= 1; }
	if(m_position.x <= m_endPosition.x) { m_position.x += 1; }
	if (m_position.y > m_endPosition.y) { m_position.y -= 1; }
	if (m_position.y <= m_endPosition.y) { m_position.y += 1; }

	m_sprite.setPosition(m_position);

	
}

void NPC::setUpNpc()
{
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\Npc_sprite.png"))
	{
		std::cout << "problem loading Npc Texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);


	if ((rand() % 2) == 0)
	{
		m_sprite.setColor(sf::Color::Yellow);
	}
	else
	{
		m_sprite.setColor(sf::Color::Cyan);
	}

	m_sprite.setOrigin(m_sprite.getScale().x / 2, m_sprite.getScale().y / 2);
	m_position = sf::Vector2f(sf::Vector2f((rand() % m_window.getSize().x), 500));
	m_sprite.setPosition(m_position);
	
	m_endPosition = sf::Vector2f(rand() % m_window.getSize().x, rand() % m_window.getSize().y);
		
	


}
