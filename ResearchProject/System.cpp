#include "System.h"
#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 


/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
System::System() :
	m_window{ sf::VideoMode{ 2500, 1500, 32 }, "GA" },
	m_exit{false}, //when true System will exit
	m_gui(m_window)//set up GUI
{
	
	




	setupFontAndText(); // load font 

	if (!m_backgroundTexture.loadFromFile("ASSETS\\IMAGES\\Background.png"))
	{
		std::cout << "problem loading background Texture" << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);

	if (!m_foregroundTexture.loadFromFile("ASSETS\\IMAGES\\Foreground.png"))
	{
		std::cout << "problem loading Foreground Texture" << std::endl;
	}
	m_foregroundSprite.setTexture(m_foregroundTexture);

 	m_npcs.reserve(10);
	for (int i = 0; i < 10; i++)
	{
		m_npcs.push_back(new NPC(m_window, m_ArialBlackfont));
	}
	for (int i = 0; i < 5; i++)
	{
		m_npcs[i]->setGender(1);
	}

	for (int i = 0; i < m_npcs.size(); i++) 
	{ 
		m_npcs[i]->setUpGAvar(REPRODUCTION_TIME, AGE_CAP);
		m_npcs[i]->setUpNpcStart(m_IDCount); m_IDCount++; 
	}
}

/// <summary>
/// default destructor 
/// </summary>
System::~System()
{
}

/// <summary>
/// main System loop
/// update 60 times per second,
/// </summary>
void System::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps

	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void System::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exit = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}

/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void System::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exit = true;
	}
	if (sf::Keyboard::Space == t_event.key.code)
	{

		for (int i = 0; i < m_npcs.size()/2; i++)
		{
			m_npcs.erase(m_npcs.begin() + i);
		}
	}
	if (sf::Keyboard::S == t_event.key.code)
	{

		for (int i = 0; i < m_npcs.size(); i++)
		{
			if (m_npcs[i]->getSize() >2)
			{
				m_npcs.erase(m_npcs.begin() + i);
			}			
		}
	}
}

/// <summary>
/// Update the System
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void System::update(sf::Time t_deltaTime)
{
	if (m_exit)
	{m_window.close();}


	m_maleCount = 0;
	m_femaleCount = 0;
	for (int i = 0; i < m_npcs.size(); i++)
	{
		m_npcs[i]->Update();
		if (m_npcs[i]->isAlive() == false) { m_npcs.erase(m_npcs.begin() + i); }

		if (i != 0)
		{
			if (m_npcs[i]->getGender() == 1)
			{
				m_maleCount++;
			}
			else { m_femaleCount++; }
		}
	}
	GAReproduction();

	if (m_highestPopulation < m_npcs.size())
	{
		m_highestPopulation = m_npcs.size();
		m_totalNPCAlltime.setString("Highest Population: " + std::to_string(m_highestPopulation));
	}
	m_totalNPC.setString("Total NPC's: " + std::to_string(m_npcs.size()));

	m_maleCountText.setString("Total males: " + std::to_string(m_maleCount));
	m_femaleCountText.setString("Total Females: " + std::to_string(m_femaleCount));
	


}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void System::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_backgroundSprite);

	for (int i = 0; i < m_npcs.size(); i++) {m_npcs[i]->Draw();}
	
	m_window.draw(m_heartSprite);
	m_window.draw(m_totalNPC);
	m_window.draw(m_totalNPCAlltime);
	m_window.draw(m_maleCountText);
	m_window.draw(m_femaleCountText);

	m_window.draw(m_foregroundSprite);

	m_gui.Draw();

	
	m_window.display();
}

int System::randomNumber(int t_max, int t_min)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(t_min, t_max); 

	return dist(rng);
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void System::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	if (!m_heartTexture.loadFromFile("ASSETS\\IMAGES\\Heart.png"))
	{
		std::cout << "problem loading heart Texture" << std::endl;
	}
	m_heartSprite.setTexture(m_heartTexture);
	m_heartSprite.setPosition(-100, -100);
	m_heartSprite.setScale(3,3);

	m_totalNPC.setFont(m_ArialBlackfont);
	m_totalNPC.setFillColor(sf::Color::Black);
	m_totalNPC.setPosition(sf::Vector2f(2050,0));
	
	m_totalNPCAlltime.setFont(m_ArialBlackfont);
	m_totalNPCAlltime.setFillColor(sf::Color::Black);
	m_totalNPCAlltime.setPosition(sf::Vector2f(2050, 30));

	m_maleCountText.setFont(m_ArialBlackfont);
	m_maleCountText.setFillColor(sf::Color::Black);
	m_maleCountText.setPosition(sf::Vector2f(2050, 60));

	m_femaleCountText.setFont(m_ArialBlackfont);
	m_femaleCountText.setFillColor(sf::Color::Black);
	m_femaleCountText.setPosition(sf::Vector2f(2050, 90));

}

void System::GAReproduce(NPC* t_npcOne, NPC* t_npcTwo)
{
	std::array<float, 4> DNA_ONE = t_npcOne->getDNA();
	std::array<float, 4> DNA_TWO = t_npcTwo->getDNA();
	std::array<float, 4> DNA_THREE;

	t_npcOne->setEndPosition(t_npcTwo->getPos());
	t_npcTwo->setEndPosition(t_npcOne->getPos());
	m_heartSprite.setPosition(sf::Vector2f((t_npcOne->getPos().x + t_npcTwo->getPos().x) / 2, (t_npcOne->getPos().y + t_npcTwo->getPos().y) / 2));


	float Mutations[4] ;
	Mutations[0] = 0;
	Mutations[1] = 0;
	Mutations[2] = 0;
	Mutations[3] = 0;


	

	int mutationChance;
	for (int i = 0; i < 4; i++)
	{
		mutationChance = randomNumber(3,0);

		if (mutationChance == 0)
		{
			Mutations[i] = -mutationArray[i];
		}
		else if(mutationChance == 1)
		{
			Mutations[i] = mutationArray[i];
		}
		else if (mutationChance == 2)
		{
			Mutations[i] = 0;
		}


	}

	DNA_THREE[0] = DNA_ONE[0];
	DNA_THREE[1] = DNA_ONE[1];
	DNA_THREE[2] = DNA_TWO[2];
	DNA_THREE[3] = DNA_TWO[3];

	for (int i = 0; i < 4; i++)
	{
		DNA_THREE[i] += Mutations[i];
		if (DNA_THREE[i] < 0) { DNA_THREE[i] = 0;}
		if (DNA_THREE[i] > 9) { DNA_THREE[i] = 9; }



		DNA_THREE[i] += DNA_THREE[i];
	}


	m_npcs.push_back(new NPC(m_window, m_ArialBlackfont));


	if (t_npcOne->getGenertaion() > t_npcTwo->getGenertaion() || t_npcOne->getGenertaion() == t_npcTwo->getGenertaion())
	{m_npcs[m_npcs.size() - 1]->setGenertaion((t_npcOne->getGenertaion()+1));}
	else {m_npcs[m_npcs.size() - 1]->setGenertaion((t_npcTwo->getGenertaion() + 1));}


	m_npcs[m_npcs.size() - 1]->setDNA(DNA_THREE);
	m_npcs[m_npcs.size() - 1]->setPosition(sf::Vector2f((t_npcOne->getPos().x + t_npcTwo->getPos().x) / 2, (t_npcOne->getPos().y + t_npcTwo->getPos().y) / 2));
	m_npcs[m_npcs.size() - 1]->setUpGAvar(REPRODUCTION_TIME, AGE_CAP);
	m_npcs[m_npcs.size() - 1]->setUpNpc(m_IDCount);
	m_IDCount++;

	t_npcOne->resetReproductionTimer();
	t_npcTwo->resetReproductionTimer();

}


void System::GAReproduction()
{
	int distanceBetweenNPC = 0;

	for (int i = 0; i < m_npcs.size(); i++)
	{
		if (m_npcs[i]->getAge() >= (AGE_CAP / 4) && m_npcs[i]->getAge() <= ((AGE_CAP / 4) * 3))
		{

			if (m_npcs[i]->getReproductionCooldown() <= 0)
			{
				for (int j = 0; j < m_npcs.size(); j++)
				{
					if (m_npcs[i] != m_npcs[j])
					{
						if (m_npcs[j]->getAge() >= (AGE_CAP / 4) && m_npcs[j]->getAge() <= ((AGE_CAP / 4) * 3))
						{
							if (m_npcs[i]->getGender() != m_npcs[j]->getGender())
							{
								if (m_npcs[j]->getReproductionCooldown() <= 0)
								{

									distanceBetweenNPC =
										sqrt((pow((m_npcs[j]->getPos().x - m_npcs[i]->getPos().x), 2)) +
										(pow((m_npcs[j]->getPos().y - m_npcs[i]->getPos().y), 2)));

									if (distanceBetweenNPC <= 400)
									{
										if (randomNumber(REPRODUCTION_CHANCE,0) == 0)
										{

											GAReproduce(m_npcs[i], m_npcs[j]);
										}
										else
										{
											m_npcs[i]->resetReproductionTimer();
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}


}
