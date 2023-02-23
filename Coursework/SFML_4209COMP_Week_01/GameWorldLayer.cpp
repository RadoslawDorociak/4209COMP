#include "GameWorldLayer.h"
GameWorldLayer::GameWorldLayer(std::string textFile, float parallaxFactor, int vWidth, int vHeight)
	:m_layText()
	, m_layVert(sf::Quads, 4)
	,m_parFactor(parallaxFactor)
	{
	if (m_layText.loadFromFile(textFile)) {
		m_layText.setRepeated(true);
		//0-1
		//3-2
		m_layVert[0].position = sf::Vector2f(0.f, 0.f);
		m_layVert[1].position = sf::Vector2f(vWidth  , 0.f);
		m_layVert[2].position = sf::Vector2f(vWidth, vHeight );
		m_layVert[3].position = sf::Vector2f(0.f, vHeight );

		m_layVert[0].texCoords = sf::Vector2f(0.f, 0.f);
		m_layVert[1].texCoords = sf::Vector2f(vWidth, 0.f);
		m_layVert[2].texCoords = sf::Vector2f(vWidth, vHeight);
		m_layVert[3].texCoords = sf::Vector2f(0.f, vHeight);
	}
}
void GameWorldLayer::followCam(Camera* camera) {
	sf::FloatRect camWindows = camera->getCameraWindow(m_parFactor);
	int left = camWindows.left;
	int right = camWindows.left + camWindows.width;
	int top = camWindows.top;
	int bottom = camWindows.top + camWindows.height;

	/*m_layVert[0].position = sf::Vector2f(left, top);
	m_layVert[1].position = sf::Vector2f(left, bottom);
	m_layVert[2].position = sf::Vector2f(right, bottom);
	m_layVert[3].position = sf::Vector2f(right, top);*/

	m_layVert[0].texCoords = sf::Vector2f(left, top);
	m_layVert[1].texCoords = sf::Vector2f(right, top);
	m_layVert[2].texCoords = sf::Vector2f(right, bottom);
	m_layVert[3].texCoords = sf::Vector2f(left, bottom);
}

void GameWorldLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.texture = &m_layText;
	target.draw(m_layVert, states);

}
void GameWorldLayer::setParallaxFactor(float parallaxFactor) {
	m_parFactor = parallaxFactor;
}
float GameWorldLayer::getParallaxFactor() {
	return m_parFactor;
}