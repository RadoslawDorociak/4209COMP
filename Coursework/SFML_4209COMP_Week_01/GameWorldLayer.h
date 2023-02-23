#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Camera.h"
class GameWorldLayer :
    public sf::Drawable
{
public:
    GameWorldLayer(std::string textureFile, float parallaxFactor,
        int vWidth, int vHeight);
    void followCam(Camera* camera);
    void setParallaxFactor(float parallaxFactor);
    float getParallaxFactor();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
    sf::Texture m_layText;
    sf::VertexArray m_layVert;
    float m_parFactor;
};

