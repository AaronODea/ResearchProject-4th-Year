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
	m_window{ sf::VideoMode{ 1920, 1080, 32 }, "GA" },
	m_exit{false}, //when true System will exit
	m_gui(m_window)//set up GUI
{	
	m_currentState = m_startingScreen;

	WIDTH = m_window.getSize().x;
	HEIGHT = m_window.getSize().y;
	m_penSize.x = (WIDTH*.0004);
	m_penSize.y = (HEIGHT * .0007);
	setupFontAndText(); // load font 
	m_gui.SetUpLineGraph(m_ArialBlackfont);


	if (!m_backgroundTexture.loadFromFile("ASSETS\\IMAGES\\Background.png")){std::cout << "problem loading background Texture" << std::endl;}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setScale(m_penSize.x, m_penSize.y);

	if (!m_foregroundTexture.loadFromFile("ASSETS\\IMAGES\\Foreground.png")) {std::cout << "problem loading Foreground Texture" << std::endl;}
	m_foregroundSprite.setTexture(m_foregroundTexture);
	m_foregroundSprite.setScale(m_penSize.x, m_penSize.y);

	m_highStatCircle.setFillColor(sf::Color(255, 255, 153, 120));
	m_highStatCircle.setOutlineColor(sf::Color(0,0,0,200));
	m_highStatCircle.setOutlineThickness(WIDTH/1000);



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
		while (timeSinceLastUpdate > timePerFrame){
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
	while (m_window.pollEvent(newEvent)) {
		if (sf::Event::Closed == newEvent.type) { m_exit = true; }// window message
		if (sf::Event::KeyPressed == newEvent.type) { processKeys(newEvent); }//user pressed a key
	}
}

/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void System::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code){m_exit = true;}

	switch (m_currentState)
	{
	default:
		break;
	case m_startingScreen:
		if (sf::Keyboard::Space == t_event.key.code) 
		{m_currentState = m_mainScreen;
			GAStartUp();
			setUpGuiStates();
			switch (m_ALGORYTHIM_CHOICE)
			{
			default:
			case 0:
				break;
			case 1:
				break;
			}
		}

		if (sf::Keyboard::Up == t_event.key.code) {m_menuButton--;
		if (m_menuButton < 0) { m_menuButton = m_menuButtonTEXT.size()-1; }}
		if (sf::Keyboard::Down == t_event.key.code) {m_menuButton++;
		if (m_menuButton >= m_menuButtonTEXT.size()) { m_menuButton = 0; }}

	

	
		switch (m_menuButton)
		{
		default:
		case 0://algo choice 
			if (sf::Keyboard::Left == t_event.key.code) { m_ALGORYTHIM_CHOICE--; }
			if (sf::Keyboard::Right == t_event.key.code) { m_ALGORYTHIM_CHOICE++; }
			if (m_ALGORYTHIM_CHOICE > 1) { m_ALGORYTHIM_CHOICE = 0; };
			if (m_ALGORYTHIM_CHOICE < 0) { m_ALGORYTHIM_CHOICE = 1; };
			break;
		case 1://Mutation choice 
			if (sf::Keyboard::Left == t_event.key.code) { m_Mutation_CHOICE--; }
			if (sf::Keyboard::Right == t_event.key.code) { m_Mutation_CHOICE++; }
			if (m_Mutation_CHOICE > 1) { m_Mutation_CHOICE = 0; };
			if (m_Mutation_CHOICE < 0) { m_Mutation_CHOICE = 1; };
			break;

		case 2://mutation
			if (sf::Keyboard::Left == t_event.key.code) { m_mutationArray[0] -= m_mutationRateSpeed; }
			if (sf::Keyboard::Right == t_event.key.code) { m_mutationArray[0] += m_mutationRateSpeed; }
			if (m_mutationArray[0] > 100) { m_mutationArray[0] = 0; };
			if (m_mutationArray[0] < 0) { m_mutationArray[0] = 100; };
			break;
		case 3://mutation
			if (sf::Keyboard::Left == t_event.key.code) { m_mutationArray[1] -= m_mutationRateSpeed;}
			if (sf::Keyboard::Right == t_event.key.code) { m_mutationArray[1] += m_mutationRateSpeed;}
			if (m_mutationArray[1] > 100) { m_mutationArray[1] = 0; };
			if (m_mutationArray[1] < 0) { m_mutationArray[1] = 100; };
			break;
		case 4://mutation
			if (sf::Keyboard::Left == t_event.key.code) { m_mutationArray[2] -= m_mutationRateSpeed;}
			if (sf::Keyboard::Right == t_event.key.code) { m_mutationArray[2] += m_mutationRateSpeed;}
			if (m_mutationArray[2] > 100) { m_mutationArray[2] = 0; };
			if (m_mutationArray[2] < 0) { m_mutationArray[2] = 100; };
			break;
		case 5://mutation
			if (sf::Keyboard::Left == t_event.key.code) { m_mutationArray[3] -= m_mutationRateSpeed;}
			if (sf::Keyboard::Right == t_event.key.code) { m_mutationArray[3] += m_mutationRateSpeed;}
			if (m_mutationArray[3] > 100) { m_mutationArray[3] = 0; };
			if (m_mutationArray[3] < 0) { m_mutationArray[3] = 100; };
			break;
		case 6://Wanted stat
			if (sf::Keyboard::Left == t_event.key.code || sf::Keyboard::Right == t_event.key.code) {
				if (m_YesNo[0] == "YES") { m_YesNo[0] = "NO"; m_wantedStatistics[0] = 0; }
				else if (m_YesNo[0] == "NO") { m_YesNo[0] = "YES"; m_wantedStatistics[0] = 1;}}
			break;
		case 7://Wanted stat
			if (sf::Keyboard::Left == t_event.key.code || sf::Keyboard::Right == t_event.key.code) {
				if (m_YesNo[1] == "YES") { m_YesNo[1] = "NO"; m_wantedStatistics[1] = 0;}
				else if (m_YesNo[1] == "NO") { m_YesNo[1] = "YES"; m_wantedStatistics[1] = 1;}}
			break;
		case 8://Wanted stat
			if (sf::Keyboard::Left == t_event.key.code || sf::Keyboard::Right == t_event.key.code) {
				if (m_YesNo[2] == "YES") { m_YesNo[2] = "NO"; m_wantedStatistics[2] = 0;}
				else if (m_YesNo[2] == "NO") { m_YesNo[2] = "YES"; m_wantedStatistics[2] = 0;}}
			break;
		case 9://Wanted stat		  
			if (sf::Keyboard::Left == t_event.key.code || sf::Keyboard::Right == t_event.key.code){
				if (m_YesNo[3] == "YES") { m_YesNo[3] = "NO"; m_wantedStatistics[3] = 0;}
				else if (m_YesNo[3] == "NO") { m_YesNo[3] = "YES"; m_wantedStatistics[3] = 0;}}
		break;
		case 10:
			if (sf::Keyboard::Left == t_event.key.code) { BREEDING_DISTANCE -= 50; }
			if (sf::Keyboard::Right == t_event.key.code) { BREEDING_DISTANCE += 50; }
			if (BREEDING_DISTANCE > 1000) { BREEDING_DISTANCE = 0; };
			if (BREEDING_DISTANCE < 0) { BREEDING_DISTANCE = 1000; };
			break;
		case 11:
			if (sf::Keyboard::Left == t_event.key.code) { REPRODUCTION_CHANCE_THRESHOLD -= 1; }
			if (sf::Keyboard::Right == t_event.key.code) { REPRODUCTION_CHANCE_THRESHOLD += 1; }
			if (REPRODUCTION_CHANCE_THRESHOLD > 100) { REPRODUCTION_CHANCE_THRESHOLD = 0; };
			if (REPRODUCTION_CHANCE_THRESHOLD < 0) { REPRODUCTION_CHANCE_THRESHOLD = 100; };
			break; 
		case 12:
			if (sf::Keyboard::Left == t_event.key.code) { STARTER_AMOUNT -= 1; }
			if (sf::Keyboard::Right == t_event.key.code) { STARTER_AMOUNT += 1; }
			if (STARTER_AMOUNT > 100) { STARTER_AMOUNT = 0; };
			if (STARTER_AMOUNT < 0) { STARTER_AMOUNT = 100; };
			break;
		case 13:
			if (sf::Keyboard::Left == t_event.key.code) { STARTER_AMOUNT -= 1; }
			if (sf::Keyboard::Right == t_event.key.code) { STARTER_AMOUNT += 1; }
			if (STARTER_AMOUNT > 100) { STARTER_AMOUNT = 0; };
			if (STARTER_AMOUNT < 0) { STARTER_AMOUNT = 100; };
			break;
		}



		break;
	case m_mainScreen:
		if (sf::Keyboard::Space == t_event.key.code) {for (int i = 0; i < m_npcs.size()/2; i++) {m_npcs.erase(m_npcs.begin() + i);}}

		if (sf::Keyboard::Left == t_event.key.code) {
			m_statisticWanted--;
			if (m_statisticWanted < 0) { m_statisticWanted = 3; };}
		if (sf::Keyboard::Right == t_event.key.code) { m_statisticWanted++; 
			if (m_statisticWanted > 3) { m_statisticWanted = 0; };}

		
	
		 
		if (sf::Keyboard::S == t_event.key.code){
			for (int i = 0; i < m_npcs.size(); i++) {if (m_npcs[i]->getSize() >2) {m_npcs.erase(m_npcs.begin() + i);}}}

		if (sf::Keyboard::Q == t_event.key.code) {

			GAReproductionHighest();
		}//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------remove


		break;
	}

}

/// <summary>
/// Update the System
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void System::update(sf::Time t_deltaTime)
{
	if (m_exit){m_window.close();}

	switch (m_currentState)
	{
	default:
		break;
	case m_startingScreen:

		m_buttonOutline.setSize((sf::Vector2f(m_menuButtonTEXT[m_menuButton].getString().getSize() * (WIDTH / 160), HEIGHT / 54)));
		m_buttonOutline.setPosition(m_menuButtonTEXT[m_menuButton].getPosition());

			switch (m_ALGORYTHIM_CHOICE)
			{
			default:
			case 0:
				m_menuButtonTEXT[0].setString("Current algorithm is Wanted Statistic  ");
				break;
			case 1:
				m_menuButtonTEXT[0].setString("Current algorithm is Highest Statistic ");
				break;
			}

			switch (m_Mutation_CHOICE)
			{
			default:
			case 0:
				m_menuButtonTEXT[1].setString("Current Mutation type is average split ");
				break;
			case 1:
				m_menuButtonTEXT[1].setString("Current Mutation type is 1/2 split");
				break;
			}

			m_menuButtonTEXT[2].setString("Current Speed mutation : " + setMutation(m_mutationArray[0]).str() + "%");
			m_menuButtonTEXT[3].setString("Current Strength mutation :" + setMutation(m_mutationArray[1]).str() + " % ");
			m_menuButtonTEXT[4].setString("Current Intelligence mutation :"+ setMutation(m_mutationArray[2]).str() + " % ");
			m_menuButtonTEXT[5].setString("Current Size mutation : " + setMutation(m_mutationArray[3]).str() + "%");
			

			m_menuButtonTEXT[6].setString("SPEED Wanted : "+ m_YesNo[0]);//wanted stats
			m_menuButtonTEXT[7].setString("Strength Wanted : "+ m_YesNo[1]);
			m_menuButtonTEXT[8].setString("Intelligence Wanted : "+ m_YesNo[2]);
			m_menuButtonTEXT[9].setString("Size Wanted : "+ m_YesNo[3]);

			m_menuButtonTEXT[10].setString("Breeding Distance : " + std::to_string(BREEDING_DISTANCE));
			m_menuButtonTEXT[11].setString("Reproduction Chance : " + std::to_string(REPRODUCTION_CHANCE_THRESHOLD) + "%");
			m_menuButtonTEXT[12].setString("Starter amount : " + std::to_string(STARTER_AMOUNT));
		break;

	case m_mainScreen:

		if (m_heartSprite.size() >= 5) {m_heartSprite.pop_back();}

		m_maleCount = 1;
		m_femaleCount = 0;

		for (int i = 0; i < m_npcs.size(); i++){
			m_npcs[i]->Update();
			if (m_npcs[i]->isAlive() == false) { m_npcs.erase(m_npcs.begin() + i); }}

		for (int i = 0; i < m_npcs.size(); i++) {
			if (m_npcs[i]->getGender() == 1) { m_maleCount++; }
			else { m_femaleCount++; }}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			//where to add the second gn
			switch (m_ALGORYTHIM_CHOICE)
			{
			default:
			case 0:
				GAReproductionWanted();

				break;
			case 1:
				GAReproductionHighest();
				break;
			}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		if (m_highestPopulation < m_npcs.size()){
			m_highestPopulation = m_npcs.size();
			m_totalNPCAlltime.setString("Highest Population: " + std::to_string(m_highestPopulation));}

		m_totalNPC.setString("Total NPC's: " + std::to_string(m_npcs.size()));
		m_maleCountText.setString("Total males: " + std::to_string(m_maleCount-1));
		m_femaleCountText.setString("Total Females: " + std::to_string(m_femaleCount));
	
		switch (m_statisticWanted)
			{
			default:
				GetAvgSpeed();
				m_staisticTrackedname.setString("Statistic tracked: Speed");
				break;
			case 0:
				GetAvgSpeed();
				m_staisticTrackedname.setString("Statistic tracked: Speed");
				break;
			case 1:	
				GetAvgStr();
				m_staisticTrackedname.setString("Statistic tracked: Strength");
				break;
			case 2:
				GetAvgInt();
				m_staisticTrackedname.setString("Statistic tracked: Intelligence");
				break;
			case 3:
				GetAvgSize();
				m_staisticTrackedname.setString("Statistic tracked: Size");
				break;
			}//tracked statistic 

		m_highestCurrentStatNumber = 0;  

		for (int i = 0; i < m_npcs.size(); i++)
		{

			switch (m_statisticWanted)
			{
			default:
			case 0:
				if (m_highestCurrentStatNumber <= m_npcs[i]->GetSpeedStatistic()) {
					m_highestCurrentStatNumber = m_npcs[i]->GetSpeedStatistic();
					m_highestCurrentStatID = i;
				}
				break;
			case 1:
				if (m_highestCurrentStatNumber <= m_npcs[i]->GetStrStatistic()) {
					m_highestCurrentStatNumber = m_npcs[i]->GetStrStatistic();
					m_highestCurrentStatID = i;
				}
				break;
			case 2:
				if (m_highestCurrentStatNumber <= m_npcs[i]->GetIntStatistic()) {
					m_highestCurrentStatNumber = m_npcs[i]->GetIntStatistic();
					m_highestCurrentStatID = i;
				}
				break;
			case 3:
				if (m_highestCurrentStatNumber <= m_npcs[i]->GetSizeStatistic()) {
					m_highestCurrentStatNumber = m_npcs[i]->GetSizeStatistic();
					m_highestCurrentStatID = i;
				}
				break;
			}///highest of that stat
		}

		if (m_npcs.size() != NULL)
		{
			m_highStatCircle.setPosition(sf::Vector2f(m_npcs[m_highestCurrentStatID]->getPos().x - (m_npcs[m_highestCurrentStatID]->getSize() * 0.5f),
				m_npcs[m_highestCurrentStatID]->getPos().y - (m_npcs[m_highestCurrentStatID]->getSize())));
			m_highStatCircle.setRadius((m_npcs[m_highestCurrentStatID]->getSize() * 1.2));
		}
		m_gui.update(m_avgStatistic, m_npcs.size(), m_statisticWanted);
	break;
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void System::render()
{
	m_window.clear(sf::Color(160,150,160));
	
	switch (m_currentState)
	{
	default:
		break;
	case m_startingScreen:

		for (int i = 0; i < m_menuButtonTEXT.size(); i++) {m_window.draw(m_menuButtonTEXT[i]);}
		m_window.draw(m_buttonOutline);
		break;
	case m_mainScreen:

		m_window.draw(m_backgroundSprite);
		for (int i = 0; i < m_npcs.size(); i++) {m_npcs[i]->Draw();}

		if (m_npcs.size() <= 10)
			{for (int i = 0; i < m_npcs.size(); i++) {m_npcs[i]->DrawStatistics();}}
			else{for (int i = m_npcs.size(); i > (m_npcs.size()-10); i--) { m_npcs[i-1]->DrawStatistics(); }}


		if (m_trackedOneNPC->getReproductionCooldown() >= 0 && m_trackedTwoNPC->getReproductionCooldown() >= 0)
		   {m_window.draw(m_heartSprite[0]);
			m_window.draw(m_heartSprite[1]);}

		m_window.draw(m_totalNPC);
		m_window.draw(m_totalNPCAlltime);
		m_window.draw(m_maleCountText);
		m_window.draw(m_femaleCountText);
		m_window.draw(m_staisticTrackedname);
	
		m_window.draw(m_speedMutation);
		m_window.draw(m_strMutation);
		m_window.draw(m_intMutation);
		m_window.draw(m_sizeMutation); 

		m_window.draw(m_speedWanted);
		m_window.draw(m_strWanted);
		m_window.draw(m_intWanted);
		m_window.draw(m_sizeWanted);

		m_window.draw(m_breeedingDistanceText);
		m_window.draw(m_reproductionChanceText);
		m_window.draw(m_starterAmountText);
		m_window.draw(m_algorithmType);
		m_window.draw(m_mutationType);


		if(m_trackedOneNPC->getReproductionCooldown() >= 0 && m_trackedTwoNPC->getReproductionCooldown() >= 0)
		{m_heartSprite[0].setPosition(sf::Vector2f((m_trackedOneNPC->getPos().x) + (m_trackedOneNPC->getSizeTexture().x/2) , (m_trackedOneNPC->getPos().y) - (m_trackedOneNPC->getSizeTexture().y * 2)));
		 m_heartSprite[1].setPosition(sf::Vector2f((m_trackedTwoNPC->getPos().x)+ (m_trackedTwoNPC->getSizeTexture().x / 2), (m_trackedTwoNPC->getPos().y) - (m_trackedOneNPC->getSizeTexture().y * 2)));}
		
		m_window.draw(m_foregroundSprite);
	
		m_window.draw(m_highStatCircle);
		m_gui.Draw();

		break;
	}

	m_window.display();
}

/// <summary>
/// random number generator that outputs a random number from input numbers
/// </summary>
int System::randomNumber(int t_max, int t_min)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(t_min, t_max); 

	return dist(rng);
}
std::stringstream System::setMutation(float t_mutation)
{
	std::stringstream MutationStream;
	
	MutationStream << std::fixed << std::setprecision(1) << t_mutation;
	return MutationStream;
}
/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void System::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf")) {std::cout << "problem loading arial black font" << std::endl;}
	if (!m_heartTexture.loadFromFile("ASSETS\\IMAGES\\Heart.png")) {std::cout << "problem loading heart Texture" << std::endl;}

	m_heartSprite.push_back(sf::Sprite());
	m_heartSprite[0].setTexture(m_heartTexture);
	m_heartSprite[0].setScale(WIDTH / 833.33f, HEIGHT / 500);

	m_heartSprite.push_back(sf::Sprite());
	m_heartSprite[1].setTexture(m_heartTexture);
	m_heartSprite[1].setScale(WIDTH / 833.33f, HEIGHT / 500);



	//++++++++++MENU STRINGS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	for (int i = 0; i < 13; i++)
	{
	m_menuButtonTEXT.push_back(sf::Text());
	m_menuButtonTEXT[i].setFont(m_ArialBlackfont);
	m_menuButtonTEXT[i].setFillColor(sf::Color::Black);
	m_menuButtonTEXT[i].setPosition(sf::Vector2f(1, 1000));
	m_menuButtonTEXT[i].setCharacterSize(WIDTH / 100);
	}

	m_menuButtonTEXT[0].setString("Current algorithm is Non-Fixed ");//gA
	m_menuButtonTEXT[0].setPosition(sf::Vector2f(WIDTH / 8, (HEIGHT / 37.5)));


	m_menuButtonTEXT[1].setString("Current Mutation type is average split ");
	m_menuButtonTEXT[1].setPosition(sf::Vector2f(WIDTH / 8, (HEIGHT / 20.5)));

	m_menuButtonTEXT[2].setString("Current Speed mutation : ");//Mutations
	m_menuButtonTEXT[3].setString("Current Strength mutation : ");
	m_menuButtonTEXT[4].setString("Current Intelligence mutation : ");
	m_menuButtonTEXT[5].setString("Current Size mutation : ");
	m_menuButtonTEXT[2].setPosition(sf::Vector2f(WIDTH/8, (HEIGHT / 9.0f)));
	m_menuButtonTEXT[3].setPosition(sf::Vector2f(WIDTH / 8 , (HEIGHT / 7.5f)));
	m_menuButtonTEXT[4].setPosition(sf::Vector2f(WIDTH / 8 , (HEIGHT / 6.5f)));
	m_menuButtonTEXT[5].setPosition(sf::Vector2f(WIDTH / 8, (HEIGHT / 5.8f)));


	m_menuButtonTEXT[6].setString("SPEED Wanted : NO");//wanted stats
	m_menuButtonTEXT[7].setString("Strength Wanted : NO");
	m_menuButtonTEXT[8].setString("Intelligence Wanted : NO");
	m_menuButtonTEXT[9].setString("Size Wanted : NO");
	m_menuButtonTEXT[6].setPosition(sf::Vector2f(WIDTH / 8, (HEIGHT / 4.4f)));
	m_menuButtonTEXT[7].setPosition(sf::Vector2f(WIDTH / 8, (HEIGHT / 4.1f)));
	m_menuButtonTEXT[8].setPosition(sf::Vector2f(WIDTH / 8, (HEIGHT / 3.8f)));
	m_menuButtonTEXT[9].setPosition(sf::Vector2f(WIDTH / 8, (HEIGHT / 3.55f)));


	m_menuButtonTEXT[10].setString("Breeding Distance : 400");//wanted stats
	m_menuButtonTEXT[11].setString("Reproduction Chance : 20%");
	m_menuButtonTEXT[12].setString("Starter amount : 10");
	m_menuButtonTEXT[10].setPosition(sf::Vector2f(WIDTH / 8, (HEIGHT / 3.0f)));
	m_menuButtonTEXT[11].setPosition(sf::Vector2f(WIDTH / 8, (HEIGHT / 2.85f)));
	m_menuButtonTEXT[12].setPosition(sf::Vector2f(WIDTH / 8, (HEIGHT / 2.7f)));
	
	m_buttonOutline.setFillColor(sf::Color(102, 204, 0, 60));
	m_buttonOutline.setOutlineColor(sf::Color(0,0,0,160));
	m_buttonOutline.setOutlineThickness(WIDTH/500);

	m_buttonOutline.setSize((sf::Vector2f(m_menuButtonTEXT[m_menuButton].getString().getSize() * (WIDTH / 150), HEIGHT / 20)));
	m_buttonOutline.setPosition(m_menuButtonTEXT[m_menuButton].getPosition());
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


	m_YesNo.push_back("NO");
	m_YesNo.push_back("NO");
	m_YesNo.push_back("NO");
	m_YesNo.push_back("NO");

}

void System::setUpGuiStates()
{
	//++++++++++Statistics STRINGS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	m_staisticTrackedname.setFont(m_ArialBlackfont);
	m_staisticTrackedname.setFillColor(sf::Color::Black);
	m_staisticTrackedname.setPosition(sf::Vector2f(WIDTH * 0.02f, HEIGHT * 0.7f));
	m_staisticTrackedname.setCharacterSize(WIDTH / 100);

	m_totalNPC.setFont(m_ArialBlackfont);
	m_totalNPC.setFillColor(sf::Color::Black);
	m_totalNPC.setPosition(sf::Vector2f(WIDTH / 1.219f, HEIGHT / 35.0f));
	m_totalNPC.setCharacterSize(WIDTH / 100);

	m_totalNPCAlltime.setFont(m_ArialBlackfont);
	m_totalNPCAlltime.setFillColor(sf::Color::Black);
	m_totalNPCAlltime.setPosition(sf::Vector2f(WIDTH / 1.219f, HEIGHT / 22.0f));
	m_totalNPCAlltime.setCharacterSize(WIDTH / 100);

	m_maleCountText.setFont(m_ArialBlackfont);
	m_maleCountText.setFillColor(sf::Color::Cyan);
	m_maleCountText.setPosition(sf::Vector2f(WIDTH / 1.219f, HEIGHT / 12.0f));
	m_maleCountText.setCharacterSize(WIDTH / 100);

	m_femaleCountText.setFont(m_ArialBlackfont);
	m_femaleCountText.setFillColor(sf::Color::Yellow);
	m_femaleCountText.setPosition(sf::Vector2f(WIDTH / 1.219f, HEIGHT / 10.0f));
	m_femaleCountText.setCharacterSize(WIDTH / 100);

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//++++++++++MUTATION STRINGS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	std::stringstream m_speedMutationStream;
	std::stringstream m_strengthMutationStream;
	std::stringstream m_intelligenceMutationStream;
	std::stringstream m_sizeMutationStream;

	m_speedMutationStream << std::fixed << std::setprecision(1) << m_mutationArray[0];
	m_strengthMutationStream << std::fixed << std::setprecision(1) << m_mutationArray[1];
	m_intelligenceMutationStream << std::fixed << std::setprecision(1) << m_mutationArray[2];
	m_sizeMutationStream << std::fixed << std::setprecision(1) << m_mutationArray[3];

	m_speedMutation.setFont(m_ArialBlackfont);
	m_speedMutation.setFillColor(sf::Color(255, 102, 102));
	m_speedMutation.setPosition(sf::Vector2f(WIDTH / 1.219f, HEIGHT / 6.6f));
	m_speedMutation.setCharacterSize(WIDTH / 100);
	m_speedMutation.setString("Speed mutation: " + m_speedMutationStream.str() + "%");

	m_strMutation.setFont(m_ArialBlackfont);
	m_strMutation.setFillColor(sf::Color(255, 178, 102));
	m_strMutation.setPosition(sf::Vector2f(WIDTH / 1.219f, HEIGHT / 5.88f));
	m_strMutation.setCharacterSize(WIDTH / 100);
	m_strMutation.setString("Strength mutation: " + m_strengthMutationStream.str() + "%");

	m_intMutation.setFont(m_ArialBlackfont);
	m_intMutation.setFillColor(sf::Color(255, 255, 102));
	m_intMutation.setPosition(sf::Vector2f(WIDTH / 1.219f, HEIGHT / 5.4f));
	m_intMutation.setCharacterSize(WIDTH / 100);
	m_intMutation.setString("Intelligence mutation: " + m_intelligenceMutationStream.str() + "%");

	m_sizeMutation.setFont(m_ArialBlackfont);
	m_sizeMutation.setFillColor(sf::Color(178, 255, 102));
	m_sizeMutation.setPosition(sf::Vector2f(WIDTH / 1.219f, HEIGHT / 5.0f));
	m_sizeMutation.setCharacterSize(WIDTH / 100);
	m_sizeMutation.setString("Size mutation: " + m_sizeMutationStream.str() + "%");

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//++++++++++STAT WANTED STRINGS+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	m_speedWanted.setFont(m_ArialBlackfont);
	m_speedWanted.setFillColor(sf::Color::Green);
	m_speedWanted.setPosition(sf::Vector2f(WIDTH / 1.219f, HEIGHT / 4.0f));
	m_speedWanted.setCharacterSize(WIDTH / 100);
	m_speedWanted.setString("Speed Wanted: " + m_YesNo[0]);
	if (m_YesNo[0] == "NO") { m_speedWanted.setFillColor(sf::Color::Red); }

	m_strWanted.setFont(m_ArialBlackfont);
	m_strWanted.setFillColor(sf::Color::Green);
	m_strWanted.setPosition(sf::Vector2f(WIDTH / 1.219f, HEIGHT / 3.71f));
	m_strWanted.setCharacterSize(WIDTH / 100);
	m_strWanted.setString("Strength Wanted: " + m_YesNo[1]);
	if (m_YesNo[1] == "NO") { m_strWanted.setFillColor(sf::Color::Red); }

	m_intWanted.setFont(m_ArialBlackfont);
	m_intWanted.setFillColor(sf::Color::Green);
	m_intWanted.setPosition(sf::Vector2f(WIDTH / 1.219f, HEIGHT / 3.5f));
	m_intWanted.setCharacterSize(WIDTH / 100);
	m_intWanted.setString("Intelligence Wanted: " + m_YesNo[2]);
	if (m_YesNo[2] == "NO") { m_intWanted.setFillColor(sf::Color::Red); }


	m_sizeWanted.setFont(m_ArialBlackfont);
	m_sizeWanted.setFillColor(sf::Color::Green);
	m_sizeWanted.setPosition(sf::Vector2f(WIDTH / 1.219f, HEIGHT / 3.3f));
	m_sizeWanted.setCharacterSize(WIDTH / 100);
	m_sizeWanted.setString("Size Wanted: " + m_YesNo[3]);
	if (m_YesNo[3] == "NO") { m_sizeWanted.setFillColor(sf::Color::Red); }

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//++++++++++Global STASTS STRINGS+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	m_breeedingDistanceText.setFont(m_ArialBlackfont);
	m_breeedingDistanceText.setFillColor(sf::Color::Black);
	m_breeedingDistanceText.setPosition(sf::Vector2f(WIDTH / 1.219f, HEIGHT / 2.81f));
	m_breeedingDistanceText.setCharacterSize(WIDTH / 100);
	m_breeedingDistanceText.setString("Breeding Distance : " + std::to_string(BREEDING_DISTANCE));

	m_reproductionChanceText.setFont(m_ArialBlackfont);
	m_reproductionChanceText.setFillColor(sf::Color::Black);
	m_reproductionChanceText.setPosition(sf::Vector2f(WIDTH / 1.219f, HEIGHT / 2.7f));
	m_reproductionChanceText.setCharacterSize(WIDTH / 100);
	m_reproductionChanceText.setString("Reproduction Chance : " + std::to_string(REPRODUCTION_CHANCE_THRESHOLD) + "%");

	m_starterAmountText.setFont(m_ArialBlackfont);
	m_starterAmountText.setFillColor(sf::Color::Black);
	m_starterAmountText.setPosition(sf::Vector2f(WIDTH / 1.219f, HEIGHT / 2.6f));
	m_starterAmountText.setCharacterSize(WIDTH / 100);
	m_starterAmountText.setString("Starter amount : " + std::to_string(STARTER_AMOUNT));




	m_algorithmType.setFont(m_ArialBlackfont);
	m_algorithmType.setFillColor(sf::Color::Black);
	m_algorithmType.setPosition(sf::Vector2f(WIDTH / 1.219f, HEIGHT / 2.4f));
	m_algorithmType.setCharacterSize(WIDTH / 100);
	
	switch (m_ALGORYTHIM_CHOICE){
	default:
	case 0:
		m_algorithmType.setString("Algorithm type : Wanted");
		break;
	case 1:
		m_algorithmType.setString("Algorithm type : Highest");
		break;}

	m_mutationType.setFont(m_ArialBlackfont);
	m_mutationType.setFillColor(sf::Color::Black);
	m_mutationType.setPosition(sf::Vector2f(WIDTH / 1.219f, HEIGHT / 2.3f));
	m_mutationType.setCharacterSize(WIDTH / 100);

	switch (m_Mutation_CHOICE){
	default:
	case 0:
		m_mutationType.setString("Mutation type : Average");
		break;
	case 1:
		m_mutationType.setString("Mutation type : 1/2 Split");
		break;}

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	


}

void System::GAReproduceAVG(NPC* t_npcOne, NPC* t_npcTwo)
{
	m_trackedOneNPC = t_npcOne;
	m_trackedTwoNPC = t_npcTwo;


	std::array<float, 4> DNA_ONE = t_npcOne->getDNA();
	std::array<float, 4> DNA_TWO = t_npcTwo->getDNA();
	std::array<float, 4> DNA_THREE;

	t_npcOne->setEndPosition(t_npcTwo->getPos());
	t_npcTwo->setEndPosition(t_npcOne->getPos());

	m_heartSprite[m_heartSprite.size()-1].setPosition(sf::Vector2f((t_npcOne->getPos().x), (t_npcOne->getPos().y)));
	m_heartSprite[m_heartSprite.size() - 1].setPosition(sf::Vector2f((t_npcTwo->getPos().x), (t_npcTwo->getPos().y)));


	float Mutations[4] ;
	Mutations[0] = 0;
	Mutations[1] = 0;
	Mutations[2] = 0;
	Mutations[3] = 0;
	

	int mutationChance;
	float number;
	for (int i = 0; i < 4; i++)
	{
		if (m_wantedStatistics[i] == 1) // if the statistic is desirable 
		{
			mutationChance = randomNumber(100, 0);
			if (mutationChance <= 25 ) {Mutations[i] = -m_mutationArray[i];} // 25% chance to reduce
			else if (mutationChance >=40) {Mutations[i] = m_mutationArray[i];} // 60% chance to increase
			else{Mutations[i] = 0;}// 15% chance to do nothing
		}
		else{
			mutationChance = randomNumber(100,0);
			if (mutationChance <= 33) // 33% chance 
			{
				number = m_mutationArray[i];
				Mutations[i] = -m_mutationArray[i];
			}
			else if(mutationChance >= 66) // 33% chance 
			{
				number = m_mutationArray[i];
				Mutations[i] = m_mutationArray[i];
			}
			else {Mutations[i] = 0;}// 33% chance
		}
	}
	//+++++++++AVG split DNA++++++++++
	DNA_THREE[0] = (DNA_ONE[0] + DNA_TWO[0]) / 2;
	DNA_THREE[1] = (DNA_ONE[1] + DNA_TWO[1]) / 2;
	DNA_THREE[2] = (DNA_ONE[2] + DNA_TWO[2]) / 2;
	DNA_THREE[3] = (DNA_ONE[3] + DNA_TWO[3]) / 2;



	for (int i = 0; i < 4; i++)
	{
		 
		DNA_THREE[i] += Mutations[i];
		if (DNA_THREE[i] < 1) { DNA_THREE[i] = 1;}
		if (DNA_THREE[i] > 100) { DNA_THREE[i] = 100; }
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

	if (m_npcs[m_npcs.size() - 1]->getGenertaion() > m_highestGen) {m_highestGen = m_npcs[m_npcs.size() - 1]->getGenertaion();}
}

void System::GAReproduceSplit(NPC* t_npcOne, NPC* t_npcTwo)
{
	m_trackedOneNPC = t_npcOne;
	m_trackedTwoNPC = t_npcTwo;


	std::array<float, 4> DNA_ONE = t_npcOne->getDNA();
	std::array<float, 4> DNA_TWO = t_npcTwo->getDNA();
	std::array<float, 4> DNA_THREE;

	t_npcOne->setEndPosition(t_npcTwo->getPos());
	t_npcTwo->setEndPosition(t_npcOne->getPos());

	m_heartSprite[m_heartSprite.size() - 1].setPosition(sf::Vector2f((t_npcOne->getPos().x), (t_npcOne->getPos().y)));
	m_heartSprite[m_heartSprite.size() - 1].setPosition(sf::Vector2f((t_npcTwo->getPos().x), (t_npcTwo->getPos().y)));


	float Mutations[4];
	Mutations[0] = 0;
	Mutations[1] = 0;
	Mutations[2] = 0;
	Mutations[3] = 0;


	int mutationChance;
	float number;
	for (int i = 0; i < 4; i++)
	{
		if (m_wantedStatistics[i] == 1) // if the statistic is desirable 
		{
			mutationChance = randomNumber(100, 0);
			if (mutationChance <= 25) { Mutations[i] = -m_mutationArray[i]; } // 25% chance to reduce
			else if (mutationChance >= 40) { Mutations[i] = m_mutationArray[i]; } // 60% chance to increase
			else { Mutations[i] = 0; }// 15% chance to do nothing
		}
		else {
			mutationChance = randomNumber(100, 0);
			if (mutationChance <= 33) // 33% chance 
			{
				number = m_mutationArray[i];
				Mutations[i] = -m_mutationArray[i];
			}
			else if (mutationChance >= 66) // 33% chance 
			{
				number = m_mutationArray[i];
				Mutations[i] = m_mutationArray[i];
			}
			else { Mutations[i] = 0; }// 33% chance
		}
	}

	DNA_THREE[0] = DNA_ONE[0];
	DNA_THREE[1] = DNA_ONE[1];
	DNA_THREE[2] = DNA_TWO[2];
	DNA_THREE[3] = DNA_TWO[3];




	for (int i = 0; i < 4; i++)
	{

		DNA_THREE[i] += Mutations[i];
		if (DNA_THREE[i] < 1) { DNA_THREE[i] = 1; }
		if (DNA_THREE[i] > 100) { DNA_THREE[i] = 100; }
	}


	m_npcs.push_back(new NPC(m_window, m_ArialBlackfont));


	if (t_npcOne->getGenertaion() > t_npcTwo->getGenertaion() || t_npcOne->getGenertaion() == t_npcTwo->getGenertaion())
	{
		m_npcs[m_npcs.size() - 1]->setGenertaion((t_npcOne->getGenertaion() + 1));
	}
	else { m_npcs[m_npcs.size() - 1]->setGenertaion((t_npcTwo->getGenertaion() + 1)); }


	m_npcs[m_npcs.size() - 1]->setDNA(DNA_THREE);
	m_npcs[m_npcs.size() - 1]->setPosition(sf::Vector2f((t_npcOne->getPos().x + t_npcTwo->getPos().x) / 2, (t_npcOne->getPos().y + t_npcTwo->getPos().y) / 2));
	m_npcs[m_npcs.size() - 1]->setUpGAvar(REPRODUCTION_TIME, AGE_CAP);
	m_npcs[m_npcs.size() - 1]->setUpNpc(m_IDCount);
	m_IDCount++;

	t_npcOne->resetReproductionTimer();
	t_npcTwo->resetReproductionTimer();

	if (m_npcs[m_npcs.size() - 1]->getGenertaion() > m_highestGen) { m_highestGen = m_npcs[m_npcs.size() - 1]->getGenertaion(); }

}

//++++++++++ Getters for average Statistics ++++++++++

/// <summary>
/// Get Average NPC SPEED
/// </summary>
float System::GetAvgSpeed()
{
	m_avgStatistic = 0;
	for (int i = 0; i < m_npcs.size(); i++) {m_avgStatistic += m_npcs[i]->GetSpeedStatistic();}
	m_avgStatistic = m_avgStatistic / m_npcs.size();
	return m_avgStatistic;
}
/// <summary>
/// Get Average NPC Strength 
/// </summary>
float System::GetAvgStr()
{
	m_avgStatistic = 0;
	for (int i = 0; i < m_npcs.size(); i++) {m_avgStatistic += m_npcs[i]->GetSizeStatistic();}
	m_avgStatistic = m_avgStatistic / m_npcs.size();
	return m_avgStatistic;
}
/// <summary>
/// Get Average NPC intelegnece 
/// </summary>
float System::GetAvgInt()
{
	m_avgStatistic = 0;
	for (int i = 0; i < m_npcs.size(); i++) {m_avgStatistic += m_npcs[i]->GetIntStatistic();}
	m_avgStatistic = m_avgStatistic / m_npcs.size();
	return m_avgStatistic;
}
/// <summary>
/// Get Average NPC size 
/// </summary>
float System::GetAvgSize()
{
	m_avgStatistic = 0;
	for (int i = 0; i < m_npcs.size(); i++) {m_avgStatistic += m_npcs[i]->GetIntStatistic();}
	m_avgStatistic = m_avgStatistic / m_npcs.size();
	return m_avgStatistic;
}


void System::GAStartUp()
{
	m_npcs.reserve(STARTER_AMOUNT);
	for (int i = 0; i < STARTER_AMOUNT; i++) { m_npcs.push_back(new NPC(m_window, m_ArialBlackfont)); }
	for (int i = 0; i < STARTER_AMOUNT / 2; i++) { m_npcs[i]->setGender(1); }

	for (int i = 0; i < m_npcs.size(); i++) {
		m_npcs[i]->setUpGAvar(REPRODUCTION_TIME, AGE_CAP);
		m_npcs[i]->setUpNpcStart(m_IDCount); m_IDCount++;
	}

	m_trackedOneNPC = m_npcs[0];
	m_trackedTwoNPC = m_npcs[1];
}

void System::GAReproductionWanted()
{
	for (int i = 0; i < m_npcs.size(); i++)
	{
		if (m_npcs[i]->getAge() >= (AGE_CAP / 4) && m_npcs[i]->getAge() <= ((AGE_CAP / 4) * 3)) //check if the first npc is within the corect age range 
		{
			if (m_npcs[i]->getReproductionCooldown() <= 0)//check if the npc is able to bread 
			{
				for (int j = 0; j < m_npcs.size(); j++)
				{
					if (m_npcs[i] != m_npcs[j])//is the npc's the same npc
					{
						if (m_npcs[j]->getAge() >= (AGE_CAP / 4) && m_npcs[j]->getAge() <= ((AGE_CAP / 4) * 3))//check if the second npc is within the corect age range 
						{
							if (m_npcs[i]->getGender() != m_npcs[j]->getGender()) //check if the genders are opposite 
							{
								if (m_npcs[j]->getReproductionCooldown() <= 0)//check if the npc is able to bread 
								{
									m_distanceBetweenNPC =
										sqrt((pow((m_npcs[j]->getPos().x - m_npcs[i]->getPos().x), 2)) +
										(pow((m_npcs[j]->getPos().y - m_npcs[i]->getPos().y), 2)));

									if (m_distanceBetweenNPC <= BREEDING_DISTANCE)
									{
										if(m_wantedStatistics[0] == 1)//speed wanted 
										{if (m_npcs[j]->GetSpeedStatistic() >= m_npcs[i]->GetSpeedStatistic()) {m_runningReproductionChance -= REPRODUCTION_INCREASE;}}//increase the chance of reproduction
										
										if (m_wantedStatistics[1] == 1)//Strength wanted
										{if (m_npcs[j]->GetStrStatistic() >= m_npcs[i]->GetStrStatistic()) { m_runningReproductionChance -= REPRODUCTION_INCREASE;}}//increase the chance of reproduction
										
										if (m_wantedStatistics[2] == 1)//intelegence wanted
										{if (m_npcs[j]->GetIntStatistic() >= m_npcs[i]->GetIntStatistic()) { m_runningReproductionChance -= REPRODUCTION_INCREASE;}} //increase the chance of reproduction
										
										if (m_wantedStatistics[3] == 1)//size wanted
										{if (m_npcs[j]->GetSizeStatistic() >= m_npcs[i]->GetSizeStatistic()) { m_runningReproductionChance -= REPRODUCTION_INCREASE;}} //increase the chance of reproduction
										
										if (randomNumber(m_runningReproductionChance,0) <= REPRODUCTION_CHANCE_THRESHOLD)
										{

											switch (m_Mutation_CHOICE)
											{
											default:
											case 0:
												GAReproduceSplit(m_npcs[i], m_npcs[j]);
												break;
											case 1:
												GAReproduceAVG(m_npcs[i], m_npcs[j]);
												break;
											}

											m_runningReproductionChance = REPRODUCTION_CHANCE;
										}
										else{
											m_npcs[i]->resetReproductionTimer();//failed reproduction wait till try again rest 
											m_npcs[j]->resetReproductionTimer();//failed reproduction wait till try again rest 
											m_runningReproductionChance = REPRODUCTION_CHANCE;}

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

void System::GAReproductionHighest()
{


	float m_highestMaleState = 0;
	float m_highestFemaleState = 0;
	float m_runningStatTotal = 0;




	for (int i = 0; i < m_npcs.size(); i++)
	{
		if (m_npcs[i]->getAge() >= (AGE_CAP / 4) && m_npcs[i]->getAge() <= ((AGE_CAP / 4) * 3)) //check if the first npc is within the corect age range 
		{
			if (m_npcs[i]->getReproductionCooldown() <= 0)//check if the npc is able to bread 
			{m_npcBreedingGroup.push_back(i);}
		}
	}


	if(m_npcBreedingGroup.size() > 2)
	{
	m_highestMaleState = 0;
	m_highestFemaleState = 0;
	m_runningStatTotal = 0;

	m_maleHeighest = m_npcBreedingGroup[randomNumber(m_npcBreedingGroup.size() - 1, 0)];
	m_femaleHeighest = m_npcBreedingGroup[randomNumber(m_npcBreedingGroup.size() - 1, 0)];

	for (int i = 0; i < m_npcBreedingGroup.size(); i++)
	{
		if (m_npcs[m_npcBreedingGroup[i]]->getGender() == 1)//male
		{
			if (m_wantedStatistics[0] == 1){m_runningStatTotal += m_npcs[m_npcBreedingGroup[i]]->GetSpeedStatistic();}
			if (m_wantedStatistics[1] == 1){m_runningStatTotal += m_npcs[m_npcBreedingGroup[i]]->GetStrStatistic();}
			if (m_wantedStatistics[2] == 1){m_runningStatTotal += m_npcs[m_npcBreedingGroup[i]]->GetIntStatistic();}
			if (m_wantedStatistics[3] == 1) {m_runningStatTotal += m_npcs[m_npcBreedingGroup[i]]->GetSizeStatistic();}

			if (m_highestMaleState < m_runningStatTotal){
				m_maleHeighest = i;
				m_highestMaleState = m_runningStatTotal;}
		}
		else if (m_npcs[m_npcBreedingGroup[i]]->getGender() == 0)//female
		{
			if (m_wantedStatistics[0] == 1) { m_runningStatTotal += m_npcs[m_npcBreedingGroup[i]]->GetSpeedStatistic(); }
			if (m_wantedStatistics[1] == 1) { m_runningStatTotal += m_npcs[m_npcBreedingGroup[i]]->GetStrStatistic(); }
			if (m_wantedStatistics[2] == 1) { m_runningStatTotal += m_npcs[m_npcBreedingGroup[i]]->GetIntStatistic(); }
			if (m_wantedStatistics[3] == 1) { m_runningStatTotal += m_npcs[m_npcBreedingGroup[i]]->GetSizeStatistic(); }

			if (m_highestFemaleState < m_runningStatTotal) {
				m_femaleHeighest = i;
				m_highestFemaleState = m_runningStatTotal;}
		}		
	}

	switch (m_Mutation_CHOICE)
	{
	default:
	case 0:
		GAReproduceSplit(m_npcs[m_maleHeighest], m_npcs[m_femaleHeighest]);
		break;
	case 1:
		GAReproduceAVG(m_npcs[m_maleHeighest], m_npcs[m_femaleHeighest]);
		break;
	}
		m_npcs[m_maleHeighest]->resetReproductionTimer();//failed reproduction wait till try again rest 
		m_npcs[m_femaleHeighest]->resetReproductionTimer();//failed reproduction wait till try again rest 
	}
	m_npcBreedingGroup.clear();

}
