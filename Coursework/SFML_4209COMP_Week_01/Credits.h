#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Credits :
    public sf::Drawable
{
public:
    Credits(std::string texFile, int wWidth, int wHeight);
    void update(sf::Time elapsedTime);
    bool goingUp;
    bool goingRight;
    bool m_initialised;
    sf::FloatRect textBox;
    bool m_creditsDone;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Texture m_tsTexture;
    sf::Sprite m_tsSprite;
    sf::Texture m_tsLogoText;
    sf::Sprite m_tsLogo;
    sf::Font m_textFont;
    sf::Text* m_messegeText;
    sf::Time m_flashingTime;
    sf::Time m_lastFlashTime;
    bool m_flashOn;
    

};

