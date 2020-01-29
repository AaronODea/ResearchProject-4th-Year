#include "Gui.h"

GUI::GUI(sf::RenderWindow& t_window) :
	m_window(t_window),
	m_lines(sf::LinesStrip, 1)
{
	SetUpLineGraph();
}

GUI::~GUI()
{
}

void GUI::Draw()
{

	m_window.draw(m_XaxisGraph);
	m_window.draw(m_YaxisGraph);
	m_window.draw(m_lines);

}

void GUI::update(float t_AvgStatistic, int t_highestGen)
{
	updateGraph(t_AvgStatistic,t_highestGen);

}

void GUI::SetUpLineGraph()
{

	m_YaxisGraph.setFillColor(sf::Color::Black);
	m_YaxisGraph.setSize(sf::Vector2f(10, 400));
	m_YaxisGraph.setPosition(sf::Vector2f(50, 1050) );

	m_XaxisGraph.setFillColor(sf::Color::Black);
	m_XaxisGraph.setSize(sf::Vector2f(2000, 10));
	m_XaxisGraph.setPosition(sf::Vector2f(50, 1450));


	m_lines[0].position = sf::Vector2f(50, 1450);
	

	for (int i = 0; i < m_lines.getVertexCount(); i++)
	{
		m_lines[i].color = sf::Color::Black;

	}
	

	


	

}

void GUI::updateGraph(float t_AvgStatistic, int t_highestGen)
{

	if (m_currentGenerationHeld < t_highestGen)
	{
		m_currentGenerationHeld = t_highestGen;
		m_lines.append(sf::Vector2f(tempXvalueGraph += 10, tempYvalueGraph - (t_AvgStatistic)));
	}

	for (int i = 0; i < m_lines.getVertexCount(); i++)
	{
		m_lines[i].color = sf::Color::Black;

	}

//	std::cout << t_AvgStatistic << std::endl;

}
