#pragma once
#include <SFML/Graphics.hpp>



class GUI
{
public:
	GUI(sf::RenderWindow& t_window);
	~GUI();

	void Draw();
	void SetUpLineGraph();

private:

	sf::RenderWindow& m_window;



	sf::VertexArray m_lines;



	sf::RectangleShape m_YaxisGraph;
	sf::RectangleShape m_XaxisGraph;





};