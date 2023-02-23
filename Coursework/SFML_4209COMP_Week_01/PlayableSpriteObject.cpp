#include "PlayableSpriteObject.h"


PlayableSpriteObject::PlayableSpriteObject()
	: m_readyToShoot(false)
	, m_rangeWeaponCooldown(0)
	, m_timeSinceLastShoot(0)
	, m_moveSpeed(200)
{
	m_bulletTexture.loadFromFile("media/textures/bullet.png");
	shot = false;
}


PlayableSpriteObject::~PlayableSpriteObject()
{

}

BulletSpriteObject* PlayableSpriteObject::processEvents(float elapsedTime, sf::Transform transform, sf::Vector2f mouseScreenPosition)
{

	BulletSpriteObject* bullet = NULL;

	const float PI = 3.1415f;

	// check mouse buttons state
	bool leftButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	bool rightButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);

	if (leftButtonPressed || rightButtonPressed)
	{
		// get character screen position
		sf::Vector2f charScreenPos = getPositionScreen(transform);

		// calculate vector difference
		sf::Vector2f differenceVector = mouseScreenPosition - charScreenPos;

		// calculate angle between the vector and the horizontal +ve x axis
		// horizontal positive x-axis is defined 0 degree, sprite facing right initially
		double angleinRadians = atan2(differenceVector.y, differenceVector.x);
		double angleinDegrees = angleinRadians / PI * 180;

		// calculate the magnitude of the difference vector
		double magnitude = sqrt(differenceVector.x*differenceVector.x + differenceVector.y*differenceVector.y);

		// normalise the difference vector
		differenceVector.x /= magnitude;
		differenceVector.y /= magnitude;

		if (rightButtonPressed)
		{
			setRotation(angleinDegrees);
			
			if (leftButtonPressed)	
			{		
				if (m_equippedWeapon == PISTOL) {
					if (!shot)
					{
						// Left-shift pressed -> Shoot
						
						bullet = shoot();
						toMeleeState();
						shot = true;
					}
					else
					{
						// Left-shift unpressed -> Melee
						shot = false;
						
					}
				}
				else {
					toMeleeState();
				}
				
			}
			
		}
	}

	float faceAngle = getRotation();

	float moveSpeed;
	sf::Vector2f moveDirection;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		float moveAngle = faceAngle - 90;
		moveAngle = moveAngle / 180 * PI;
		float cosine = cos(moveAngle);
		float sine = sin(moveAngle);

		moveSpeed = m_moveSpeed;
		moveDirection.x = cosine;
		moveDirection.y = sine;

		toWalkingState();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		float moveAngle = faceAngle + 90;
		moveAngle = moveAngle / 180 * PI;
		float cosine = cos(moveAngle);
		float sine = sin(moveAngle);

		moveSpeed = m_moveSpeed;
		moveDirection.x = cosine;
		moveDirection.y = sine;

		toWalkingState();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		float moveAngle = faceAngle;
		moveAngle = moveAngle / 180 * PI;
		float cosine = cos(moveAngle);
		float sine = sin(moveAngle);

		moveSpeed = m_moveSpeed;
		moveDirection.x = cosine;
		moveDirection.y = sine;

		toWalkingState();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		float moveAngle = faceAngle + 180;
		moveAngle = moveAngle / 180 * PI;
		float cosine = cos(moveAngle);
		float sine = sin(moveAngle);

		moveSpeed = m_moveSpeed;
		moveDirection.x = cosine;
		moveDirection.y = sine;

		toWalkingState();
	}
	else
	{
		moveSpeed = 0;
		toIdleState();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		equipKnife();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		equipPistol();
	}
	move(moveDirection*moveSpeed*elapsedTime);

	if (m_rangeWeaponCooldown == 0)
		m_readyToShoot = false;
	else
	{
		m_timeSinceLastShoot += elapsedTime;
		if (m_timeSinceLastShoot >= m_rangeWeaponCooldown)
		{
			m_readyToShoot = true;
		}
	}

	return bullet;
}

void PlayableSpriteObject::update(float elapsedTime)
{
	AnimSpriteObject::update(elapsedTime);
}

int	PlayableSpriteObject::setFlashlightIdleAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_flashlightIdleAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_flashlightIdleAnimationID;
}

int	PlayableSpriteObject::setFlashlightWalkingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_flashlightWalkingAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_flashlightWalkingAnimationID;
}

int	PlayableSpriteObject::setFlashlightMeleeAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_flashlightMeleeAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	m_animatedSpriteList[m_flashlightMeleeAnimationID]->setLoop(false);
	m_animatedSpriteList[m_flashlightMeleeAnimationID]->setCanBeInterrupted(false);
	return m_flashlightMeleeAnimationID;
}

int	PlayableSpriteObject::setKnifeIdleAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_knifeIdleAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_knifeIdleAnimationID;
}

int	PlayableSpriteObject::setKnifeWalkingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_knifeWalkingAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_knifeWalkingAnimationID;
}

int	PlayableSpriteObject::setKnifeMeleeAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_knifeMeleeAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	m_animatedSpriteList[m_knifeMeleeAnimationID]->setLoop(false);
	m_animatedSpriteList[m_knifeMeleeAnimationID]->setCanBeInterrupted(false);
	return m_knifeMeleeAnimationID;
}

int PlayableSpriteObject::setPistolIdleAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_pistolIdleAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_pistolIdleAnimationID;
}

int PlayableSpriteObject::setPistolWalkingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_pistolWalkingAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_pistolWalkingAnimationID;
}

int	PlayableSpriteObject::setPistolMeleeAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_pistolMeleeAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	m_animatedSpriteList[m_pistolMeleeAnimationID]->setLoop(false);
	m_animatedSpriteList[m_pistolMeleeAnimationID]->setCanBeInterrupted(false);
	return m_pistolMeleeAnimationID;
}

int	PlayableSpriteObject::setPistolShootAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_pistolShootAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	m_animatedSpriteList[m_pistolShootAnimationID]->setLoop(false);
	m_animatedSpriteList[m_pistolShootAnimationID]->setCanBeInterrupted(false);
	return m_pistolShootAnimationID;
}

int	PlayableSpriteObject::setRifleIdleAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_rifleIdleAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_rifleIdleAnimationID;
}

int	PlayableSpriteObject::setRifleWalkingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_rifleWalkingAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_rifleWalkingAnimationID;
}

int	PlayableSpriteObject::setRifleMeleeAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_rifleMeleeAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	m_animatedSpriteList[m_rifleMeleeAnimationID]->setLoop(false);
	m_animatedSpriteList[m_rifleMeleeAnimationID]->setCanBeInterrupted(false);
	return m_rifleMeleeAnimationID;
}

int	PlayableSpriteObject::setRifleShootAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_rifleShootAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	m_animatedSpriteList[m_rifleShootAnimationID]->setLoop(false);
	m_animatedSpriteList[m_rifleShootAnimationID]->setCanBeInterrupted(false);
	return m_rifleShootAnimationID;
}

void PlayableSpriteObject::equipFlashlight()
{
	m_playerAction = IDLE;
	setCurAnim(m_flashlightIdleAnimationID);
	m_equippedWeapon = FLASHLIGHT;
}

void PlayableSpriteObject::equipKnife()
{
	m_playerAction = IDLE;
	setCurAnim(m_knifeIdleAnimationID);
	m_equippedWeapon = KNIFE;
}

void PlayableSpriteObject::equipPistol()
{
	m_playerAction = IDLE;
	setCurAnim(m_pistolIdleAnimationID);
	m_equippedWeapon = PISTOL;
	m_rangeWeaponCooldown = 1;
}

void PlayableSpriteObject::equipRifle()
{
	m_playerAction = IDLE;
	setCurAnim(m_rifleIdleAnimationID);
	m_equippedWeapon = RIFLE;
	m_rangeWeaponCooldown = 3;
}

bool PlayableSpriteObject::toIdleState()
{

	if (m_curAnimation->canBeInterrupted() || m_curAnimation->isCompleted())
	{
		switch (m_equippedWeapon)
		{
		case FLASHLIGHT:
		{
			m_playerAction = IDLE;
			setCurAnim(m_flashlightIdleAnimationID);
			break;
		}

		case KNIFE:
		{
			m_playerAction = IDLE;
			setCurAnim(m_knifeIdleAnimationID);
			break;
		}

		case PISTOL:
		{
			m_playerAction = IDLE;
			setCurAnim(m_pistolIdleAnimationID);
			break;
		}

		case RIFLE:
		{
			m_playerAction = IDLE;
			setCurAnim(m_rifleIdleAnimationID);
			break;
		}

		default:
			break;
		}

		return true;
	}

	return false;
}

bool PlayableSpriteObject::toWalkingState()
{

	if (m_curAnimation->canBeInterrupted() || m_curAnimation->isCompleted())
	{
		switch (m_equippedWeapon)
		{
		case FLASHLIGHT:
		{
			m_playerAction = WALKING;
			setCurAnim(m_flashlightWalkingAnimationID);
			break;
		}

		case KNIFE:
		{
			m_playerAction = WALKING;
			setCurAnim(m_knifeWalkingAnimationID);
			break;
		}

		case PISTOL:
		{
			m_playerAction = WALKING;
			setCurAnim(m_pistolWalkingAnimationID);
			break;
		}

		case RIFLE:
		{
			m_playerAction = WALKING;
			setCurAnim(m_rifleWalkingAnimationID);
			break;
		}

		default:
			break;
		}

		return true;
	}
	else

		return false;
}

bool PlayableSpriteObject::toMeleeState()
{
	if (m_curAnimation->canBeInterrupted() || m_curAnimation->isCompleted())
	{
		switch (m_equippedWeapon)
		{
		case FLASHLIGHT:
		{
			m_playerAction = MELEE;
			setCurAnim(m_flashlightMeleeAnimationID);
			break;
		}

		case KNIFE:
		{
			m_playerAction = MELEE;
			setCurAnim(m_knifeMeleeAnimationID);
			break;
		}

		case PISTOL:
		{
			m_playerAction = MELEE;
			setCurAnim(m_pistolMeleeAnimationID);
			break;
		}

		case RIFLE:
		{
			m_playerAction = MELEE;
			setCurAnim(m_rifleMeleeAnimationID);
			break;
		}

		default:
			break;
		}

		return true;
	}
	else
		return false;
}

bool PlayableSpriteObject::toShootState()
{

	if (m_curAnimation->canBeInterrupted() || m_curAnimation->isCompleted())
	{
		switch (m_equippedWeapon)
		{
		case FLASHLIGHT:
			return false;

		case KNIFE:
			return false;

		case PISTOL:
		{
			m_playerAction = SHOOT;
			setCurAnim(m_pistolShootAnimationID);
		}

		return true;

		case RIFLE:
		{
			m_playerAction = SHOOT;
			setCurAnim(m_rifleShootAnimationID);
		}

		return true;

		default:
			return false;
		}
	}

	else
		return false;
}

void PlayableSpriteObject::setSpeed(float speed)
{
	m_moveSpeed = speed;
}

BulletSpriteObject* PlayableSpriteObject::shoot()
{
	// Check if current weapon and state allows changing to shoot state
	if (toShootState())
	{
		BulletSpriteObject*	bullet = new BulletSpriteObject();
		bullet->applyTexture(&m_bulletTexture);
		bullet->setPosition(getPositionWorld());
		bullet->setMaxRange(3000);
		bullet->setSpeed(5000);

		const float PI = 3.14;
		float angle = getRotation() / 180 * PI;
		sf::Vector2f faceDirection = sf::Vector2f(cos(angle), sin(angle));
		bullet->setMoveDirection(faceDirection, true);

		m_timeSinceLastShoot = 0;
		m_readyToShoot = false;

		return bullet;
	}
	else
		return NULL;

}
//only 2 weapons, so a bool is enough to determine which one is currently equipped
bool PlayableSpriteObject::getCurrentWeapon() {
	switch (m_equippedWeapon) {
	case KNIFE:
		return true;

	case PISTOL:
		return false;
	}
}