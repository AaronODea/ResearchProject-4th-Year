#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>



class GUI
{
public:
	GUI(sf::RenderWindow& t_window);
	~GUI();

	void Draw();
	void update(float t_AvgStatistic, int t_highestGen);

	void SetUpLineGraph();
	void updateGraph(float t_AvgStatistic, int t_highestGen);

private:

	sf::RenderWindow& m_window;

	int m_currentGenerationHeld = -1;

	int tempXvalueGraph = 50;
	int tempYvalueGraph = 1450;

	sf::VertexArray m_lines;



	sf::RectangleShape m_YaxisGraph;
	sf::RectangleShape m_XaxisGraph;





};