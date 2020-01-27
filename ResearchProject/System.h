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


	//++++++++++GLOBAL VARIABLE ++++++++++
	int REPRODUCTION_CHANCE = 3;   // 4 = 1/4 
	int REPRODUCTION_TIME = 400; //450
	int AGE_CAP = 5000;

	std::array<float, 4> mutationArray = { 1,0,0,0 };



	//++++++++++NPCS VARIABLES ++++++++++
	int m_IDCount = 0;
	std::vector<NPC*> m_npcs;

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

