#include "Camera.h"
Camera::Camera(int wWidth, int wHeight) :
	m_camPos(0, 0) ,
	m_camWinSize(wWidth, wHeight),
m_camZoom(1), m_camZoomMin(0.5f), m_camZoomMax(1.3f) {

}

void Camera::setPosition(sf::Vector2f target) {
	m_camPos = target;
}
sf::FloatRect Camera::getCameraWindow(float parallaxFactor) {
	sf::FloatRect window;
	window.left = m_camPos.x - m_camWinSize.x / 2 * m_camZoom * parallaxFactor;
	window.top = m_camPos.y - m_camWinSize.y / 2 * m_camZoom * parallaxFactor;

	window.width = m_camWinSize.x * m_camZoom * parallaxFactor;
	window.height = m_camWinSize.y * m_camZoom * parallaxFactor;

	return window;
}
void Camera::zoomUp() {
	if (m_camZoom > m_camZoomMin)
	m_camZoom = m_camZoom - m_camZoom * 0.1f;
}
void Camera::zoomDown() {
	if(m_camZoom < m_camZoomMax)
	m_camZoom = m_camZoom + m_camZoom * 0.1f;
}
sf::Transform Camera::getViewTransform() const {
	sf::Transform transform = sf::Transform::Identity;
	transform.translate(m_camPos);
	return transform.getInverse();
}
sf::Transform Camera::getProjTransform() const {
	sf::Transform transform = sf::Transform::Identity;
	transform.translate(m_camWinSize.x / 2, m_camWinSize.y / 2);
	transform.scale(1.0f / m_camZoom, 1.0f / m_camZoom);
	return transform;
}