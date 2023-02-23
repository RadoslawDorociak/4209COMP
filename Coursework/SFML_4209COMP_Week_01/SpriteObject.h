#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
class SpriteObject :
    public sf::Drawable, public sf::Transformable
{
public:
    SpriteObject();
    virtual ~SpriteObject();
    bool setDefTexture(std::string texFile);
    bool setDefTexture(std::string texFile, std::string spriteInfFile);
    void setColor(const sf::Color& color);
    sf::Vector2f getPositionWorld();
    sf::Vector2f getPositionScreen(sf::Transform ViewProjTransform);
    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;
    virtual void update(float elapsedTime);
   /* void *setPosition(int posX, int posY);*/
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Texture* m_defTexture;
protected:
    sf::Sprite m_sprite;
    sf::Texture* m_sprTexture;
    sf::IntRect m_textRectangle;
    sf::Vector2f m_spriteOrigin;
    bool m_initialised;
};

