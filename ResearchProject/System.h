#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "RichText.h"
#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include <random>
#include <array>
#include "NPC.h"
#include "Gui.h"
#include <chrono>
#include <ctime>
#include <cmath>
#include <fstream>

enum STATES { m_startingScreen, m_mainScreen};

class System
{
public:
	System();
	~System();
	
	STATES m_currentState;
	


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
	void makefile();
	
	//++++++++++FUNCTION++++++++++
	int randomNumber(int t_max, int t_min);
	std::stringstream setMutation(float t_mutation);

	//++++++++++Events++++++++++

	void EventCall();

	void SpeedEvent();
	void StrEvent();
	void intEvent();
	void SizeEvent();


	//++++++++++SET UP++++++++++
	void setupFontAndText();
	void setUpGuiStates();

	void reset();
	//++++++++++GA++++++++++
	void GAStartUp();
	void GAReproductionWanted();
	void GAReproductionHighest();
	void GAReproduceAVG(NPC* t_npcOne, NPC* t_npcTwo);
	void GAReproduceSplit(NPC* t_npcOne, NPC* t_npcTwo);


	//++++++++++Get Statistics ++++++++++
	float GetAvgSpeed();
	float GetAvgStr();
	float GetAvgInt();
	float GetAvgSize();

	float m_avgStatisticSpeed = 0;
	float m_avgStatisticStr= 0;
	float m_avgStatisticInt = 0;
	float m_avgStatisticSize = 0;

	int m_statisticWanted = 0;

	//++++++++++CONST VARIABLE ++++++++++ 
	int BREEDING_DISTANCE = 400;
	int REPRODUCTION_CHANCE_THRESHOLD = 20; // 20  = 20% CHANCE OF REPRODUCTION
	const int REPRODUCTION_CHANCE = 100;   // Total % chance of reproduction 
	int STARTER_AMOUNT = 10;

	int EVENT_COUNTDOWM = 20;

	int ENDEING_TYPE = 0; // 0 = gen 1 = number of npcs
	int ENDEING_NUMBER = 10;

	bool m_EndReached = false;

	//++++++++++GLOBAL VARIABLE ++++++++++
	int REPRODUCTION_INCREASE = 40; //increase in reproduction chance when a wanted trait is found 

	int REPRODUCTION_TIME = 10; // 1 = 1 years
	int AGE_CAP = 50;  // 50 = 50 years 

	std::chrono::steady_clock::time_point m_StartTimeREPOHighest;
	std::chrono::steady_clock::time_point m_CurrentTimeREPOHighest;
	std::chrono::duration<double> m_elapsedtimeREPOHighest;


    std::chrono::steady_clock::time_point m_StartTimeEvent;
	std::chrono::steady_clock::time_point m_CurrentTimeEvent;
	std::chrono::duration<double> m_elapsedtimeEvent;
	int m_randomEvent = 0;

	int m_totalItarationsRunning = 0;
	int m_totalItarations = 3;

	//++++++++++vars for singe reproduction+++++++

	std::array<float, 4> m_mutationArray = { 15,0,0,0 }; // mutation array for  the chance of mutation 
	std::array<int, 4> m_wantedStatistics = { 1,0,0,0 }; // 1= yes 0 = no

	//++++++++++NPCS VARIABLES ++++++++++
	int m_IDCount = 0;
	std::vector<NPC*> m_npcs;
	std::vector<int> m_npcBreedingGroup;
	int hpHit = 0;

	int m_distanceBetweenNPC = 0;
	int m_runningReproductionChance = REPRODUCTION_CHANCE;

	float m_highestCurrentStatNumber = 0;
	int m_highestCurrentStatID = 0;

	int m_maleHeighest ;
	int m_femaleHeighest;

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

	//++++++++++MENU TEXT++++++++++
	int m_menuButton = 0;

	int m_ALGORYTHIM_CHOICE = 0;
	int m_Mutation_CHOICE = 0;

	float m_mutationRateSpeed = 0.1f;//increase for the amount the button increases by

	std::vector <sf::Text> m_menuButtonTEXT;
	
	//++++++++++Mutation &  statistics ++++++++++
	sf::Text m_staisticTrackedname;

	sf::Text m_speedMutation;
	sf::Text m_strMutation;
	sf::Text m_intMutation;
	sf::Text m_sizeMutation;

	sf::Text m_speedWanted;
	sf::Text m_strWanted;
	sf::Text m_intWanted;
	sf::Text m_sizeWanted;


	sf::Text m_breeedingDistanceText;
	sf::Text m_reproductionChanceText;
	sf::Text m_starterAmountText;

	sf::Text m_algorithmType;
	sf::Text m_mutationType;

	sf::Text m_EventTypeText;
	sf::Text m_EventTypeTimeText;

	

	std::vector<std::string> m_YesNo;
	sf::RectangleShape m_buttonOutline;

	//++++++++++Sprites & Textures ++++++++++
	sf::Sprite m_backgroundSpriteMainMenu;
	sf::Texture m_backgroundTextureMainMenu;

	sf::Sprite m_backgroundSprite;
	sf::Texture m_backgroundTexture;

	sf::Sprite m_foregroundSprite;
	sf::Texture m_foregroundTexture;

	sf::Texture m_heartTexture;




	std::vector< sf::Sprite> m_heartSprite;

	sf::CircleShape m_highStatCircle;

	NPC* m_trackedOneNPC;
	NPC* m_trackedTwoNPC;
	//++++++++++GUI++++++++++
	GUI m_gui;

};

#endif // !SYSTEM_HPP

