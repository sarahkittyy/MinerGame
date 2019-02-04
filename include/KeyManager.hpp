#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

/**
 * @brief Simple mostly static KeyManager class for retrieving the state of the keyboard & mouse globally.
 * 
 */
class KeyManager
{
public:
	/**
	 * @brief Set the internal window reference for getMousePos()
	 * 
	 * @param mWindowPtr A pointer to the window on which this class is operating on. 
	 * 
	 * @remarks CALL THIS!! >w<
	 */
	static void setWindowReference(sf::RenderWindow* mWindowPtr);

	/**
	 * @brief Main key updating function. Call once per frame.
	 * 
	 */
	static void update();

	/**
	 * @brief Retrieve the mouse position.
	 * 
	 * @return sf::Vector2i The mouse position.
	 */
	static sf::Vector2i getMousePos();

	/**
	 * @brief Retrieve the LMB state.
	 * 
	 * @return short The state of the left mouse button.
	 * 
	 * @see getKeyState
	 */
	static short getLMouseState();
	
	/**
	 * @brief Retrieve the RMB state.
	 * 
	 * @return short The state of the right mouse button.
	 * 
	 * @see getKeyState
	 */
	static short getRMouseState();

	/**
	 * @brief Retrieves current keyboard states.
	 * 
	 * @param key 
	 * @return short The state of the key.
	 * 
	 * @remarks 
	 * 		0: Unpressed
	 * 		1: Pressed
	 * 		2: Just Released
	 */
	static short getKeyState(sf::Keyboard::Key key);

private:

	/**
	 * @brief The internal window reference.
	 * 
	 */
	static sf::RenderWindow* mWindowPtr;

	/**
	 * @brief A map of keys and their respective current state.
	 * 
	 */
	static std::unordered_map<sf::Keyboard::Key, short> mKeyStates;

	/**
	 * @brief The current LMB state.
	 * 
	 */
	static short mLMouseState;
	
	/**
	 * @brief The current RMB state.
	 * 
	 */
	static short mRMouseState;
};