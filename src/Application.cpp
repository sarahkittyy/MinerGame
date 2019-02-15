#include "Application.hpp"

Application::Application()
	: mWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y),
			  "Miner",
			  sf::Style::Titlebar | sf::Style::Close),
	  mMap("map"),
	  mBuilder(&mMap),
	  mUpgrades(&mBuilder)
{
	mWindow.setFramerateLimit(60);

	// Init ImGui
	ImGui::SFML::Init(mWindow);
	mImGuiClock.restart();

	//Init the UpgradeManager.
	mUpgrades.loadUpgradeData(mBuilder.getObjectData());

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

	//Get the right-bottom coordinate of the map.
	sf::Vector2i bottom_right = {
		WINDOW_SIZE.x - 260,
		WINDOW_SIZE.y - 200};

	// Update ImGui
	ImGui::SFML::Update(mWindow, mImGuiClock.restart());

	// Get ImGui window flags.
	ImGuiWindowFlags default_flags =
		ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoTitleBar;

	// Init building window.///////////////////////////////////
	ImGui::Begin("General",
				 nullptr,
				 ImVec2(bottom_right.x, 200),
				 -1.0f,
				 default_flags);
	ImGui::SetWindowPos(ImVec2(0, bottom_right.y));

	// Create a child container for the building buttons.
	ImGui::BeginChild("BuildingButtons",
					  ImVec2(150, 180),
					  true,
					  default_flags & ~ImGuiWindowFlags_NoTitleBar);
	ImGui::Columns(5, nullptr, false);

	// Render the building manager's gui components.
	mBuilder.renderGuiBuildings();

	ImGui::EndChild();

	ImGui::SameLine();

	//Create a child container for the upgrades.
	ImGui::BeginChild("UpgradeButtons",
					  ImVec2(150, 180),
					  true,
					  default_flags & ~ImGuiWindowFlags_NoTitleBar);
	ImGui::Columns(5, nullptr, false);

	//Render the upgrade GUI's buttons here.
	mUpgrades.renderGui();

	ImGui::EndChild();

	// Stop initializing imgui window componenets.
	ImGui::End();
	////////////////////////////////////////////////////////

	// Create the statistics window.////////////////////
	ImGui::Begin("Statistics",
				 nullptr,
				 ImVec2(260, bottom_right.y - 200),
				 -1.0f,
				 default_flags);
	ImGui::SetWindowPos(ImVec2(bottom_right.x, 0));

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
	ImGui::Begin("Tooltip",
				 nullptr,
				 ImVec2(260, 400),
				 -1.0f,
				 default_flags);
	ImGui::SetWindowPos(ImVec2(bottom_right.x, bottom_right.y - 200));

	// Create the child container for the building manager tooltip.
	ImGui::BeginChild(
		"TooltipBuildings",
		ImVec2(200, 325),
		false,
		default_flags);

	//If not rendering the upgrade tooltip...
	if (!mUpgrades.renderGuiTooltip())
	{
		// Render the resource tooltip.
		mBuilder.renderGuiTooltip();
	}



	ImGui::EndChild();

	ImGui::End();
	//////////////////////////////////////////////////////
}