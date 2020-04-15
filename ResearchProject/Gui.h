#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>



class GUI
{
public:
	GUI(sf::RenderWindow& t_window);
	~GUI();

	void Draw();
	void update(float t_speedAVG, float t_strAVG, float t_intAVG, float t_sizeAVG, int t_highestGen, int t_currentStat);


	void SetUpLineGraph(sf::Font& t_font);
	void updateGraphSpeed(float t_AvgStatistic);
	void updateGraphStr(float t_AvgStatistic);
	void updateGraphInt(float t_AvgStatistic);
	void updateGraphSize(float t_AvgStatistic);


private:
	int WIDTH = 1920;
	int HEIGHT = 1080;

	int m_currentStat = 0;


	sf::Text m_currentAVG;

	sf::RenderWindow& m_window;

	int m_currentGenerationHeld = -1;

	int m_AverageGraphXSpeed = WIDTH/50;
	int m_AverageGraphXStr = WIDTH / 50;
	int m_AverageGraphXInt = WIDTH / 50;
	int m_AverageGraphXSize = WIDTH / 50;


	int m_AverageGraphYSpeed = HEIGHT / 1.0344f;
	int m_AverageGraphYStr = HEIGHT / 1.0344f;
	int m_AverageGraphYInt = HEIGHT / 1.0344f;
	int m_AverageGraphYSize = HEIGHT / 1.0344f;

	sf::VertexArray m_linesSpeed;
	sf::VertexArray m_linesStr;
	sf::VertexArray m_linesInt;
	sf::VertexArray m_linesSize;

	std::vector<float> m_speedAvgLog;
	std::vector<float> m_strAvgLog;
	std::vector<float> m_intAvgLog;
	std::vector<float> m_sizedAvgLog;

	std::vector<int> m_totalPopulationLog;


	std::vector<sf::Color> m_color;

	sf::Text m_averageGraphTextX;
	sf::Text m_averageGraphTextY;

	sf::RectangleShape m_YaxisGraph;
	sf::RectangleShape m_XaxisGraph;





};