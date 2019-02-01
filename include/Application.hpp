#include <SFML/Graphics.hpp>

/**
 * @brief Base application class.
 * 
 */
class Application
{
public:
	/**
	 * @brief Initializes all game objects.
	 * 
	 */
	Application();
	
	/**
	 * @brief Main game loop / logic handling.
	 * 
	 * @return int The exit code of the program.
	 */
	int run();
	
private:
	/**
	 * @brief The main SFML renderwindow.
	 * 
	 */
	sf::RenderWindow mWindow;	
};