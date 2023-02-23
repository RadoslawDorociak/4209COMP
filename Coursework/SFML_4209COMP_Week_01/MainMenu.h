#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class MainMenu :
    public sf::Drawable
{
public:
    MainMenu(std::string texFile, int wWidth, int wHeight);
    void update(sf::Time elapsedTime);
    bool goingUp;
    bool goingRight;
    bool m_initialised;
    int pressButton();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Texture m_tsTexture;
    sf::Sprite m_tsSprite;
    sf::Font m_textFont;
    sf::Text* m_startGameText;
    sf::Text* m_OptionsText;
    sf::Text* m_ExitText;
    sf::Text* m_SelectedText;
    void checkButton(sf::Text* button);
    void highLightButton(sf::Text* button);
    //int pressButton();
    sf::Time m_flashingTime;
    sf::Time m_lastFlashTime;
    bool m_flashOn;
    sf::FloatRect textBox;

};

