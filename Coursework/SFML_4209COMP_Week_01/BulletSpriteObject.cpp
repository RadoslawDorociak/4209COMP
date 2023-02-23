#include "BulletSpriteObject.h"


BulletSpriteObject::BulletSpriteObject()
	: m_distanceTravelled(0)
	, m_active(true)
{
}


BulletSpriteObject::~BulletSpriteObject()
{
}

void BulletSpriteObject::setSpeed(float speed)
{
	m_moveSpeed = speed;
}

void BulletSpriteObject::setMoveDirection(sf::Vector2f directionVector, bool rotate)
{
	m_moveDirection = directionVector;

	if (rotate)
	{
		const float PI = 3.1415;
		float angleRadian = atan2(directionVector.y, directionVector.x);
		float angleDegree = angleRadian / PI * 180;
		setRotation(angleDegree);
	}
}

void BulletSpriteObject::setMaxRange(float range)
{
	m_maxRange = range;
}

void BulletSpriteObject::update(float elapsedTime)
{
	if (m_active)
	{
		move(m_moveDirection*m_moveSpeed*elapsedTime);
		m_distanceTravelled += m_moveSpeed*elapsedTime;

		if (m_distanceTravelled >= m_maxRange)
			m_active = false;
	}

	SpriteObject::update(elapsedTime);
}

bool BulletSpriteObject::isActive()
{
	return m_active;
}

void BulletSpriteObject::applyTexture(sf::Texture* texture)
{
	m_initialised = true;
	m_sprTexture = texture;
	// Setting default origin and rectangle
	m_spriteOrigin = sf::Vector2f(m_sprTexture->getSize().x / 2, m_sprTexture->getSize().y / 2);
	m_textRectangle = sf::IntRect(0, 0, m_sprTexture->getSize().x, m_sprTexture->getSize().y);
}
