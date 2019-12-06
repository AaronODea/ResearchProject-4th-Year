#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>


class NPC
{
public:
	NPC(sf::RenderWindow& t_window ,sf::Font& t_font);
	~NPC();

	void setUpNpcStart(int t_ID);
	void setUpNpc(int t_ID);
	void setUpGAvar(int t_RT, int t_Age);


	void Draw();
	void Update();
	sf::Vector2f getPos();
	int getID();
	float getSize();
	int getGender();
	int getAge();
	int getGenertaion();
	int getReproductionCooldown();
	std::string getDNA();
	
	void setDNA(std::string t_DNA);
	void setPosition(sf::Vector2f t_pos);
	void setGenertaion(int t_gen);
	void setGender(int t_gender);

	void resetReproductionTimer();

	bool isAlive();

	void setUpGeneticAlg();

	//Const
	int REPRODUCTION_TIME;
	int AGE_CAP;

private:
	sf::RenderWindow& m_window;

	sf::CircleShape m_mateingrandTemp;
	

	bool m_alive = true;
	int m_ID = NULL;




	int m_mateingRange =  200;
	int m_generation = 0;
	int m_gender = 0; // 0 = female     1 = male
	int m_age = 0;
	int m_health = 100;


	//variables for genetic algorithm
	int m_ReproductionTimer = REPRODUCTION_TIME; //1 = 1 cycle

	int m_speed = (rand() % 5)+1;
	int m_strength = (rand() % 8) + 1;
	int m_intelligence = (rand() % 8) + 1;
	int m_size = (rand() % 4)+1;  

	//DNA sequence 
	std::string m_DNA =(	
						std::to_string(m_speed) +
						std::to_string(m_strength) + 
						std::to_string(m_intelligence) +
						std::to_string( static_cast<int>(m_size))
						);



	bool m_SequenceComplete  = false;
	int m_rateOfMutation = 25;



	//text and displays;
	sf::Font m_font;
	sf::Text m_DNAText;
	sf::Text m_GenerationText;
	sf::Text m_AgeText;

	sf::RectangleShape m_healthBarBase;
	sf::RectangleShape m_healthBarFront;





	//sprite Visual
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	sf::Vector2f m_position;
	sf::Vector2f m_endPosition;

	void wander();
};
