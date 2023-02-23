#include "Credits.h"
Credits::Credits(std::string texFile, int wWidth, int wHeight)
{
	m_tsTexture.loadFromFile(texFile);
	m_tsLogoText.loadFromFile("media/textures/company.png");

	m_tsSprite.setTexture(m_tsTexture);
	m_tsSprite.setColor(sf::Color(100, 100, 100));
	m_tsLogo.setTexture(m_tsLogoText);
	sf::Vector2u textSize = m_tsTexture.getSize();
	sf::Vector2u textSize2 = m_tsLogoText.getSize();
	m_tsSprite.setTextureRect(sf::IntRect(0, 0, textSize.x, textSize.y));
	m_tsLogo.setTextureRect(sf::IntRect(0, 0, textSize2.x, textSize2.y));
	m_tsSprite.setPosition(0, 0);
	m_tsLogo.setPosition(-400, -400);
	m_initialised = m_textFont.loadFromFile("media/fonts/SegoeMarker.ttf");
	m_messegeText = new sf::Text();
	m_messegeText->setFont(m_textFont);
	m_messegeText->setPosition(wWidth / 2, wHeight * 2.2);
	m_messegeText->setFillColor(sf::Color(220, 220, 255, 255));
	m_creditsDone = false;
}

void Credits::update(sf::Time elapsedTime) {

	m_messegeText->setString("Mostly Gud Games\n\nLead Programmer : \nRadoslaw Dorociak\n\nLead Artist : \nBaroque Obama\n\nProgrammers : \nSmith Smith\nWilliam Willson\n\nArtists : \nPablo PicsArto\nLeonardo DaPaint\n\nSpecial acknowledgements:\n\nDr. Sud Sudirman\nFor all the help and support\n\ndementiaRunner\nWire texture\n\nhhh316\nCracked Dirt Texture\n\nMy cat Richard\nPosing for pictures\n\nAnother cat, Albert\nCurrently in the background");
	m_messegeText->setCharacterSize(50);
	textBox = m_messegeText->getLocalBounds();

	m_messegeText->setOrigin(textBox.width / 2, textBox.height / 2);
	m_tsLogo.setPosition(m_messegeText->getPosition().x - 100, m_messegeText->getPosition().y - 1200);
	m_messegeText->setPosition(m_messegeText->getPosition().x, m_messegeText->getPosition().y - 1);
	if (m_messegeText->getPosition().y < -700) {
		m_creditsDone = true;
		m_messegeText->setPosition(1920 / 2, 1080 * 2);

	}

}
void Credits::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_tsSprite);
	target.draw(m_tsLogo);
	target.draw(*m_messegeText);
}