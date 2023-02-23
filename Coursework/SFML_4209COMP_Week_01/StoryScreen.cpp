#include "StoryScreen.h"
StoryScreen::StoryScreen(std::string texFile, int wWidth, int wHeight)
{
	m_tsTexture.loadFromFile(texFile);
	m_tsSprite.setTexture(m_tsTexture);
	sf::Vector2u textSize = m_tsTexture.getSize();
	m_tsSprite.setTextureRect(sf::IntRect(0, 0, textSize.x, textSize.y));
	m_tsSprite.setPosition(0,0);
	m_tsSprite.setColor(sf::Color(100, 100, 100));
	m_initialised = m_textFont.loadFromFile("media/fonts/SegoeMarker.ttf");
	m_messegeText = new sf::Text();
	m_messegeText->setFont(m_textFont);
	m_messegeText->setPosition(wWidth / 2, wHeight/2);
	m_messegeText->setFillColor(sf::Color(220,220,255,255));

	storyText = "For many years the kingdom of cats has lived in peace and harmony, surrounded by beauty and fluffiness. One day, however, vicious creatures attacked it. Ugly and terrifying, the only \nthing worse than their look being their smell: the goblins. In appearance, they resembled regular cats, however they were ugly and filthy, with ears like those of bats. Wasn’t long \nbefore many parts of the kingdom were overrun. And so the cats had to find a way to stop the invasion. The invading forces have been led by baron Bert, by far the baldest of them \nall. He waged war with no mercy and needed to be stopped. For that a hero would need to be sent out to face him and his army of horrible beings. It took a long time to determine \nwho would be the most appropriate for the task. Many options were considered, from Lynx warriors of the north, to proud Lions of the south. A meeting was called by the council \nwhere all met up and discussed the options. The first suggestion was to use simple brute force, implied by the tigers that were proud of their physical prowess. Yet any warrior \nwould fall when facing near unlimited hordes. Another suggestion came from American cats, that simply wanted to use guns. As they lacked physical ability, no champion was \nsuggested for them. The idea to use guns, however was widely accepted. Queen of the kingdom was more in favor of direct weaponry, such as knives. As they had plenty of both, \nthey decided to equip the hero with both.\n\n\n\nA problem still remained, while the debate about the weapons was finished, no hero was yet selected. And so they debated for days upon days as the forces of goblins have spread \nand burned their lands. Many more champions were suggested, too numerous to list. As the enemy was closing in on the capital, it was clear that a decision needs to be made and \nit needs to be made fast. However, as bureaucracy tends to work, no decision was made in time and the kingdom has fallen and almost everyone perished, cursing their politicians with \ntheir last breath. In the end very few survived and formed groups focused on guerilla warfare, hoping ot regain their ground against the goblin hordes. Most of those groups, \nhowever perished just as the armies of various kingdoms. At this point it seemed that all hope was lost, and it wasn’t all that far fetched, however, one hero still remained ready to \npick up arms against the invaders. And then he died, another tried. The cycle repeated for a long time, seemingly stalling inevitable destiny. As the end was drawing near it was clear \nthat the old kingdom cannot be restored, but then one cat, exceptionally fluffy decided to pick up a gun, a knife and just do it his own way. While unlikely that he will succeed, he will \nnot rest until peace is once again the norm in the kingdom of cats, and baron Bert with his army of evil goblins is driven out.\n\nPress Any Button To Continue";
		curTextLenght = 1;
}

void StoryScreen::update(sf::Time elapsedTime) {

		
	m_messegeText->setString(storyText.substr(0,curTextLenght));
	if (curTextLenght < storyText.length()) {
		curTextLenght++;
	}
		

	m_messegeText->setCharacterSize(26);
	textBox = m_messegeText->getLocalBounds();
	m_messegeText->setOrigin(textBox.left + textBox.width / 2.0f,
		textBox.top + textBox.height / 2.0f);
	m_messegeText->setOrigin(textBox.width / 2, textBox.height / 2);

	

	

	
	//m_messegeText->setPosition(m_messegeText->getPosition().x + 0.1, m_messegeText->getPosition().y + 0.1);
	
	//m_messegeText->setPosition(0, 0);
	}
void StoryScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_tsSprite);
	target.draw(*m_messegeText);
}