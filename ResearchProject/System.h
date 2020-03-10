#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <SFML/Graphics.hpp>
#include <random>
#include <array>
#include "NPC.h"
#include "Gui.h"




class System
{
public:
	System();
	~System();
	/// <summary>
	/// main method
	/// </summary>
	void run();

private:

	int WIDTH = 1920;
	int HEIGHT = 1080;
	sf::Vector2f m_penSize;


	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	bool m_exit; // control exiting 


	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	//++++++++++FUNCTION++++++++++
	int randomNumber(int t_max, int t_min);


	//++++++++++SET UP++++++++++
	void setupFontAndText();

	//++++++++++GA++++++++++
	void GAReproduction();
	void GAReproduce(NPC* t_npcOne, NPC* t_npcTwo);

	//++++++++++Get Statistics ++++++++++
	float GetAvgSpeed();
	float GetAvgStr();
	float GetAvgInt();
	float GetAvgSize();

	float m_avgStatistic = 0;


	//++++++++++CONST VARIABLE ++++++++++ 
	const int BREEDING_DISTANCE = 400;
	const int REPRODUCTION_CHANCE_THRESHOLD = 20; // 20  = 20% CHANCE OF REPRODUCTION
	const int REPRODUCTION_CHANCE = 100;   // Total % chance of reproduction 
	const int STARTER_AMOUNT = 10;


	//++++++++++GLOBAL VARIABLE ++++++++++
	int REPRODUCTION_INCREASE = 30; //increase in reproduction chance when a wanted trait is found 

	int REPRODUCTION_TIME = 300; // 300 = 3 years
	int AGE_CAP = 5000;  // 5000 = 50 years 

	std::array<float, 4> mutationArray = { 30,0,0,0 }; // mutation array for  the chance of mutation 
	std::array<int, 4> m_wantedStatistics = { 1,0,0,0 }; // 1= yes 0 = no




	//++++++++++NPCS VARIABLES ++++++++++
	int m_IDCount = 0;
	std::vector<NPC*> m_npcs;

	int m_distanceBetweenNPC = 0;
	int m_runningReproductionChance = REPRODUCTION_CHANCE;

	//++++++++++TEXT++++++++++
	//gender stat 
	int m_maleCount = 0;
	int m_femaleCount = 0;
	sf::Text m_maleCountText;
	sf::Text m_femaleCountText;

	//generation stat  
	int m_highestGen = 0;
	sf::Text m_highestGenText;

	//population
	int m_highestPopulation = 0;
	sf::Text m_totalNPC;
	sf::Text m_totalNPCAlltime;
	

	//++++++++++Sprites & Textures ++++++++++
	sf::Sprite m_backgroundSprite;
	sf::Texture m_backgroundTexture;

	sf::Sprite m_foregroundSprite;
	sf::Texture m_foregroundTexture;

	sf::Sprite m_heartSprite;
	sf::Texture m_heartTexture;


	//++++++++++GUI++++++++++
	GUI m_gui;

};

#endif // !SYSTEM_HPP

