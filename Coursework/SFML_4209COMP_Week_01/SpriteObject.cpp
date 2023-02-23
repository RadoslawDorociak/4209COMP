#include "SpriteObject.h"
SpriteObject::SpriteObject() 
	:m_initialised(false) 
{
	m_defTexture = NULL;

}
SpriteObject::~SpriteObject() {
	if (m_defTexture != NULL) delete m_defTexture;
}
bool SpriteObject::setDefTexture(std::string textFile) {

	if (m_defTexture != NULL) delete m_defTexture;
	m_defTexture = new sf::Texture();
	if (!m_defTexture->loadFromFile(textFile)) {
		m_initialised = false;
		delete m_defTexture;
		m_defTexture = NULL;
		
		return false;
	}
	m_sprTexture = m_defTexture;
	m_spriteOrigin = sf::Vector2f(m_defTexture->getSize().x / 2, m_defTexture->getSize().y / 2);
	m_textRectangle = sf::IntRect(0, 0, m_defTexture->getSize().x, m_defTexture->getSize().y);
	m_initialised = true;
	
	return true;
	
}

bool SpriteObject::setDefTexture(std::string textFile, std::string spriteInfFile) {
	if (m_defTexture != NULL) delete m_defTexture;
	m_defTexture = new sf::Texture();
	if (!m_defTexture->loadFromFile(textFile)) {
		m_initialised = false;
		delete m_defTexture;
		m_defTexture = NULL;
		return false;
	}
	m_sprTexture = m_defTexture;
	std::string s_left, s_top, s_width, s_height, s_xcenter, s_ycenter;
	int i_left, i_top, i_width, i_height, i_xcenter, i_ycenter;
	std::ifstream inputFile(spriteInfFile);
	if (inputFile.is_open()) {
		std::string stringLine;
		std::getline(inputFile, stringLine);
		if (inputFile.good()) {
			std::istringstream stringStream(stringLine);
			stringStream >> s_left;
			stringStream >> s_top;
			stringStream >> s_width;
			stringStream >> s_height;
			stringStream >> s_xcenter;
			stringStream >> s_ycenter;
			i_left = std::stoi(s_left);
			i_top = std::stoi(s_top);
			i_width = std::stoi(s_width);
			i_height = std::stoi(s_height);
			i_xcenter = std::stoi(s_xcenter);
			i_ycenter = std::stoi(s_ycenter);
		}
		m_spriteOrigin = sf::Vector2f(i_xcenter - i_left, i_ycenter - i_top);
		m_textRectangle = sf::IntRect(i_left, i_top, i_width, i_height);
		inputFile.close();
		m_initialised = true;
		return true;
	}
}
void SpriteObject::setColor(const sf::Color& color) {
	m_sprite.setColor(color);
}
sf::FloatRect SpriteObject::getLocalBounds() const {
	float left = static_cast<float> (-m_spriteOrigin.x);
	float top = static_cast<float> (-m_spriteOrigin.y);
	float width = static_cast<float> (m_textRectangle.width);
	float height = static_cast<float> (m_textRectangle.height);
	return sf::FloatRect(left, top, width, height);
}
sf::FloatRect SpriteObject::getGlobalBounds() const {
	return getTransform().transformRect(getLocalBounds());
}
sf::Vector2f SpriteObject::getPositionWorld() {
	return getTransform().transformPoint(0, 0);
}
sf::Vector2f SpriteObject::getPositionScreen(sf::Transform ViewProjTransform) {
	sf::Transform WorldViewProjTransform = ViewProjTransform * getTransform();
	return WorldViewProjTransform * sf::Vector2f();
}
void SpriteObject::update(float elapsedTime) {
	
	if (!m_initialised)return;
	if (m_sprTexture != NULL)m_sprite.setTexture(*m_sprTexture);
	
	m_sprite.setTextureRect(m_textRectangle);

	m_sprite.setOrigin(m_spriteOrigin);
}
void SpriteObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_sprite, states);
}
