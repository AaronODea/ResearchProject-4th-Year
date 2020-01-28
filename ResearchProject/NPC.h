#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include <algorithm>
#include <iomanip>
#include <array>
#include <sstream>



class NPC
{
public:
	NPC(sf::RenderWindow& t_window ,sf::Font& t_font);
	~NPC();

	//++++++++++SET UP FUNCTIONS ++++++++++
	void setUpNpcStart(int t_ID);
	void setUpNpc(int t_ID);
	void setUpGAvar(int t_RT, int t_Age);//set up Genetic Alg

	//++++++++++GET FUNCTIONS ++++++++++
	sf::Vector2f getPos();
	int getID();
	float getSize();
	int getGender();
	int getAge();
	int getGenertaion();
	int getReproductionCooldown();
	std::array<float, 4> getDNA();
	bool isAlive();

	float GetSpeedStatistic();
	float GetStrStatistic();
	float GetIntStatistic();
	float GetSizeStatistic();


	//++++++++++SET FUNCTIONS ++++++++++
	void setPosition(sf::Vector2f t_pos);
	void setEndPosition(sf::Vector2f t_pos);
	void setDNA(std::array<float, 4> t_DNA);
	void setGenertaion(int t_gen);
	void setGender(int t_gender);

	//++++++++++FUNCTIONS ++++++++++
	void Draw();
	void Update();
	int randomNumber(int t_max, int t_min);//make a random number 
	void resetReproductionTimer();


	//  put into main system or set up gn Function_-------------------------------------------------------------------------
	int REPRODUCTION_TIME;
	int AGE_CAP;
	int m_mateingRange = 200;
	int m_ReproductionTimer = 0; //1 = 1 cycle
	float m_rateOfMutation = 25;


private:
	//text and displays;
	sf::Font m_font;
	sf::RenderWindow& m_window;


	sf::CircleShape m_mateingrandTemp;//temp circle for range of reprocuction 
	

	bool m_alive = true;
	int m_ID = NULL;

	int m_generation = 0;//generation of the NPC
	int m_gender = 0; // 0 = female     1 = male
	int m_age = 0;
	int m_health = 100;


	//variables for genetic algorithm
	float m_speed;
	float m_strength;
	float m_intelligence;
	float m_size;
	bool m_SequenceComplete = false; // when the end goal has been reached 


	//DNA sequence 
	std::string m_DNADisplay;
	std::stringstream m_speedStream;
	std::stringstream m_strengthStream;
	std::stringstream m_intelligenceStream;
	std::stringstream m_sizeStream;

	std::array<float, 4>  m_DNA;

	//++++++++++++++++++++++++TEXT+++++++++++++++++++++
	sf::Text m_DNAText;
	sf::Text m_GenerationText;
	sf::Text m_AgeText;

	//Health Bar 
	sf::RectangleShape m_healthBarBase;
	sf::RectangleShape m_healthBarFront;


	//sprite Visual
	sf::Sprite m_sprite;
	sf::Texture m_texture;


	//positions 
	sf::Vector2f m_position;
	sf::Vector2f m_endPosition;
	sf::Vector2f m_penSize;


	void wander();
};
