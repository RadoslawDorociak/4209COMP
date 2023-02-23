#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Camera
{
public:
	Camera(int wWidth, int wHeight);
	sf::FloatRect getCameraWindow(float parallaxFactor);
	void setPosition(sf::Vector2f target);
	void zoomUp();
	void zoomDown();
	float m_camZoom;
	float m_camZoomMin;
	float m_camZoomMax;
	sf::Transform getViewTransform() const;
	sf::Transform getProjTransform() const;
private:
	sf::Vector2f m_camWinSize;
	sf::Vector2f m_camPos;

};

