#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>



class GUI
{
public:
	GUI(sf::RenderWindow& t_window ,sf::Font& t_font);
	~GUI();

	void Draw();
	void update(float t_AvgStatistic, int t_highestGen);

	void SetUpLineGraph();
	void updateGraph(float t_AvgStatistic, int t_highestGen);

private:



	sf::Font m_font;
	sf::RenderWindow& m_window;

	int m_currentGenerationHeld = -1;

	int m_AverageGraphX = 50;
	int m_AverageGraphY = 1450;

	sf::VertexArray m_lines;


	sf::Text m_averageGraphTextX;
	sf::Text m_averageGraphTextY;

	sf::RectangleShape m_YaxisGraph;
	sf::RectangleShape m_XaxisGraph;





};