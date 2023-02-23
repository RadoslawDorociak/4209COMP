#include "NPCSpriteObject.h"


NPCSpriteObject::NPCSpriteObject()
	: m_targetLocation(0, 0)
	, m_moveSpeed(100.0f)
	, m_state(IDLE)
	, m_idleAnimationID(-1)
	, m_walkingAnimationID(-1)
	, m_attackingAnimationID(-1)
	, m_visionConeAngle(90.0f)
	, m_visionRange(600.0f)
{

}

NPCSpriteObject::~NPCSpriteObject()
{
}

int NPCSpriteObject::setIdleAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_idleAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_idleAnimationID;
}

int	NPCSpriteObject::setWalkingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_walkingAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_walkingAnimationID;
}

int NPCSpriteObject::setAttackingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_attackingAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_attackingAnimationID;
}

void NPCSpriteObject::toIdleState()
{
	m_state = IDLE;
	setCurAnim(m_idleAnimationID);
}

void NPCSpriteObject::toWalkingState()
{
	m_state = WALKING;
	setCurAnim(m_walkingAnimationID);
}

void NPCSpriteObject::toAttackingState()
{
	m_state = ATTACKING;
	setCurAnim(m_attackingAnimationID);
}

void NPCSpriteObject::setTargetLocation(sf::Vector2f targetLocation)
{
	m_targetLocation = targetLocation;
}

void NPCSpriteObject::setMovementSpeed(float speed)
{
	m_moveSpeed = speed;
}


bool NPCSpriteObject::inInVision(sf::Vector2f targetPoint) {
	const float PI = 3.1415f;
	sf::Vector2f curPos = getPosition();
	sf::Vector2f vector = targetPoint - curPos;
	float distance = sqrt(vector.x * vector.x + vector.y * vector.y);
	if (distance > m_visionRange) return false;
	if (distance < m_visionRange / 2) return true;
	float faceAngle = getRotation();
	float targetAngle = atan2(vector.y, vector.x);
	targetAngle = targetAngle * 180 / PI;

	while (targetAngle > 360) {
		targetAngle = targetAngle - 360;
	}
	while (targetAngle < 0) {
		targetAngle = targetAngle + 360;
	}
	float angleDifference = fabs(targetAngle - faceAngle);
	if (angleDifference <= m_visionConeAngle / 2) return true;
	else return false;

}void NPCSpriteObject::update(float elapsedTime, sf::Vector2f targetPoint)
{
	const float PI = 3.1415f;
	sf::Vector2f currentPosition = getPosition();
	sf::Vector2f faceDirection = m_targetLocation - currentPosition;
	if (inInVision(targetPoint)) {
		m_targetLocation = targetPoint;
	}
	float distance = sqrt(faceDirection.x * faceDirection.x + faceDirection.y * faceDirection.y);
	if (distance < elapsedTime * m_moveSpeed) {
		setPosition(m_targetLocation);
		toIdleState();
		setTargetLocation(sf::Vector2f(rand() % 4000 - 2000, rand() % 4000 - 2000));
	}
	else {
		float angle = atan2(faceDirection.y, faceDirection.x);
		setRotation(angle / PI * 180);
		sf::Vector2f unitMoveVector = sf::Vector2f(cos(angle), sin(angle));
		sf::Vector2f totalMoveVector = unitMoveVector * elapsedTime * m_moveSpeed;
		move(totalMoveVector);

		toWalkingState();
	}
	AnimSpriteObject::update(elapsedTime);
}