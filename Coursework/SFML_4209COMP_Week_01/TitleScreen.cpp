#include "TitleScreen.h"
TitleScreen::TitleScreen(std::string texFile, int wWidth, int wHeight)
{
	m_tsTexture.loadFromFile(texFile);
	m_tsSprite.setTexture(m_tsTexture);
	sf::Vector2u textSize = m_tsTexture.getSize();
	m_tsSprite.setTextureRect(sf::IntRect(0, 0, textSize.x, textSize.y));
	m_tsSprite.setPosition(0, 0);
	m_initialised = m_textFont.loadFromFile("media/fonts/SegoeMarker.ttf");
	m_messegeText = new sf::Text();
	m_messegeText->setFont(m_textFont);
	m_messegeText->setPosition(wWidth / 2, wHeight / 2);
	m_messegeText->setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
}

void TitleScreen::update(sf::Time elapsedTime) {

	m_messegeText->setString("PRESS ANY BUTTON");
	m_messegeText->setCharacterSize(100);
	textBox = m_messegeText->getLocalBounds();

	m_messegeText->setOrigin(textBox.width / 2, textBox.height / 2);

	if (m_messegeText->getPosition().x > 1920 - m_messegeText->getLocalBounds().width / 2) {
		goingRight = false;
		m_messegeText->setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	}
		
	if (m_messegeText->getPosition().x < 0 + m_messegeText->getLocalBounds().width / 2) {
		goingRight = true;
			m_messegeText->setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	}
		
		if (m_messegeText->getPosition().y < 0 - m_messegeText->getLocalBounds().height / 2) {
			goingUp = false;
			m_messegeText->setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	}
		
		if (m_messegeText->getPosition().y > 1080 - m_messegeText->getLocalBounds().height) {
			goingUp = true;
			m_messegeText->setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	}
		
	//m_messegeText->setPosition(m_messegeText->getPosition().x + 0.1, m_messegeText->getPosition().y + 0.1);
	if (goingUp) m_messegeText->setPosition(m_messegeText->getPosition().x, m_messegeText->getPosition().y - 5);
	else m_messegeText->setPosition(m_messegeText->getPosition().x, m_messegeText->getPosition().y + 5);

	if (goingRight) m_messegeText->setPosition(m_messegeText->getPosition().x + 5, m_messegeText->getPosition().y);
	else m_messegeText->setPosition(m_messegeText->getPosition().x - 5, m_messegeText->getPosition().y);
}
void TitleScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(m_tsSprite);
	target.draw(*m_messegeText);
}