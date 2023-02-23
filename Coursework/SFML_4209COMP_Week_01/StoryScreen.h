#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class StoryScreen :
    public sf::Drawable
{
public:
    StoryScreen(std::string texFile, int wWidth, int wHeight);
    void update(sf::Time elapsedTime);
    bool goingUp;
    bool goingRight;
    bool m_initialised;
    sf::FloatRect textBox;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Texture m_tsTexture;
    sf::Sprite m_tsSprite;
    sf::Font m_textFont;
    sf::Text* m_messegeText;
    sf::Time m_flashingTime;
    sf::Time m_lastFlashTime;
    bool m_flashOn;
    std::string storyText;
    int curTextLenght;
};

