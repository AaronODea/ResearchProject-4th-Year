#include "Gui.h"

GUI::GUI(sf::RenderWindow& t_window, sf::Font& t_font) :
	m_window(t_window),
	m_font(t_font),
	m_lines(sf::TriangleFan, 2)
{
	WIDTH = m_window.getSize().x;
	HEIGHT = m_window.getSize().y;
	SetUpLineGraph();

	m_color.push_back(sf::Color::Black);
	m_color.push_back(sf::Color::Blue);
	m_color.push_back(sf::Color::Green);
	m_color.push_back(sf::Color::Yellow);
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

void GUI::update(float t_AvgStatistic, int t_highestGen, int t_currentStat)
{
	updateGraph(t_AvgStatistic,t_highestGen, t_currentStat);

}

void GUI::SetUpLineGraph()
{

	m_YaxisGraph.setFillColor(sf::Color::White);
	m_YaxisGraph.setOutlineColor(sf::Color::Black);
	m_YaxisGraph.setOutlineThickness(5);
	m_YaxisGraph.setSize(sf::Vector2f(WIDTH/250, HEIGHT/4.1f));
	m_YaxisGraph.setPosition(sf::Vector2f(WIDTH/50, HEIGHT/1.371f) );

	m_XaxisGraph.setFillColor(sf::Color::White);
	m_XaxisGraph.setOutlineColor(sf::Color::Black);
	m_XaxisGraph.setOutlineThickness(5);
	m_XaxisGraph.setSize(sf::Vector2f(WIDTH/2.5f, HEIGHT/150));
	m_XaxisGraph.setPosition(sf::Vector2f(WIDTH / 50, HEIGHT/1.0344f));


	m_averageGraphTextX.setFont(m_font);
	m_averageGraphTextY.setFont(m_font);

	//m_averageGraphTextX
	//m_averageGraphTextY

	m_lines[0].position = sf::Vector2f(WIDTH/31.667f, HEIGHT / 1.0344f);

	

	for (int i = 0; i < m_lines.getVertexCount(); i++)
	{
		m_lines[i].color = sf::Color::Black;

	}

}

void GUI::updateGraph(float t_AvgStatistic, int t_highestGen, int t_currentStat)
{


	if (m_currentGenerationHeld != t_highestGen)
	{
		if (m_AverageGraphX >= WIDTH/2.5){
			m_lines.clear();
			m_AverageGraphX = WIDTH/41.667f;
			m_lines.append(sf::Vector2f(m_AverageGraphX, m_AverageGraphY));
			m_lines.append(sf::Vector2f(m_AverageGraphX, m_AverageGraphY - (t_AvgStatistic) *  4));
			m_lines.append(sf::Vector2f(m_AverageGraphX, m_AverageGraphY - (t_AvgStatistic) * 4));
		}

		m_currentGenerationHeld = t_highestGen;	
		m_lines.resize(m_lines.getVertexCount()-1);
		m_lines.append(sf::Vector2f(m_AverageGraphX += WIDTH/125, m_AverageGraphY - (t_AvgStatistic)*  3));
		m_lines.append(sf::Vector2f(m_AverageGraphX, m_AverageGraphY));
	}
	for (int i = 0; i < m_lines.getVertexCount(); i++)
	{
		m_lines[i].color = m_color[t_currentStat];
	}
}
