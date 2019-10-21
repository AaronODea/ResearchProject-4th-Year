#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <SFML/Graphics.hpp>

class System
{
public:
	System();
	~System();
	/// <summary>
	/// main method
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message

	sf::Text m_temptext; // text used for message on screen

	bool m_exit; // control exiting 

};

#endif // !SYSTEM_HPP

