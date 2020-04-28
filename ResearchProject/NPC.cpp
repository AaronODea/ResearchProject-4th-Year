#include "NPC.h"


NPC::NPC(sf::RenderWindow& t_window, sf::Font& t_font) :
	m_window(t_window),
	m_font(t_font)
{
	WIDTH = m_window.getSize().x;
	HEIGHT = m_window.getSize().y;
	m_penSize.x = (WIDTH / 1.28f);
	m_penSize.y = (HEIGHT / 1.578f);
	m_StartTimeReproduction = std::chrono::steady_clock::now();
	m_StartTimeAGE = std::chrono::steady_clock::now();

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

	m_window.draw(m_DNAString);
}

void NPC::Update()
{
	m_CurrentTimeReproduction = std::chrono::steady_clock::now();
	m_elapsedtimeReproduction = std::chrono::duration_cast<std::chrono::duration<double>>(m_CurrentTimeReproduction - m_StartTimeReproduction);

	m_CurrentTimeAGE = std::chrono::steady_clock::now();
	m_elapsedtimeAGE = std::chrono::duration_cast<std::chrono::duration<double>>(m_CurrentTimeAGE - m_StartTimeAGE);

	if (m_health <= 0)
	{
		m_alive = false;
	}

	//if (m_elapsedtimeReproduction.count() >= REPRODUCTION_TIME)
	//{

	//}

	m_age = m_elapsedtimeAGE.count();
	m_AgeText.setString("Age: " + std::to_string(m_age));

 	if (m_age >= m_runningAge)
	{
		m_deathChance = randomNumber(static_cast<int>(m_strength), 0);
		if (m_deathChance <= m_strength/2)
		{
			m_alive = false; 
		}
		else {m_runningAge = m_age + 1;
			if(m_age >= AGE_CAP *2){m_alive = false;}}
	}


	wander();

	m_healthBarBase.setPosition(sf::Vector2f(m_position.x, m_position.y - (m_texture.getSize().y) ));
	m_healthBarFront.setPosition(sf::Vector2f(m_position.x, m_position.y - (m_texture.getSize().y) ));

	m_healthBarFront.setSize(sf::Vector2f(m_health, m_healthBarFront.getSize().y));


	m_DNAText.setPosition(sf::Vector2f(m_healthBarBase.getPosition().x, m_healthBarBase.getPosition().y - (WIDTH / 90)));
	m_DNAString.setPosition(sf::Vector2f(m_healthBarBase.getPosition().x, m_healthBarBase.getPosition().y - (WIDTH / 90)));

	m_GenerationText.setPosition(sf::Vector2f(m_position.x + (m_texture.getSize().x) * 0.5f, m_position.y + (m_texture.getSize().y) * 0.5f));
	m_AgeText.setPosition(sf::Vector2f(m_DNAText.getPosition().x, m_DNAText.getPosition().y - (WIDTH / 100)));
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
sf::Vector2f NPC::getSizeTexture()
{
	return sf::Vector2f(m_texture.getSize());
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

std::chrono::duration<double> NPC::getReproductionCooldown()
{
	return m_elapsedtimeReproduction;
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
	m_StartTimeReproduction = std::chrono::steady_clock::now();
}

bool NPC::isAlive()
{
	return m_alive;
}

void NPC::wander()//wander function for npcs to wander around their pen
{
	if ((std::sqrt((m_endPosition.x - m_position.x) * (m_endPosition.x - m_position.x) + (m_endPosition.y - m_position.y) * (m_endPosition.y - m_position.y))) <= (HEIGHT/75)){
		m_endPosition.x = randomNumber(m_penSize.x, 0);
		m_endPosition.y = randomNumber(m_penSize.y, 0);}

	if (m_position.x >= m_endPosition.x) { m_position.x -= m_speed / (sizeRounded * m_speedScale); }
	if (m_position.x <= m_endPosition.x) { m_position.x += m_speed / (sizeRounded * m_speedScale); }
	if (m_position.y > m_endPosition.y) { m_position.y -= m_speed / (sizeRounded * m_speedScale); }
	if (m_position.y <= m_endPosition.y) { m_position.y += m_speed / (sizeRounded * m_speedScale); }

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
{return m_speed;}

float NPC::GetStrStatistic()
{return m_strength;}

float NPC::GetIntStatistic()
{return m_intelligence;}

float NPC::GetSizeStatistic()
{return m_size;}

void NPC::takeHealth(int t_reduction)
{
	m_health -= t_reduction;

	if (m_health <= 0){m_health = 0;}
	

}

//++++++++++SET UP FUNCTIONS ++++++++++

void NPC::setUpNpcStart(int t_ID)
{

	m_DNAString.setFont(m_font);
	

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
	m_DNAString << sf::Color::Black << "DNA: " <<
				   sf::Color(255, 102, 102) << m_speedStream.str() + ","<<
				   sf::Color(255, 178, 102) << m_strengthStream.str() + "," <<
				   sf::Color(255, 255, 102) << m_intelligenceStream.str() + "," <<
				   sf::Color(178, 255, 102) << m_sizeStream.str();



	m_DNAString.setPosition(sf::Vector2f(m_healthBarBase.getPosition().x - 50, m_healthBarBase.getPosition().y - 30));
	m_DNAString.setCharacterSize(WIDTH / 150);

	//set the ID of the NPC
	m_ID = t_ID;

	//Set the NPC Texture
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\Npc_sprite.png")) {std::cout << "problem loading Npc Texture" << std::endl;}
	m_sprite.setTexture(m_texture);

	//set gender
	if (m_gender == 0){
		m_gender = 0;
		m_sprite.setColor(sf::Color(255, 255, 0, 200));
	}
	else{
		m_gender = 1;
		m_sprite.setColor(sf::Color(0, 255, 255, 200));
	}

	//set size,origin and scale 

	if (m_size <= 50) {
		m_speedScale = 0.99f;
		if (m_size <= 10) { m_sizeScale = 0.08f; sizeRounded = 10;	}
		else if (m_size <= 20) { m_sizeScale = 0.07f; sizeRounded = 20;}
		else if (m_size <= 30) { m_sizeScale = 0.06f; sizeRounded = 30;}
		else if (m_size <= 40) { m_sizeScale = 0.05f; sizeRounded = 40;}
		else { m_sizeScale = 0.04f; sizeRounded = 50;}
	}
	else {
		if (m_size <= 60) { m_sizeScale = 0.035f; sizeRounded = 60; m_speedScale = 0.6f;}
		else if (m_size <= 70) { m_sizeScale = 0.037f; sizeRounded = 70; m_speedScale = 0.7f;}
		else if (m_size <= 80) { m_sizeScale = 0.039f; sizeRounded = 80; m_speedScale = 0.8f;}
		else if (m_size <= 90) { m_sizeScale = 0.041f; sizeRounded = 90; m_speedScale = 0.9f;}
		else { m_sizeScale = 0.042f; sizeRounded = 100; m_speedScale = 1;}
	}
	m_sprite.setScale(sizeRounded * m_sizeScale, sizeRounded *m_sizeScale);
	m_sprite.setOrigin(m_sprite.getScale().x / 2, m_sprite.getScale().y / 2);



	//set the starting position of the NPCs
	m_position = sf::Vector2f(WIDTH / 2, HEIGHT / 2);
	m_sprite.setPosition(m_position);

	//Set a random postion within the Pen for the NPCS to walk to0
	m_endPosition.x = randomNumber(m_penSize.x, 0);
	m_endPosition.y = randomNumber(m_penSize.y, 0);

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
	m_DNAString.setPosition(sf::Vector2f(m_healthBarBase.getPosition().x - 50, m_healthBarBase.getPosition().y - 30));
	m_DNAString.setFont(m_font);
	m_DNAString.setCharacterSize(WIDTH / 150);

	//generation text 
	m_GenerationText.setString(std::to_string(m_generation));
	m_GenerationText.setOrigin(m_sprite.getOrigin());
	m_GenerationText.setPosition(sf::Vector2f(m_position.x + (m_texture.getSize().x) * .5, m_position.y + (m_texture.getSize().y) * .5));
	m_GenerationText.setFont(m_font);
	m_GenerationText.setFillColor(sf::Color::Black);
	m_GenerationText.setCharacterSize(WIDTH / 150);

	//age text 
	m_AgeText.setString("Age: " + std::to_string((m_age)));
	m_AgeText.setPosition(sf::Vector2f(m_DNAText.getPosition().x, m_DNAText.getPosition().y - WIDTH/125));
	m_AgeText.setFont(m_font);
	m_AgeText.setFillColor(sf::Color::Black);
	m_AgeText.setCharacterSize(WIDTH / 150);


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
	m_DNAString.setFont(m_font);
	m_DNAString << sf::Color::Black << "DNA: " <<
		sf::Color(255, 102, 102) << m_speedStream.str() + "," <<
		sf::Color(255, 178, 102) << m_strengthStream.str() + "," <<
		sf::Color(255, 255, 102) << m_intelligenceStream.str() + "," <<
		sf::Color(178, 255, 102) << m_sizeStream.str();

	//set the ID of the NPC
	m_ID = t_ID;
	  
	//Set the NPC Texture
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\Npc_sprite.png")) {std::cout << "problem loading Npc Texture" << std::endl;}
	m_sprite.setTexture(m_texture);

	//set gender
	if (randomNumber(1, 0) == 0){
		m_gender = 0;
		m_sprite.setColor(sf::Color::Yellow);
	}
	else{
		m_gender = 1;
		m_sprite.setColor(sf::Color::Cyan);
	}

	//set size,origin and scale 

	if (m_size <= 50) {
		m_speedScale = 0.99f;
		if (m_size <= 10) { m_sizeScale = 0.08f; sizeRounded = 10; }
		else if (m_size <= 20) { m_sizeScale = 0.07f; sizeRounded = 20; }
		else if (m_size <= 30) { m_sizeScale = 0.06f; sizeRounded = 30; }
		else if (m_size <= 40) { m_sizeScale = 0.05f; sizeRounded = 40; }
		else { m_sizeScale = 0.04f; sizeRounded = 50; }
	}
	else {
		if (m_size <= 60) { m_sizeScale = 0.035f; sizeRounded = 60; m_speedScale = 0.6f; }
		else if (m_size <= 70) { m_sizeScale = 0.037f; sizeRounded = 70; m_speedScale = 0.7f; }
		else if (m_size <= 80) { m_sizeScale = 0.039f; sizeRounded = 80; m_speedScale = 0.8f; }
		else if (m_size <= 90) { m_sizeScale = 0.041f; sizeRounded = 90; m_speedScale = 0.9f; }
		else { m_sizeScale = 0.042f; sizeRounded = 100; m_speedScale = 1; }
	}
	m_sprite.setScale(sizeRounded * m_sizeScale, sizeRounded * m_sizeScale);
	m_sprite.setOrigin(m_sprite.getScale().x / 2, m_sprite.getScale().y / 2);



	//set the starting position of the NPCs
	m_position = sf::Vector2f(WIDTH / 2, HEIGHT / 2);
	m_sprite.setPosition(m_position);

	//Set a random postion within the Pen for the NPCS to walk to0
	m_endPosition.x = randomNumber(m_penSize.x, 0);
	m_endPosition.y = randomNumber(m_penSize.y, 0);

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
	m_DNAString.setPosition(sf::Vector2f(m_healthBarBase.getPosition().x - 50, m_healthBarBase.getPosition().y - 30));
	m_DNAString.setFont(m_font);
	m_DNAString.setCharacterSize(WIDTH / 150);

	//generation text 
	m_GenerationText.setString(std::to_string(m_generation));
	m_GenerationText.setOrigin(m_sprite.getOrigin());
	m_GenerationText.setPosition(sf::Vector2f(m_position.x + (m_texture.getSize().x) * .5, m_position.y + (m_texture.getSize().y) * .5));
	m_GenerationText.setFont(m_font);
	m_GenerationText.setFillColor(sf::Color::Black);
	m_GenerationText.setCharacterSize(WIDTH / 150);

	//age text 
	m_AgeText.setString("Age: " + std::to_string((m_age)));
	m_AgeText.setPosition(sf::Vector2f(m_DNAText.getPosition().x, m_DNAText.getPosition().y - WIDTH / 125));
	m_AgeText.setFont(m_font);
	m_AgeText.setFillColor(sf::Color::Black);
	m_AgeText.setCharacterSize(WIDTH / 150);


	resetReproductionTimer();
}

void NPC::setUpGAvar(int t_RT, int t_Age)
{
	REPRODUCTION_TIME = t_RT;
	AGE_CAP = t_Age;
	m_runningAge = (t_Age-((t_Age / 9)));
}
