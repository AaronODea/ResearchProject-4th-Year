#include "NPC.h"


NPC::NPC(sf::RenderWindow& t_window, sf::Font& t_font):
m_window(t_window),
m_font(t_font)
{
}

NPC::~NPC()
{
}

void NPC::Draw()
{
	//m_window.draw(m_mateingrandTemp);
	m_window.draw(m_sprite);
	m_window.draw(m_DNAText);
	m_window.draw(m_GenerationText);
	m_window.draw(m_AgeText);
	m_window.draw(m_healthBarBase);
	m_window.draw(m_healthBarFront);

}

void NPC::Update()
{
	
	if (m_ReproductionTimer >= 0) { m_ReproductionTimer--; }
	if (m_age <= AGE_CAP) { m_age++; m_AgeText.setString("Age: " + std::to_string(m_age)); }
	else {m_alive = false;}


	wander();
	m_mateingrandTemp.setPosition(m_position);
	
	m_healthBarBase.setPosition(sf::Vector2f(m_position.x, m_position.y - m_size*15));
	m_healthBarFront.setPosition(sf::Vector2f(m_position.x, m_position.y - m_size *15));

	m_DNAText.setPosition(sf::Vector2f(m_healthBarBase.getPosition().x-50, m_healthBarBase.getPosition().y - 30));
	m_GenerationText.setPosition(m_position);
	m_AgeText.setPosition(sf::Vector2f(m_DNAText.getPosition().x, m_DNAText.getPosition().y - 20));



}

sf::Vector2f NPC::getPos()
{
	return m_position;
}

int NPC::getID()
{
	return m_ID;
}

float NPC::getSize()
{
	return m_size;
}

int NPC::getGender()
{
	return m_gender;
}

int NPC::getAge()
{
	return m_age;
}

int NPC::getGenertaion()
{
	return m_generation;
}

int NPC::getReproductionCooldown()
{
	return m_ReproductionTimer;
}

std::string NPC::getDNA()
{
	return m_DNA;
}

void NPC::setDNA(std::string t_DNA)
{

	m_DNA = t_DNA;
}

void NPC::setPosition(sf::Vector2f t_pos)
{
	m_position = t_pos;
}

void NPC::setEndPosition(sf::Vector2f t_pos)
{
	m_endPosition = t_pos;
}

void NPC::setGenertaion(int t_gen)
{
	m_generation = t_gen;
}

void NPC::setGender(int t_gender)
{
	m_gender = t_gender;
}

void NPC::resetReproductionTimer()
{
 m_ReproductionTimer = REPRODUCTION_TIME;
}

bool NPC::isAlive ()
{
	return m_alive;
}

void NPC::setUpGeneticAlg()
{
}

void NPC::wander()
{
	if ((std::sqrt((m_endPosition.x - m_position.x) * (m_endPosition.x - m_position.x)+(m_endPosition.y - m_position.y) * (m_endPosition.y - m_position.y)))  <= 20)
	{
		m_endPosition = sf::Vector2f(rand() % m_window.getSize().x, rand() % m_window.getSize().y);
	}

	if (m_position.x >= m_endPosition.x) { m_position.x -= m_speed; }
	if(m_position.x <= m_endPosition.x) { m_position.x += m_speed; }
	if (m_position.y > m_endPosition.y) { m_position.y -= m_speed; }
	if (m_position.y <= m_endPosition.y) { m_position.y += m_speed; }

	m_sprite.setPosition(m_position);

	
}

void NPC::setUpNpcStart(int t_ID)
{
	m_ID = t_ID;
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\Npc_sprite.png"))
	{
		std::cout << "problem loading Npc Texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);

	if (m_gender == 0)
	{
		m_gender = 0;
		m_sprite.setColor(sf::Color::Yellow);
	}
	else
	{
		m_gender = 1;
		m_sprite.setColor(sf::Color::Cyan);
	}

	m_sprite.setScale(m_size, m_size);
	m_sprite.setOrigin(m_texture.getSize().x / 2,m_texture.getSize().y / 2);
	m_position = sf::Vector2f(800,800);


	m_sprite.setPosition(m_position);

	m_endPosition = sf::Vector2f(rand() % m_window.getSize().x, rand() % m_window.getSize().y);


	//circle for reproduction
	m_mateingrandTemp.setRadius(m_mateingRange);
	m_mateingrandTemp.setOutlineColor(sf::Color::Red);
	m_mateingrandTemp.setOutlineThickness(10);
	m_mateingrandTemp.setFillColor(sf::Color::Transparent);
	m_mateingrandTemp.setPosition(m_position);
	m_mateingrandTemp.setOrigin(m_mateingRange, m_mateingRange);


	//Health Bar.
	m_healthBarBase.setFillColor(sf::Color(169, 169, 169));
	m_healthBarBase.setOutlineColor(sf::Color::Black);
	m_healthBarBase.setSize(sf::Vector2f(100, 10));
	m_healthBarBase.setOrigin(m_healthBarBase.getSize().x / 2, m_healthBarBase.getSize().y / 2);
	m_healthBarBase.setPosition(sf::Vector2f(m_position.x, m_position.y + m_size * 2));

	m_healthBarFront.setFillColor(sf::Color::Red);
	m_healthBarFront.setSize(sf::Vector2f(100, 10));
	m_healthBarFront.setOrigin(m_healthBarBase.getSize().x / 2, m_healthBarBase.getSize().y / 2);
	m_healthBarFront.setPosition(sf::Vector2f(m_position.x, m_position.y + m_size * 10));



	//DNA text 
	m_DNAText.setString("DNA: "+m_DNA);
	m_DNAText.setPosition(sf::Vector2f(m_healthBarBase.getPosition().x - 50, m_healthBarBase.getPosition().y - 30));
	m_DNAText.setFont(m_font);
	m_DNAText.setFillColor(sf::Color::Black);
	m_DNAText.setCharacterSize(20);

	//generation text 
	m_GenerationText.setString(std::to_string(m_generation));
	m_GenerationText.setPosition(m_position);
	m_GenerationText.setFont(m_font);
	m_GenerationText.setFillColor(sf::Color::Black);
	m_GenerationText.setCharacterSize(10);

	//age text 
	m_AgeText.setString("Age: " + std::to_string(m_age));
	m_AgeText.setPosition(sf::Vector2f(m_DNAText.getPosition().x, m_DNAText.getPosition().y - 20));
	m_AgeText.setFont(m_font);
	m_AgeText.setFillColor(sf::Color::Black);
	m_AgeText.setCharacterSize(20);

	std::cout << "ID:" + std::to_string(m_ID) << std::endl;
	std::cout << "DNA:" + m_DNA << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;
	resetReproductionTimer();
}

void NPC::setUpNpc(int t_ID)
{
	m_ID = t_ID;
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\Npc_sprite.png"))
	{
		std::cout << "problem loading Npc Texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);

	if ((rand() % 2) == 0)
	{
		m_gender = 0;
		m_sprite.setColor(sf::Color::Yellow);
	}
	else
	{
		m_gender = 1;
		m_sprite.setColor(sf::Color::Cyan);
	}

	m_sprite.setScale(m_size, m_size);
	m_sprite.setOrigin( m_texture.getSize().x /2,m_texture.getSize().y /2);
	m_sprite.setPosition(m_position);
	
	m_endPosition = sf::Vector2f(rand() % m_window.getSize().x, rand() % m_window.getSize().y);
	
	//circle for reproduction
	m_mateingrandTemp.setRadius(m_mateingRange);
	m_mateingrandTemp.setOutlineColor(sf::Color::Red);
	m_mateingrandTemp.setOutlineThickness(10);
	m_mateingrandTemp.setFillColor(sf::Color::Transparent);
	m_mateingrandTemp.setPosition(m_position);
	m_mateingrandTemp.setOrigin(m_mateingRange, m_mateingRange);	

	//Health Bar.
	m_healthBarBase.setFillColor(sf::Color(169, 169, 169));
	m_healthBarBase.setOutlineColor(sf::Color::Black);
	m_healthBarBase.setSize(sf::Vector2f(100, 10));
	m_healthBarBase.setOrigin(m_healthBarBase.getSize().x / 2, m_healthBarBase.getSize().y / 2);
	m_healthBarBase.setPosition(sf::Vector2f(m_position.x, m_position.y + m_size * 2));

	m_healthBarFront.setFillColor(sf::Color::Red);
	m_healthBarFront.setSize(sf::Vector2f(100, 10));
	m_healthBarFront.setOrigin(m_healthBarBase.getSize().x / 2, m_healthBarBase.getSize().y / 2);
	m_healthBarFront.setPosition(sf::Vector2f(m_position.x, m_position.y + m_size * 10));

	//DNA text 
	m_DNAText.setString("DNA: " + m_DNA);
	m_DNAText.setPosition(sf::Vector2f(m_healthBarBase.getPosition().x - 50, m_healthBarBase.getPosition().y - 30));
	m_DNAText.setFont(m_font);
	m_DNAText.setFillColor(sf::Color::Black);
	m_DNAText.setCharacterSize(20);

	//generation text 
	m_GenerationText.setString(std::to_string(m_generation));
	m_GenerationText.setPosition(m_position);
	m_GenerationText.setFont(m_font);
	m_GenerationText.setFillColor(sf::Color::Black);
	m_GenerationText.setCharacterSize(10);

	//age text 
	m_AgeText.setString("Age: " + std::to_string(m_age));
	m_AgeText.setPosition(sf::Vector2f(m_DNAText.getPosition().x, m_DNAText.getPosition().y - 20));
	m_AgeText.setFont(m_font);
	m_AgeText.setFillColor(sf::Color::Black);
	m_AgeText.setCharacterSize(20);
}

void NPC::setUpGAvar(int t_RT, int t_Age)
{
	REPRODUCTION_TIME = t_RT;
	AGE_CAP = t_Age;
}
