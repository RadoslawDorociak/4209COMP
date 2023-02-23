#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteAnimation.h"
#include "SpriteObject.h"
class AnimSpriteObject:
	public SpriteObject
{
public:
	AnimSpriteObject();
	virtual ~AnimSpriteObject();
	int addAnimation(std::string spriteSheetFile, std::string spriteInfoFile, float animTime);
	void setCurAnim(int animIndex);
	SpriteAnimation* getCurAnim();
	virtual void update(float elapsedTime);
	void play();
	void pause();
	void stop();

private:
	std::vector<sf::Texture*> m_spriteTextList;
	int m_curAnimID;
	float m_curTime;
	bool m_isPaused;
	//bool m_initialised;
	//sf::IntRect m_textureRect;
	//sf::Vector2f m_spriteOrigin;
protected:
	std::vector<SpriteAnimation*> m_animatedSpriteList;
	SpriteAnimation* m_curAnimation;
	//sf::Texture* m_spriteTexture;
};

