#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <SFML/Graphics.hpp>
#include "NPC.h"

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

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	

	void setupFontAndText();

	//GA
	void GAReproduction();
	void GAReproduce(NPC* t_npcOne, NPC* t_npcTwo);


	//vars for global
	int REPRODUCTION_CHANCE = 3;   // 4 = 1/4 
	int REPRODUCTION_TIME = 450; //450
	int AGE_CAP = 5000;

	int mutationArray[4] = { 1,0,0,0 };


	int m_IDCount = 0;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message


	sf::Sprite m_heartSprite;
	sf::Texture m_heartTexture;

	sf::Text m_totalNPC;


	std::vector<NPC *> m_npcs;
	

	bool m_exit; // control exiting 

};

#endif // !SYSTEM_HPP

