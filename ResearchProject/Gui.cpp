#include "Gui.h"

GUI::GUI(sf::RenderWindow& t_window) :
	m_window(t_window),
	m_linesSpeed(sf::TriangleFan, 2),
	m_linesStr(sf::TriangleFan, 2),
	m_linesInt(sf::TriangleFan, 2),
	m_linesSize(sf::TriangleFan, 2)

{
	WIDTH = m_window.getSize().x;
	HEIGHT = m_window.getSize().y;

	m_color.push_back(sf::Color(255,102,102));
	m_color.push_back(sf::Color(255,178,102));
	m_color.push_back(sf::Color(255, 255, 102));
	m_color.push_back(sf::Color(178, 255, 102));
}



GUI::~GUI()
{
}

void GUI::Draw()
{

	m_window.draw(m_XaxisGraph);
	m_window.draw(m_YaxisGraph);

	switch (m_currentStat)//draw call for stat selected
	{
	default:
	case 0:
		m_window.draw(m_linesSpeed);
		break;
	case 1:
		m_window.draw(m_linesStr);
		break;
	case 2:
		m_window.draw(m_linesInt);
		break;
	case 3:
		m_window.draw(m_linesSize);
		break;
	}

	m_window.draw(m_currentAVG);
}

void GUI::update(float t_speedAVG, float t_strAVG, float t_intAVG, float t_sizeAVG, int t_highestGen, int t_currentStat) 
{
		m_currentStat = t_currentStat;

		if (m_currentGenerationHeld != t_highestGen)
		{
			updateGraphSpeed(t_speedAVG);
			updateGraphStr(t_strAVG);
			updateGraphInt(t_intAVG);
			updateGraphSize(t_sizeAVG);

			for (int i = 0; i < m_linesSpeed.getVertexCount(); i++) { m_linesSpeed[i].color = m_color[0]; }
			for (int i = 0; i < m_linesStr.getVertexCount(); i++) { m_linesStr[i].color = m_color[1]; }
			for (int i = 0; i < m_linesInt.getVertexCount(); i++) { m_linesInt[i].color = m_color[2]; }
			for (int i = 0; i < m_linesSize.getVertexCount(); i++) { m_linesSize[i].color = m_color[3]; }

			m_currentGenerationHeld = t_highestGen;


			/*log for data oputput to file*/
			//=============================================
			m_speedAvgLog.push_back(t_speedAVG);
			m_strAvgLog.push_back(t_strAVG);
			m_intAvgLog.push_back(t_intAVG);
			m_sizedAvgLog.push_back(t_sizeAVG);

			m_totalPopulationLog.push_back(t_highestGen);
			//=============================================
		}
		switch (t_currentStat)
		{
		default:
		case 0:
			m_currentAVG.setString(std::to_string(t_speedAVG));
			break;
		case 1:
			m_currentAVG.setString(std::to_string(t_strAVG));
			break;
		case 2:
			m_currentAVG.setString(std::to_string(t_intAVG));
			break;
		case 3:
			m_currentAVG.setString(std::to_string(t_sizeAVG));
			break;
		}
}

void GUI::SetUpLineGraph(sf::Font& t_font)
{

	m_YaxisGraph.setFillColor(sf::Color::White);
	m_YaxisGraph.setOutlineColor(sf::Color::Black);
	m_YaxisGraph.setOutlineThickness(WIDTH / 500);
	m_YaxisGraph.setSize(sf::Vector2f(WIDTH/250, HEIGHT/4.1f));
	m_YaxisGraph.setPosition(sf::Vector2f(WIDTH/50, HEIGHT/1.371f) );

	m_XaxisGraph.setFillColor(sf::Color::White);
	m_XaxisGraph.setOutlineColor(sf::Color::Black);
	m_XaxisGraph.setOutlineThickness(WIDTH/500);
	m_XaxisGraph.setSize(sf::Vector2f(WIDTH/2.5f, HEIGHT/150));
	m_XaxisGraph.setPosition(sf::Vector2f(WIDTH / 50, HEIGHT/1.0344f));


 	m_averageGraphTextX.setFont(t_font);
	m_averageGraphTextY.setFont(t_font);




	m_linesSpeed[0].position =sf::Vector2f(WIDTH / 41.667f,(HEIGHT / 1.0344f));
	m_linesStr[0].position = sf::Vector2f(WIDTH / 41.667f, (HEIGHT / 1.0344f));
	m_linesInt[0].position = sf::Vector2f(WIDTH / 41.667f, (HEIGHT / 1.0344f));
	m_linesSize[0].position = sf::Vector2f(WIDTH / 41.667f, (HEIGHT / 1.0344f));

	m_linesSpeed[1].position =sf::Vector2f(WIDTH / 41.667f,(HEIGHT / 1.0344f));
	m_linesStr[1].position = sf::Vector2f(WIDTH / 41.667f, (HEIGHT / 1.0344f));
	m_linesInt[1].position = sf::Vector2f(WIDTH / 41.667f, (HEIGHT / 1.0344f));
	m_linesSize[1].position = sf::Vector2f(WIDTH / 41.667f, (HEIGHT / 1.0344f));

	m_AverageGraphXSpeed = WIDTH / 41.667f;
	m_AverageGraphXStr = WIDTH / 41.667f;
	m_AverageGraphXInt = WIDTH / 41.667f;
	m_AverageGraphXSize = WIDTH / 41.667f;


	for (int i = 0; i < m_linesSpeed.getVertexCount(); i++) { m_linesSpeed[i].color = m_color[0];}
	for (int i = 0; i < m_linesStr.getVertexCount(); i++) { m_linesStr[i].color = m_color[1]; }
	for (int i = 0; i < m_linesInt.getVertexCount(); i++) { m_linesInt[i].color = m_color[2]; }
	for (int i = 0; i < m_linesSize.getVertexCount(); i++) { m_linesSize[i].color = m_color[3]; }


	m_currentAVG.setFont(t_font);
	m_currentAVG.setFillColor(sf::Color::Black);
	m_currentAVG.setPosition(sf::Vector2f(WIDTH / 41.667f, (HEIGHT / 1.0344f)));
	m_currentAVG.setCharacterSize(20);
	m_currentAVG.setString("");


}

void GUI::updateGraphSpeed(float t_AvgStatistic)
{
		m_AverageGraphYSpeed = (t_AvgStatistic * 2);
		m_linesSpeed.append(sf::Vector2f(m_AverageGraphXSpeed, (HEIGHT / 1.0344f) - m_AverageGraphYSpeed));

		if (m_AverageGraphXSpeed >= WIDTH / 2.5) {
			m_linesSpeed.clear();
			m_AverageGraphXSpeed = WIDTH / 41.667f;
			m_linesSpeed.append(sf::Vector2f(sf::Vector2f(WIDTH / 41.667f, (HEIGHT / 1.0344f))));
			m_linesSpeed.append(sf::Vector2f(sf::Vector2f(WIDTH / 41.667f, (HEIGHT / 1.0344f))));
		}

		m_linesSpeed.append(sf::Vector2f(m_AverageGraphXSpeed += (WIDTH / 200), (HEIGHT / 1.0344f) - m_AverageGraphYSpeed));
		m_linesSpeed.append(sf::Vector2f(m_AverageGraphXSpeed, (HEIGHT / 1.0344f)));
		m_linesSpeed.append(sf::Vector2f(m_AverageGraphXSpeed - (WIDTH / 200), (HEIGHT / 1.0344f)));

		m_currentAVG.setPosition(sf::Vector2f(m_AverageGraphXSpeed, (HEIGHT / 1.08f) - m_AverageGraphYSpeed));
}
void GUI::updateGraphStr(float t_AvgStatistic)
{

	m_AverageGraphYStr = (t_AvgStatistic * 2);
	m_linesStr.append(sf::Vector2f(m_AverageGraphXStr, (HEIGHT / 1.0344f) - m_AverageGraphYStr));

	if (m_AverageGraphXStr >= WIDTH / 2.5) {
		m_linesStr.clear();
		m_AverageGraphXStr = WIDTH / 41.667f;
		m_linesStr.append(sf::Vector2f(sf::Vector2f(WIDTH / 41.667f, (HEIGHT / 1.0344f))));
		m_linesStr.append(sf::Vector2f(sf::Vector2f(WIDTH / 41.667f, (HEIGHT / 1.0344f))));
	}

	m_linesStr.append(sf::Vector2f(m_AverageGraphXStr += (WIDTH / 200), (HEIGHT / 1.0344f) - m_AverageGraphYStr));
	m_linesStr.append(sf::Vector2f(m_AverageGraphXStr, (HEIGHT / 1.0344f)));
	m_linesStr.append(sf::Vector2f(m_AverageGraphXStr - (WIDTH / 200), (HEIGHT / 1.0344f)));

	m_currentAVG.setPosition(sf::Vector2f(m_AverageGraphXStr, (HEIGHT / 1.08f) - m_AverageGraphYStr));

}
void GUI::updateGraphInt(float t_AvgStatistic)
{
		m_AverageGraphYInt = (t_AvgStatistic * 2);
		m_linesInt.append(sf::Vector2f(m_AverageGraphXInt, (HEIGHT / 1.0344f) - m_AverageGraphYInt));


		if (m_AverageGraphXInt >= WIDTH / 2.5) {
			m_linesInt.clear();
			m_AverageGraphXInt = WIDTH / 41.667f;
			m_linesInt.append(sf::Vector2f(sf::Vector2f(WIDTH / 41.667f, (HEIGHT / 1.0344f))));
			m_linesInt.append(sf::Vector2f(sf::Vector2f(WIDTH / 41.667f, (HEIGHT / 1.0344f))));
		}

		m_linesInt.append(sf::Vector2f(m_AverageGraphXInt += (WIDTH / 200), (HEIGHT / 1.0344f) - m_AverageGraphYInt));
		m_linesInt.append(sf::Vector2f(m_AverageGraphXInt, (HEIGHT / 1.0344f)));
		m_linesInt.append(sf::Vector2f(m_AverageGraphXInt - (WIDTH / 200), (HEIGHT / 1.0344f)));

		m_currentAVG.setPosition(sf::Vector2f(m_AverageGraphXInt, (HEIGHT / 1.08f) - m_AverageGraphYInt));
}
void GUI::updateGraphSize(float t_AvgStatistic)
{
		m_AverageGraphYSize = (t_AvgStatistic * 2);
		m_linesSize.append(sf::Vector2f(m_AverageGraphXSize, (HEIGHT / 1.0344f) - m_AverageGraphYSize));


		if (m_AverageGraphXSize >= WIDTH / 2.5) {
			m_linesSize.clear();
			m_AverageGraphXSize = WIDTH / 41.667f;
			m_linesSize.append(sf::Vector2f(sf::Vector2f(WIDTH / 41.667f, (HEIGHT / 1.0344f))));
			m_linesSize.append(sf::Vector2f(sf::Vector2f(WIDTH / 41.667f, (HEIGHT / 1.0344f))));
		}
		m_linesSize.append(sf::Vector2f(m_AverageGraphXSize += (WIDTH / 200), (HEIGHT / 1.0344f) - m_AverageGraphYSize));
		m_linesSize.append(sf::Vector2f(m_AverageGraphXSize, (HEIGHT / 1.0344f)));
		m_linesSize.append(sf::Vector2f(m_AverageGraphXSize - (WIDTH / 200), (HEIGHT / 1.0344f)));

		m_currentAVG.setPosition(sf::Vector2f(m_AverageGraphXSize, (HEIGHT / 1.08f) - m_AverageGraphYSize));
}


