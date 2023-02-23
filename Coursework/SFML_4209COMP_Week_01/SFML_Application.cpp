#include "SFML_Application.h"
SFML_Application::SFML_Application(int windowWidth, int windowHeight)
	: m_Window(sf::VideoMode(windowWidth, windowHeight), "SFML Application", sf::Style::Fullscreen)
	, m_initialised(true)
	, m_screenWidth(windowWidth)
	, m_screenHeight(windowHeight)
	, m_appState(TITLESCREEN)
	, m_TitleScreen("media/textures/villain.png", windowWidth, windowHeight)
	, m_StoryScreen("media/textures/villain.png", windowWidth, windowHeight)
	, m_Credits("media/textures/villain.png", windowWidth, windowHeight)
	, m_MainMenu("media/textures/menu.jpg", windowWidth, windowHeight)
	//, m_camera(windowWidth, windowHeight)
	,m_updateTimer(sf::seconds(1.f/60.f))
	,m_timeCount(sf::seconds(0))
	,m_FPSCount(0)
	,m_gameWorld(windowWidth, windowHeight, &m_Window)
{
	m_textFont.loadFromFile("media/fonts/SegoeMarker.ttf");
	m_messegeText = new sf::Text();
	m_messegeText->setFont(m_textFont);
	m_messegeText->setPosition(windowWidth - 50, windowHeight -50);
	m_messegeText->setFillColor(sf::Color(255,255,255));
	
	//GameWorldLayer* background = new GameWorldLayer("media/textures/wall.png", 1, windowWidth, windowHeight);
	///*m_layerList.push_back(background);
	//m_camPos = sf::Vector2f(0, 0);*/
	m_Window.setFramerateLimit(60);
	m_creditsPlayed = false;
}
void SFML_Application::start() {
	if (m_appState == TITLESCREEN) {
		
	}

	
	
}
void SFML_Application::update(sf::Time elapsedTime) {
	
	
	m_Window.pollEvent(m_event);
	if (m_event.type == sf::Event::Closed ) {
		m_Window.close();
		
	}
	
	switch (m_appState)
	{
	case TITLESCREEN:
		m_TitleScreen.update(elapsedTime);
		if (m_event.type == sf::Event::KeyPressed) {
			
			m_appState = MAINMENU;
		}
		break;
	case MAINMENU:
		m_MainMenu.update(elapsedTime);
		
		
		if (detectClick(m_event)) {
			switch (m_MainMenu.pressButton()) {
			case 1:
			{
				//load game
				if (!m_creditsPlayed) {
					m_appState = STORY;
					m_creditsPlayed = true;
				}
					
				else m_appState = GAMEPLAY;
				break;
			}
			case 2: {
				//load credits
				m_appState = CREDITS;
				break;
			}
			case 3:{
				//exit
				m_Window.close();
				break;
				  }
			default: {
				//not likely to do anything, is here just in case
				break;
			}
			}
	
		}
		//m_messegeText->setString("Main Menu");
		break;
	case STORY:
		m_StoryScreen.update(elapsedTime);
		if (m_event.type == sf::Event::KeyPressed) {

			m_appState = GAMEPLAY;
		}
		break;
	case CREDITS:
		m_Credits.update(elapsedTime);
		if (m_event.type == sf::Event::KeyPressed) {
			m_appState = MAINMENU;
			
		}
		if (m_Credits.m_creditsDone) {
			m_Credits.m_creditsDone = false;
			m_appState = MAINMENU;
		}
		break;
	case GAMEPLAY:
		m_gameWorld.update(elapsedTime.asSeconds());
		if (m_event.key.code == sf::Keyboard::Escape ) {
			m_appState = MAINMENU;
			
		}
		if (m_gameWorld.m_playerHP < 0) {
			m_gameWorld.Reset();
			
		}
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			m_camPos.x = m_camPos.x + 10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			m_camPos.x = m_camPos.x - 10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			m_camPos.y = m_camPos.y + 10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			m_camPos.y = m_camPos.y - 10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			m_camera.zoomDown();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			m_camera.zoomUp();
		}
		m_camera.setPosition(m_camPos);
		m_layerList[0]->followCam(&m_camera);*/
		break;
	case EXIT:
		break;
	}
	
	

}

void SFML_Application::render() {
	m_Window.clear();
	switch (m_appState)
	{
	case TITLESCREEN:
		m_Window.draw(m_TitleScreen);
		
		break;
	case MAINMENU:
		m_Window.draw(m_MainMenu);
		break;
	case STORY:
		m_Window.draw(m_StoryScreen);

		break;
	case CREDITS:
		m_Window.draw(m_Credits);
		break;
	case GAMEPLAY:
		m_Window.draw(m_gameWorld);
		//m_Window.draw(*m_layerList[0]);
		break;
	case EXIT:
		break;
	}
	m_Window.draw(*m_messegeText);
	m_Window.display();
	
}
void SFML_Application::run() {
	if (!m_initialised) {
		return;
	}
	sf::Clock clock;
	//m_messegeText->setString("Title Screen");
	m_appState = TITLESCREEN;
	sf::Time timeSinceUpdate = sf::Time::Zero;
	while (m_Window.isOpen()) {
		sf::Time elapsedTime = clock.restart();
		timeSinceUpdate += elapsedTime;
		
		while (timeSinceUpdate > m_updateTimer) {
			update(m_updateTimer);
			timeSinceUpdate -= m_updateTimer;
		}
		//update(elapsedTime);
		updateFPS(elapsedTime);
		render();
		//std::cout << "works";
	}
}

void SFML_Application::updateFPS(sf::Time elapsedTime) {
	m_timeCount += elapsedTime;
	m_FPSCount += 1;

	if (m_timeCount >= sf::seconds(1.0f)) {
		std::cout << std::to_string(m_FPSCount) << " fps  ";
		m_messegeText->setString(std::to_string(m_FPSCount));
		m_timeCount -= sf::seconds(1.0f);
		m_FPSCount = 0;
	}
}
bool SFML_Application::detectClick(sf::Event evnt) {
	if (evnt.type == sf::Event::MouseButtonPressed) //Mouse button Pressed
	{
		if (evnt.mouseButton.button == sf::Mouse::Left && !clicked) //specifies
		{

			std::cout << " lmb-pressed " << std::endl;
			clicked = true;
			
		}
	}

	else
	{
		
			clicked = false;
			
		
	}
	return clicked;
}
SFML_Application::~SFML_Application() {
	/*for (std::vector<GameWorldLayer*>::iterator it = m_layerList.begin();
		it != m_layerList.end();
		it++) {
		delete (*it);

	}
	m_layerList.clear();*/
}