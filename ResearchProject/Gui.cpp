#include "Gui.h"

GUI::GUI(sf::RenderWindow& t_window) :
	m_window(t_window)
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

}

void GUI::SetUpLineGraph()
{

	m_YaxisGraph.setFillColor(sf::Color::Black);
	m_YaxisGraph.setSize(sf::Vector2f(10, 400));
	m_YaxisGraph.setPosition(sf::Vector2f(50, 1050) );

	m_XaxisGraph.setFillColor(sf::Color::Black);
	m_XaxisGraph.setSize(sf::Vector2f(2000, 10));
	m_XaxisGraph.setPosition(sf::Vector2f(50, 1450));


	//pt[0] = pt1 - sf::Vector2f((thick / 2.0f), (thick / 2.0f));
	//pt[1] = pt1 + sf::Vector2f((thick / 2.0f), .nb      (thick / 2.0f));
	//pt[2] = pt2 + sf::Vector2f((thick / 2.0f), (thick / 2.0f));
	//pt[3] = pt2 - sf::Vector2f((thick / 2.0f), (thick / 2.0f));
	//sf::SetFillColor(sf::Color(255, 255, 255, 255));
	//

}
