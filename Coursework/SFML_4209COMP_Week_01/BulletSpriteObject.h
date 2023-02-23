#pragma once
#include "SpriteObject.h"
class BulletSpriteObject :
	public SpriteObject
{
public:
	BulletSpriteObject();
	virtual ~BulletSpriteObject();

	virtual void	update(float elapsedTime);

	void			setMaxRange(float range);
	void			setSpeed(float speed);
	void			setMoveDirection(sf::Vector2f directionVector, bool rotate);
	void			applyTexture(sf::Texture* texture);
	bool			isActive();

private:

	float			m_moveSpeed;
	sf::Vector2f	m_moveDirection;
	
	float			m_maxRange;
	float			m_distanceTravelled;
	bool			m_active;
};

