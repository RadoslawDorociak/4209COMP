#pragma once
#include <SFML/Graphics.hpp>
class SpriteAnimation
{
public:
	SpriteAnimation();
	~SpriteAnimation();
	void setSpriteSheet(sf::Texture* spriteText);
	void addFrame(sf::IntRect textureRect, sf::Vector2f centre);
	bool getCurFrame(sf::IntRect* rect, sf::Vector2f* centre);
	void setFrameTime(float timePerFrame);
	float getFrameTime();
	float getTimePerFrame();
	sf::Texture* getSpriteSheet();
	int getNumOfFrames();

	void getTextureInfo(int newFrame, sf::IntRect* rect, sf::Vector2f* centre);
	
	void setLoop(bool loop);
	bool isLooped() const;

	void setCanBeInterrupted(bool torf);
	bool canBeInterrupted() const;

	void incrementFrameNum();
	int getCurFrameNum();
	void resetCurAnimation();

	bool isCompleted();
	
	
private:
	std::vector<sf::IntRect> m_frameRectList;
	std::vector<sf::Vector2f> m_frameCentreList;

	sf::Texture* m_spritesheet;

	int m_curFrameNum;
	float m_timePerFrame;

	bool m_isLoop;
	bool m_canBeInterrupted;
};

