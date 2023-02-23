#include "MainMenu.h"
MainMenu::MainMenu(std::string texFile, int wWidth, int wHeight)
{
	m_tsTexture.loadFromFile(texFile);
	m_tsSprite.setTexture(m_tsTexture);
	sf::Vector2u textSize = m_tsTexture.getSize();
	m_tsSprite.setTextureRect(sf::IntRect(0, 0, textSize.x, textSize.y));
	m_tsSprite.setPosition(0, 0);
	
	m_initialised = m_textFont.loadFromFile("media/fonts/SegoeMarker.ttf");
	m_startGameText = new sf::Text();
	m_OptionsText = new sf::Text();
	m_ExitText = new sf::Text();
	m_startGameText->setFont(m_textFont);
	m_OptionsText->setFont(m_textFont);
	m_ExitText->setFont(m_textFont);
	m_startGameText->setPosition(wWidth / 6, wHeight - wHeight / 3);
	m_OptionsText->setPosition(wWidth / 6, wHeight - wHeight / 3.7f);
	m_ExitText->setPosition(wWidth / 6, wHeight - wHeight / 5);
	m_startGameText->setString("START GAME");
	m_OptionsText->setString("CREDITS");
	m_ExitText->setString("EXIT");
	m_startGameText->setCharacterSize(80);
	m_OptionsText->setCharacterSize(80);
	m_ExitText->setCharacterSize(80);
	textBox = m_startGameText->getLocalBounds();
	m_startGameText->setOrigin(textBox.width / 2, textBox.height / 2);
	textBox = m_OptionsText->getLocalBounds();
	m_OptionsText->setOrigin(textBox.width / 2, textBox.height / 2);
	textBox = m_ExitText->getLocalBounds();
	m_ExitText->setOrigin(textBox.width / 2, textBox.height / 2);
	m_startGameText->setFillColor(sf::Color(0, 0, 0));
	m_OptionsText->setFillColor(sf::Color(0, 0, 0));
	m_ExitText->setFillColor(sf::Color(0, 0, 0));
	m_SelectedText = m_startGameText;
}

void MainMenu::update(sf::Time elapsedTime) {
	checkButton(m_startGameText);
	checkButton(m_OptionsText);
	checkButton(m_ExitText);
	highLightButton(m_startGameText);
	highLightButton(m_OptionsText);
	highLightButton(m_ExitText);
	
}
void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_tsSprite);
	target.draw(*m_startGameText);
	target.draw(*m_OptionsText);
	target.draw(*m_ExitText);
}
void MainMenu::checkButton(sf::Text* button) {
	//textBox = button->getLocalBounds();
	if (sf::Mouse::getPosition().x > button->getPosition().x - button->getLocalBounds().width / 2 && sf::Mouse::getPosition().x < button->getPosition().x + button->getLocalBounds().width / 2) {
		if (sf::Mouse::getPosition().y > button->getPosition().y + button->getLocalBounds().height / 2  && sf::Mouse::getPosition().y < button->getPosition().y - button->getLocalBounds().height / 2 +100) {
			
			m_SelectedText = button;
		}

	}

}
void MainMenu::highLightButton(sf::Text* button) {
	if (button == m_SelectedText) {
		button->setFillColor(sf::Color(255, 0, 0));
		button->setStyle(sf::Text::Bold);
	}
	else {
		button->setFillColor(sf::Color(0, 0, 0));
		button->setStyle(sf::Text::Regular);
	}
}
int MainMenu::pressButton() {
	if (m_SelectedText == m_startGameText) {
		return 1;
	}
	else if (m_SelectedText == m_OptionsText) {
		return 2;
	}
	else if (m_SelectedText == m_ExitText) {
		return 3;
	}
}