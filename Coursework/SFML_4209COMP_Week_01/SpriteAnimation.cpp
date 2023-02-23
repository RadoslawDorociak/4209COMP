#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation() 
	: m_curFrameNum(0),
	m_canBeInterrupted(true),
	m_isLoop(true)
{


}
SpriteAnimation::~SpriteAnimation() {
	m_frameCentreList.clear();
	m_frameRectList.clear();
}
void SpriteAnimation::setSpriteSheet(sf::Texture* spriteText) {
	m_spritesheet = spriteText;
}

sf::Texture* SpriteAnimation::getSpriteSheet() {
	return m_spritesheet;
}

void SpriteAnimation::addFrame(sf::IntRect textureRect, sf::Vector2f centre) {
	m_frameRectList.push_back(textureRect);
	m_frameCentreList.push_back(centre);
}
int SpriteAnimation::getNumOfFrames() {
	return m_frameRectList.size();
}

bool SpriteAnimation::getCurFrame(sf::IntRect* rect, sf::Vector2f* centre) {
	if ((m_curFrameNum < 0) || (m_curFrameNum >= m_frameRectList.size())) {
		return false;
	}

	sf::IntRect irect = m_frameRectList[m_curFrameNum];
	sf::Vector2f icenter = m_frameCentreList[m_curFrameNum];

	rect->left = irect.left;
	rect->top = irect.top;
	rect->width = irect.width;
	rect->height = irect.height;

	centre->x = icenter.x;
	centre->y = icenter.y;

	return true;
}

int SpriteAnimation::getCurFrameNum() {
	return m_curFrameNum;
}

void SpriteAnimation::resetCurAnimation() {
	m_curFrameNum = 0;
}

void SpriteAnimation::setFrameTime(float timePerFrame) {
	m_timePerFrame = timePerFrame;
}
float SpriteAnimation::getFrameTime() {
	return m_timePerFrame;
}
float SpriteAnimation::getTimePerFrame() {
	return m_timePerFrame;
}
void SpriteAnimation::incrementFrameNum() {
	m_curFrameNum++;
	if (m_curFrameNum >= m_frameRectList.size() - 1) {
		if (m_isLoop) resetCurAnimation();
		else m_curFrameNum = m_frameRectList.size() - 1;
	}
}
bool SpriteAnimation::isCompleted() {
	if (m_curFrameNum >= m_frameRectList.size() - 1) return true;
	else return false;
}
bool SpriteAnimation::isLooped() const {
	return m_isLoop;
}
void SpriteAnimation::setLoop(bool loop) {
	m_isLoop = loop;
}
bool SpriteAnimation::canBeInterrupted() const {
	return m_canBeInterrupted;
}
void SpriteAnimation::setCanBeInterrupted(bool torf) {
	m_canBeInterrupted = torf;
}

