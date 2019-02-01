#include "KeyManager.h"

//STATIC DECL
sf::RenderWindow* KeyManager::mWindowPtr;
std::unordered_map<sf::Keyboard::Key, short> KeyManager::mKeyStates;
short KeyManager::mMouseState;
/////////////

void KeyManager::setWindowReference(sf::RenderWindow* newPtr)
{
	mWindowPtr = newPtr;
}

void KeyManager::update()
{
	//For every key supported by SFML...
	for(unsigned i = 0; i < (unsigned)sf::Keyboard::KeyCount; ++i)
	{
		//Temporary variable for the current key.
		sf::Keyboard::Key cKey = static_cast<sf::Keyboard::Key>(i);

		//If it's pressed, set it's state to pressed.
		if(sf::Keyboard::isKeyPressed(cKey))
		{
			mKeyStates[cKey] = 1;
		}
		else
		{
			//If it's not pressed, and was just pressed,
			//..it was just released.
			if(mKeyStates[cKey] == 1)
			{
				mKeyStates[cKey] = 2;
			}
			//Otherwise, it's unpressed.
			else mKeyStates[cKey] = 0;
		}
	}

	//Mouse position updates!
	//If the mouse is pressed, set state to 1.
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mMouseState = 1;
	}
	else
	{
		//Set the mouse state to just released if it was pressed..
		//Otherwise, set it to unpressed.
		mMouseState = (mMouseState == 1) ? (2) : (0);
	}
}

sf::Vector2i KeyManager::getMousePos()
{
	//Get the mouse position relative to the current window.
	return sf::Mouse::getPosition(*mWindowPtr);
}

short KeyManager::getMouseState()
{
	return mMouseState;
}

short KeyManager::getKeyState(sf::Keyboard::Key key)
{
	//Retrieve the state of the specified key.
	return mKeyStates[key];
}