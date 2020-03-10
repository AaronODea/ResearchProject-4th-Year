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
	m_window.draw(m_GenerationText);

}

void NPC::DrawStatistics()
{
	m_window.draw(m_DNAText);
	m_window.draw(m_AgeText);
	m_window.draw(m_healthBarBase);
	m_window.draw(m_healthBarFront);
}

void NPC::Update()
{
	
	if (m_ReproductionTimer >= 0) { m_ReproductionTimer--; }
	if (m_age <= AGE_CAP) { m_age++; m_AgeText.setString("Age: " + std::to_string(m_age/100)); }
	else {m_alive = false;}


	wander();


	m_mateingrandTemp.setPosition(m_position);
	
	m_healthBarBase.setPosition(sf::Vector2f(m_position.x, m_position.y - (m_texture.getSize().y)*2.5 ));
	m_healthBarFront.setPosition(sf::Vector2f(m_position.x, m_position.y - (m_texture.getSize().y) * 2.5));

	m_DNAText.setPosition(sf::Vector2f(m_healthBarBase.getPosition().x, m_healthBarBase.getPosition().y - 30));
	m_GenerationText.setPosition(sf::Vector2f(m_position.x + (m_texture.getSize().x) * .5, m_position.y + (m_texture.getSize().y) * .5));
	m_AgeText.setPosition(sf::Vector2f(m_DNAText.getPosition().x, m_DNAText.getPosition().y - 20));
}


//++++++++++GET FUNCTIONS +++++++++
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

std::array<float, 4> NPC::getDNA()
{
	return m_DNA;
}


//++++++++++SETER FUNCTIONS ++++++++++
void NPC::setDNA(std::array<float, 4> t_DNA)
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



//++++++++++FUNCTIONS ++++++++++
void NPC::resetReproductionTimer()
{
 m_ReproductionTimer = REPRODUCTION_TIME;
}

bool NPC::isAlive ()
{
	return m_alive;
}

void NPC::wander()
{
	if ((std::sqrt((m_endPosition.x - m_position.x) * (m_endPosition.x - m_position.x)+(m_endPosition.y - m_position.y) * (m_endPosition.y - m_position.y)))  <= 20)
	{
		m_penSize.x =randomNumber(m_window.getSize().x,0);
		m_penSize.y = randomNumber(m_window.getSize().y, 0);

		if (m_penSize.x > 1950){m_penSize.x = 1950;}
		if (m_penSize.y > 950){ m_penSize.y = 950; }

		m_endPosition = m_penSize;
	}

	if (m_position.x >= m_endPosition.x ) { m_position.x -= m_speed / (m_size * .9); }
	if(m_position.x <= m_endPosition.x) { m_position.x += m_speed / (m_size * .9); }
	if (m_position.y > m_endPosition.y ) { m_position.y -= m_speed / (m_size * .9); }
	if (m_position.y <= m_endPosition.y ) { m_position.y += m_speed / (m_size*.9); }

	m_sprite.setPosition(m_position);

	
}

int NPC::randomNumber(int t_max, int t_min)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(t_min, t_max);

	return dist(rng);
}
//++++++++++GETTER FUNCTIONS++++++++++
float NPC::GetSpeedStatistic()
{
	return m_speed;
}

float NPC::GetStrStatistic()
{
	return m_speed;
}

float NPC::GetIntStatistic()
{
	return m_intelligence;
}

float NPC::GetSizeStatistic()
{
	return m_size;
}

//++++++++++SET UP FUNCTIONS ++++++++++

void NPC::setUpNpcStart(int t_ID)
{

	//randomise the starters DNA
	m_speed = (randomNumber(m_Statistic_cap, 1));
	m_strength = (randomNumber(m_Statistic_cap, 1));
	m_intelligence = (randomNumber(m_Statistic_cap, 1));
	m_size = (randomNumber(m_Statistic_cap, 1));

	//DNA sequence 
	m_DNA[0] = m_speed;
	m_DNA[1] = m_strength;
	m_DNA[2] = m_intelligence;
	m_DNA[3] = m_size;

	//set all of the streams to 2 decimals points 
	m_speedStream << std::fixed << std::setprecision(1) << m_speed;
	m_strengthStream << std::fixed << std::setprecision(1) << m_strength;
	m_intelligenceStream << std::fixed << std::setprecision(1) << m_intelligence;
	m_sizeStream << std::fixed << std::setprecision(1) << m_size;

	//make the Dna String for display
	m_DNADisplay =
		m_speedStream.str()+ "," +
		m_strengthStream.str() + "," +
		m_intelligenceStream.str() + "," +
		m_sizeStream.str();

	//set the ID of the NPC
	m_ID = t_ID;
	
	//Set the NPC Texture
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\Npc_sprite.png"))
	{
		std::cout << "problem loading Npc Texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);

	//set gender
	if (m_gender == 0)
	{
		m_gender = 0;
		m_sprite.setColor(sf::Color(255, 255, 0,200));
	}
	else
	{
		m_gender = 1;
		m_sprite.setColor(sf::Color(0, 255, 255,200));
	}

	//set size,origin and scale 

	if (m_size < 20.0f)
	{
		if (m_size < 10.0f)
		{m_sprite.setScale(m_size * .3, m_size * .3);}
		else {m_sprite.setScale(m_size * .2, m_size * .2);}
	}
	else{m_sprite.setScale(m_size * .06, m_size * .06);}
	m_sprite.setOrigin(m_sprite.getScale().x / 2, m_sprite.getScale().y / 2);

	//set the starting position of the NPCs
	m_position = sf::Vector2f(800,800);
	m_sprite.setPosition(m_position);

	//Set a random postion within the Pen for the NPCS to walk to0
	m_penSize.x = randomNumber(m_window.getSize().x,0);
	m_penSize.y = randomNumber(m_window.getSize().y, 0);

	if (m_penSize.x > 1950) { m_penSize.x = 1950; }	//size of pen for npcs 
	if (m_penSize.y > 950) { m_penSize.y = 950; }
	m_endPosition = m_penSize;

	////++++++++++++++++++++++++++TEXT SETUP++++++++++++++++++++++++++
	////Health Bar.
	m_healthBarBase.setFillColor(sf::Color(169, 169, 169));
	m_healthBarBase.setOutlineColor(sf::Color::Black);
	m_healthBarBase.setSize(sf::Vector2f(100, 10));
	m_healthBarBase.setOrigin(m_sprite.getOrigin());
	m_healthBarBase.setPosition(sf::Vector2f(m_position.x, m_position.y - (m_texture.getSize().y) * 2.5));


	////front of health bar
	m_healthBarFront.setFillColor(sf::Color::Red);
	m_healthBarFront.setSize(sf::Vector2f(100, 10));
	m_healthBarFront.setOrigin(m_sprite.getOrigin());
	m_healthBarFront.setPosition(sf::Vector2f(m_position.x, m_position.y - (m_texture.getSize().y) * 2.5));


	//DNA text 
	m_DNAText.setString("DNA: "+ m_DNADisplay);
	m_DNAText.setPosition(sf::Vector2f(m_healthBarBase.getPosition().x - 50, m_healthBarBase.getPosition().y - 30));
	m_DNAText.setFont(m_font);
	m_DNAText.setFillColor(sf::Color::Black);
	m_DNAText.setCharacterSize(20);

	//generation text 
	m_GenerationText.setString(std::to_string(m_generation));
	m_GenerationText.setOrigin(m_sprite.getOrigin());
	m_GenerationText.setPosition(sf::Vector2f(m_position.x + (m_texture.getSize().x) * .5, m_position.y + (m_texture.getSize().y) * .5));
	m_GenerationText.setFont(m_font);
	m_GenerationText.setFillColor(sf::Color::Black);
	m_GenerationText.setCharacterSize(20);

	//age text 
	m_AgeText.setString("Age: " + std::to_string((m_age)));
	m_AgeText.setPosition(sf::Vector2f(m_DNAText.getPosition().x, m_DNAText.getPosition().y - 20));
	m_AgeText.setFont(m_font);
	m_AgeText.setFillColor(sf::Color::Black);
	m_AgeText.setCharacterSize(20);

	//cmd out of inital ID's
	std::cout << "ID:" + std::to_string(m_ID) << std::endl;
	std::cout << "DNA: " + m_DNADisplay << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;
	resetReproductionTimer();
}
void NPC::setUpNpc(int t_ID)
{
	//randomise the starters DNA
	m_speed = m_DNA[0];
	m_strength = m_DNA[1];
	m_intelligence = m_DNA[2];
	m_size = m_DNA[3];

	//set all of the streams to 2 decimals points 
	m_speedStream << std::fixed << std::setprecision(1) << m_speed;
	m_strengthStream << std::fixed << std::setprecision(1) << m_strength;
	m_intelligenceStream << std::fixed << std::setprecision(1) << m_intelligence;
	m_sizeStream << std::fixed << std::setprecision(1) << m_size;

	//make the Dna String for display
	m_DNADisplay =
		m_speedStream.str() + "," +
		m_strengthStream.str() + "," +
		m_intelligenceStream.str() + "," +
		m_sizeStream.str();

	//set the ID of the NPC
	m_ID = t_ID;

	//Set the NPC Texture
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\Npc_sprite.png"))
	{
		std::cout << "problem loading Npc Texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);

	//set gender
	if (randomNumber(1, 0) == 0)
	{
		m_gender = 0;
		m_sprite.setColor(sf::Color::Yellow);
	}
	else
	{
		m_gender = 1;
		m_sprite.setColor(sf::Color::Cyan);
	}


	//set size,origin and scale 
	if (m_size < 20.0f)
	{
		if (m_size < 10.0f)
		{
			m_sprite.setScale(m_size * .3, m_size * .3);
		}
		else { m_sprite.setScale(m_size * .2, m_size * .2); }
	}
	else { m_sprite.setScale(m_size * .06, m_size * .06); }
	m_sprite.setOrigin(m_sprite.getScale().x / 2, m_sprite.getScale().y / 2);

	//set the starting position of the NPCs
	m_sprite.setPosition(m_position);

	//Set a random postion within the Pen for the NPCS to walk to0
	m_penSize.x = randomNumber(m_window.getSize().x, 0);
	m_penSize.y = randomNumber(m_window.getSize().y, 0);

	if (m_penSize.x > 1950) { m_penSize.x = 1950; }//size of pen for npcs 
	if (m_penSize.y > 950) { m_penSize.y = 950; }
	m_endPosition = m_penSize;


	//++++++++++++++++++++++++++TEXT SETUP++++++++++++++++++++++++++
	////Health Bar.
	m_healthBarBase.setFillColor(sf::Color(169, 169, 169));
	m_healthBarBase.setOutlineColor(sf::Color::Black);
	m_healthBarBase.setSize(sf::Vector2f(100, 10));
	m_healthBarBase.setOrigin(m_sprite.getOrigin());
	m_healthBarBase.setPosition(sf::Vector2f(m_position.x, m_position.y - (m_texture.getSize().y) * 2.5));


	////front of health bar
	m_healthBarFront.setFillColor(sf::Color::Red);
	m_healthBarFront.setSize(sf::Vector2f(100, 10));
	m_healthBarFront.setOrigin(m_sprite.getOrigin());
	m_healthBarFront.setPosition(sf::Vector2f(m_position.x, m_position.y - (m_texture.getSize().y) * 2.5));


	//DNA text 
	m_DNAText.setString("DNA: " + m_DNADisplay);
	m_DNAText.setPosition(sf::Vector2f(m_healthBarBase.getPosition().x - 50, m_healthBarBase.getPosition().y - 30));
	m_DNAText.setFont(m_font);
	m_DNAText.setFillColor(sf::Color::Black);
	m_DNAText.setCharacterSize(20);

	//generation text 
	m_GenerationText.setString(std::to_string(m_generation));
	m_GenerationText.setOrigin(m_sprite.getOrigin());
	m_GenerationText.setPosition(sf::Vector2f(m_position.x + (m_texture.getSize().x) * .5, m_position.y + (m_texture.getSize().y) * .5));
	m_GenerationText.setFont(m_font);
	m_GenerationText.setFillColor(sf::Color::Black);
	m_GenerationText.setCharacterSize(20);

	//age text 
	m_AgeText.setString("Age: " + std::to_string((m_age)));
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
