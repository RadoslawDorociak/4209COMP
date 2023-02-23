#include "AnimSpriteObject.h"
#include <fstream>
#include <sstream>
#include <string>

AnimSpriteObject::AnimSpriteObject()
	: m_curAnimation(NULL),
	m_isPaused(false),
	m_curAnimID(-1)
{

}
AnimSpriteObject::~AnimSpriteObject() {
	for (std::vector<sf::Texture*>::iterator it = m_spriteTextList.begin();
		it != m_spriteTextList.end();
		++it) {
		delete (*it);
	}
	m_spriteTextList.clear();
	for (std::vector<SpriteAnimation*>::iterator it = m_animatedSpriteList.begin();
		it != m_animatedSpriteList.end();
		++it) {
		delete (*it);
	}
	m_animatedSpriteList.clear();
}

int AnimSpriteObject::addAnimation(std::string spriteSheetFile, std::string spriteInfoFile, float animTime) {
	sf::Texture* spriteText = new sf::Texture();
	if (!spriteText->loadFromFile(spriteSheetFile)) {
		return -1;
	}
	m_spriteTextList.push_back(spriteText);
	SpriteAnimation* animation = new SpriteAnimation();
	animation->setSpriteSheet(spriteText);
	std::string left;
	std::string top;
	std::string width;
	std::string height;
	std::string xcenter;
	std::string ycenter;
	
	int ileft, itop, iwidth, iheight, ixcenter, iycenter;
	int frameCounter = 0;

	std::ifstream inputFile(spriteInfoFile);
	if (inputFile.is_open()) do {
		std::string stringLine;
		std::getline(inputFile, stringLine);
		if (inputFile.good()) {
			std::istringstream stringStream(stringLine);
			stringStream >> left;
			stringStream >> top;
			stringStream >> width;
			stringStream >> height;
			stringStream >> xcenter;
			stringStream >> ycenter;
			ileft = std::stoi(left);
			itop = std::stoi(top);
			iwidth = std::stoi(width);
			iheight = std::stoi(height);
			ixcenter = std::stoi(xcenter);
			iycenter = std::stoi(ycenter);
			animation->addFrame(sf::IntRect(ileft, itop, iwidth, iheight), sf::Vector2f(ixcenter - ileft, iycenter - itop));
			frameCounter++;
		}
		else break;
	} while (true);
	inputFile.close();
	if (frameCounter > 0) {
		animation->setFrameTime(animTime / frameCounter);
		m_animatedSpriteList.push_back(animation);
		m_initialised = true;
		
		return m_animatedSpriteList.size() - 1;
	}
	else return -1;
		
}
void AnimSpriteObject::setCurAnim(int animIndex) {
	SpriteAnimation* newAnim = m_animatedSpriteList[animIndex];
	if (newAnim) {
		if (m_curAnimation != newAnim) {
			m_curAnimation = newAnim;
			m_sprTexture = m_curAnimation->getSpriteSheet();
			m_curAnimation->resetCurAnimation();
			m_curAnimation->getCurFrame(&m_textRectangle, &m_spriteOrigin);
			m_curTime = 0;
		}

	}
}
SpriteAnimation* AnimSpriteObject::getCurAnim() {
	return m_curAnimation;
}
void AnimSpriteObject::play() {
	m_isPaused = false;
}
void AnimSpriteObject::pause() {
	m_isPaused = true;
}
void AnimSpriteObject::stop() {
	m_isPaused = true;
	m_curTime = 0;
}
void AnimSpriteObject::update(float elapsedTime) {
	if (!m_isPaused && m_curAnimation) {
		float frameTime = m_curAnimation->getTimePerFrame();
		m_curTime += elapsedTime;
		if (m_curTime >= frameTime) {
			m_curAnimation->incrementFrameNum();
			m_curAnimation->getCurFrame(&m_textRectangle, &m_spriteOrigin);
			m_curTime = m_curTime - frameTime;
			
		}

	}
	SpriteObject::update(elapsedTime);
}