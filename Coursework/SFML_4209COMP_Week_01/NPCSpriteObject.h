#pragma once
#include "AnimSpriteObject.h"
class NPCSpriteObject :
	public AnimSpriteObject
{
public:
			NPCSpriteObject();
	virtual ~NPCSpriteObject();

	virtual void	update(float elapsedTime, sf::Vector2f targetPoint);

	void	setTargetLocation(sf::Vector2f targetLocation);
	void	setMovementSpeed(float speed);

	int		setIdleAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);
	int		setWalkingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);
	int		setAttackingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);

	void	toIdleState();
	void	toWalkingState();
	void	toAttackingState();

	bool inInVision(sf::Vector2f targetPoint);

private:

	enum NPCState {
		IDLE,
		WALKING,
		ATTACKING
	};

	NPCState		m_state;
	
	sf::Vector2f	m_targetLocation;
	float			m_moveSpeed;
	int				m_idleAnimationID;
	int				m_walkingAnimationID;
	int				m_attackingAnimationID;

	float			m_visionConeAngle;
	float			m_visionRange;
};

