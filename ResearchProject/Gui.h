#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>



class GUI
{
public:
	GUI(sf::RenderWindow& t_window);
	~GUI();

	void Draw();
	void update(float t_AvgStatistic, int t_highestGen, int t_currentStat);


	void SetUpLineGraph(sf::Font& t_font);
	void updateGraph(float t_AvgStatistic, int t_highestGen, int t_currentStat);

private:
	int WIDTH = 1920;
	int HEIGHT = 1080;


	sf::Text m_currentGeneration;

	sf::RenderWindow& m_window;

	int m_currentGenerationHeld = -1;

	int m_AverageGraphX = WIDTH/50;
	int m_AverageGraphY = HEIGHT / 1.0344f;

	sf::VertexArray m_lines;
	std::vector<sf::Color> m_color;

	sf::Text m_averageGraphTextX;
	sf::Text m_averageGraphTextY;

	sf::RectangleShape m_YaxisGraph;
	sf::RectangleShape m_XaxisGraph;





};