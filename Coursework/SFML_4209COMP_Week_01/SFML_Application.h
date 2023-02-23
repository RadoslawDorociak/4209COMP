#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TitleScreen.h"
#include "StoryScreen.h"
#include "MainMenu.h"
#include "GameWorldLayer.h"
#include "GameWorld.h"
#include "Credits.h"
enum AppState {
    TITLESCREEN,
    MAINMENU,
    GAMEPLAY,
    EXIT,
    CREDITS,
    STORY
};

class SFML_Application :
    public sf::NonCopyable
{
public:
    SFML_Application(int windowWidth, int windowHeight);
    void run();
    void update(sf::Time elapsedTime);
    void start();
    void render();
    bool detectClick(sf::Event evnt);
    bool m_initialised;
    bool clicked;
    bool initState;
    sf::RenderWindow m_Window;
    std::size_t m_screenWidth;
    std::size_t m_screenHeight;
    sf::Event m_event;
    
    SFML_Application::~SFML_Application();
private:
    sf::Time m_timeCount;
    GameWorld m_gameWorld;
    sf::Time m_updateTimer;
    std::size_t m_FPSCount;
    void updateFPS(sf::Time elapsedTime);
    MainMenu m_MainMenu;
    TitleScreen m_TitleScreen;
    StoryScreen m_StoryScreen;
    Credits m_Credits;
    AppState m_appState;
    bool m_creditsPlayed;
    sf::Text* m_messegeText;
    sf::Font m_textFont;
};

