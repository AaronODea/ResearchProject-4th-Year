#include "Gui.h"

GUI::GUI(sf::RenderWindow& t_window) :
	m_window(t_window),
	m_lines(sf::LinesStrip, 4)
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

void GUI::SetUpLineGraph()
{

	m_YaxisGraph.setFillColor(sf::Color::Black);
	m_YaxisGraph.setSize(sf::Vector2f(10, 400));
	m_YaxisGraph.setPosition(sf::Vector2f(50, 1050) );

	m_XaxisGraph.setFillColor(sf::Color::Black);
	m_XaxisGraph.setSize(sf::Vector2f(2000, 10));
	m_XaxisGraph.setPosition(sf::Vector2f(50, 1450));


	m_lines[0].position = sf::Vector2f(50, 1450);
	m_lines[1].position = sf::Vector2f(1000, 1300);
	m_lines[2].position = sf::Vector2f(1200, 1200);
	m_lines[3].position = sf::Vector2f(2000, 1050);

	m_lines.append(sf::Vector2f(2400, 1050));
	for (int i = 0; i < m_lines.getVertexCount(); i++)
	{
		m_lines[i].color = sf::Color::Black;

	}
	

	


	

}
