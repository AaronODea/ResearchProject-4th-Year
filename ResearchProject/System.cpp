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
	m_window{ sf::VideoMode{ 2000, 1000, 32 }, "GA" },
	m_exit{false} //when true System will exit
{
	setupFontAndText(); // load font 

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
}

/// <summary>
/// Update the System
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void System::update(sf::Time t_deltaTime)
{
	if (m_exit)
	{m_window.close();}


	for (int i = 0; i < m_npcs.size(); i++)  
	{ 
		m_npcs[i]->Update(); 
		if (m_npcs[i]->isAlive() == false) {m_npcs.erase(m_npcs.begin() + i);}
	}


	GAReproduction();


	std::cout << m_npcs.size() << std::endl;
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void System::render()
{
	m_window.clear(sf::Color::White);

	for (int i = 0; i < m_npcs.size(); i++) {m_npcs[i]->Draw();}

	m_window.display();
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
}

void System::GAReproduce(NPC* t_npcOne, NPC* t_npcTwo)
{
	std::string DNA_ONE = t_npcOne->getDNA();
	std::string DNA_TWO = t_npcTwo->getDNA();
	std::string DNA_THREE = "";



	int DNA_arry_ONE[4];
	int DNA_arry_TWO[4];
	int DNA_arry_THREE[4];


	for (int i = 0; i < DNA_ONE.size(); i++)
	{
		DNA_arry_ONE[i] = (int)(DNA_ONE.at(i)-48);
		DNA_arry_TWO[i] = (int)(DNA_TWO.at(i) - 48);
	}

	float  mutation_speed =(mutationArray[0]/100)*(rand()% 2);
	//float  mutation_str = mutationArray[1]/100 * (rand() % 2) - 1;
	//float mutation_int = mutationArray[2]/100 * (rand() % 2) - 1;
	//float  mutation_size = mutationArray[3]/100 * (rand() % 2) - 1;
	float  mutation_str = 0;
	float mutation_int = 0;
	float  mutation_size = 0;




	DNA_arry_THREE[0] = DNA_arry_ONE[0] + mutation_speed;
	DNA_arry_THREE[1] = DNA_arry_ONE[1] + mutation_str;
	DNA_arry_THREE[2] = DNA_arry_TWO[2] + mutation_int;
	DNA_arry_THREE[3] = DNA_arry_TWO[3] + mutation_size;




	for (int i = 0; i <=  3; i++)
	{
		if (DNA_arry_THREE[i] < 0) {DNA_arry_THREE[i] = 0;}
		DNA_THREE += std::to_string(DNA_arry_THREE[i]);
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
										if (rand() % REPRODUCTION_CHANCE == 0)
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
