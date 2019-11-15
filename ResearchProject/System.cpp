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
	m_exit{false} //when true System will exit
{
	srand(time(0));
	setupFontAndText(); // load font 

	m_npcs.reserve(5);
	m_npcs.push_back(new NPC(m_window));
	m_npcs.push_back(new NPC(m_window));
	m_npcs.push_back(new NPC(m_window));
	m_npcs.push_back(new NPC(m_window));
	m_npcs.push_back(new NPC(m_window));
	m_npcs.push_back(new NPC(m_window));

	for(int i = 0; i < m_npcs.size() ;i++) {m_npcs[i]->setUpNpc();}

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
	{
		m_window.close();
	}


	for (int i = 0; i < m_npcs.size(); i++) { m_npcs[i]->Update(); }
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void System::render()
{
	m_window.clear(sf::Color::White);

	for (int i = 0; i < m_npcs.size(); i++) {m_npcs[i]->Draw();}

	m_npcs[0]->getPos();
	
	m_window.draw(m_temptext);
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
	m_temptext.setFont(m_ArialBlackfont);
	m_temptext.setString("test");
	m_temptext.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_temptext.setPosition(40.0f, 40.0f);
	m_temptext.setCharacterSize(80U);
	m_temptext.setOutlineColor(sf::Color::Red);
	m_temptext.setFillColor(sf::Color::Black);
	m_temptext.setOutlineThickness(3.0f);
}