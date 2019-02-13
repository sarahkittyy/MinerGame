#include "Application.hpp"

Application::Application()
	: mWindow(sf::VideoMode(600, 600), "Miner", sf::Style::Titlebar | sf::Style::Close),
	  mMap("map"),
	  mBuilder(&mMap)
{
	mWindow.setFramerateLimit(60);

	// Init ImGui
	ImGui::SFML::Init(mWindow);
	mImGuiClock.restart();

	// Init the keyboard manager
	KeyManager::setWindowReference(&mWindow);
}

int Application::run()
{
	mWindow.resetGLStates();

	// Begin main application loop
	while (mWindow.isOpen())
	{
		// Poll Events
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			// Update ImGui
			ImGui::SFML::ProcessEvent(event);

			// Update SFML
			switch (event.type)
			{
			default:
				break;
			case sf::Event::Closed:
				mWindow.close();
				break;
			}
		}

		// Update the keyboard manager.
		KeyManager::update();

		// Update the GUI.
		mUpdateGui();

		// Update the building manager
		mBuilder.update();

		// Start drawing.
		mWindow.clear(BG_COLOR);

		mWindow.draw(mMap);
		mWindow.draw(mBuilder);

		// Render ImGui last.
		ImGui::SFML::Render(mWindow);
		// Finish drawing.
		mWindow.display();
	}

	// Release resources.
	ImGui::SFML::Shutdown();

	return 0;
}

void Application::mUpdateGui()
{
	// Update ImGui
	ImGui::SFML::Update(mWindow, mImGuiClock.restart());

	// Get ImGui window flags.
	ImGuiWindowFlags default_flags =
		ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoTitleBar;

	// Init building window.///////////////////////////////////
	ImGui::Begin("Buildings", nullptr, ImVec2(400, 200), -1.0f, default_flags);
	ImGui::SetWindowPos(ImVec2(0, 400));

	// Create a child container for the building buttons.
	ImGui::BeginChild("BuildingButtons",
					  ImVec2(120, 180),
					  true,
					  default_flags & ~ImGuiWindowFlags_NoTitleBar);
	ImGui::Columns(4, nullptr, false);

	// Render the building manager's gui components.
	mBuilder.renderGuiBuildings();

	ImGui::EndChild();

	// Stop initializing imgui window componenets.
	ImGui::End();
	////////////////////////////////////////////////////////

	// Create the statistics window.////////////////////
	ImGui::Begin("Statistics", nullptr, ImVec2(200, 250), -1.0f, default_flags);
	ImGui::SetWindowPos(ImVec2(400, 0));

	ImGui::Columns(4, nullptr, false);
	ImGui::SetColumnWidth(0, 20);
	ImGui::SetColumnWidth(1, 43);
	ImGui::SetColumnWidth(2, 15);
	ImGui::SetColumnWidth(3, 100);

	// Render the resource counts with their icons.
	mBuilder.renderGuiResources();

	ImGui::End();
	//////////////////////////////////////////////////////

	//////////////////////////////////////////////////////
	// Create the tooltip window.
	ImGui::Begin("Tooltip", nullptr, ImVec2(200, 350), -1.0f, default_flags);
	ImGui::SetWindowPos(ImVec2(400, 250));

	// Create the child container for the building manager tooltip.
	ImGui::BeginChild(
		"TooltipBuildings", ImVec2(200, 325), false, default_flags);

	// Render the resource tooltip.
	mBuilder.renderGuiTooltip();

	ImGui::EndChild();

	ImGui::End();
	//////////////////////////////////////////////////////
}