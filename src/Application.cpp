#include "Application.hpp"

Application::Application() :
	mWindow(sf::VideoMode(600,600), "Miner")
{
	mWindow.setFramerateLimit(60);
	
	//Init ImGui
	ImGui::SFML::Init(mWindow);
	mImGuiClock.restart();
	
	//Init the keyboard manager
	KeyManager::setWindowReference(&mWindow);
	
	//Init the map.
	mMap.loadFromFilename("map");
	
	//Init the object map.
	mObjectMap.loadFromFilename("objectmap");
}

int Application::run()
{
	mWindow.resetGLStates();
	
	//Begin main application loop
	while(mWindow.isOpen())
	{
		//Poll Events
		sf::Event event;
		while(mWindow.pollEvent(event))
		{
			//Update ImGui
			ImGui::SFML::ProcessEvent(event);
			
			//Update SFML
			switch(event.type)
			{
			default:
				break;
			case sf::Event::Closed:
				mWindow.close();
				break;
			}
		}
		
		//Update the keyboard manager.
		KeyManager::update();
		
		//Update the GUI.
		mUpdateGui();
		
		//Start drawing.
		mWindow.clear(BG_COLOR);
		
		mWindow.draw(mMap);
		mWindow.draw(mObjectMap);
		
		//Render ImGui last.
		ImGui::SFML::Render(mWindow);
		//Finish drawing.
		mWindow.display();
	}
	
	//Release resources.
	ImGui::SFML::Shutdown();
	
	return 0;
}

void Application::mUpdateGui()
{
	//Update ImGui
	ImGui::SFML::Update(mWindow, mImGuiClock.restart());
	
	//Init window components.
	ImGui::Begin("Miner");
	
	//Stop initializing imgui window componenets.
	ImGui::End();	
}