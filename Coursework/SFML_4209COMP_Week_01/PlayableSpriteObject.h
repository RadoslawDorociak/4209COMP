#pragma once
#include "AnimSpriteObject.h"
#include "BulletSpriteObject.h"

class PlayableSpriteObject :
	public AnimSpriteObject
{
public:
	PlayableSpriteObject();
	virtual ~PlayableSpriteObject();

	virtual void update(float elapsedTime);
	BulletSpriteObject* processEvents(float elapsedTime, sf::Transform transform, sf::Vector2f mouseScreenPosition);

	int		setFlashlightIdleAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);
	int		setFlashlightWalkingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);
	int		setFlashlightMeleeAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);

	int		setKnifeIdleAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);
	int		setKnifeWalkingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);
	int		setKnifeMeleeAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);

	int		setPistolIdleAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);
	int		setPistolWalkingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);
	int		setPistolMeleeAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);
	int		setPistolShootAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);

	int		setRifleIdleAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);
	int		setRifleWalkingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);
	int		setRifleMeleeAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);
	int		setRifleShootAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);

	bool	toIdleState();
	bool	toWalkingState();
	bool	toMeleeState();
	bool	toShootState();

	void	equipFlashlight();
	void	equipKnife();
	void	equipPistol();
	void	equipRifle();

	void	setSpeed(float speed);

	bool getCurrentWeapon();
private:

	float			m_moveSpeed;
	sf::Vector2f	m_faceDirection;
	sf::Texture		m_bulletTexture;
	bool shot;

	enum PlayerAction {
		IDLE,
		WALKING,
		MELEE,
		SHOOT
	};

	enum EquippedWeapon {
		FLASHLIGHT,
		KNIFE,
		PISTOL,
		RIFLE
	};

	PlayerAction	m_playerAction;
	EquippedWeapon	m_equippedWeapon;

	int				m_flashlightIdleAnimationID;
	int				m_flashlightWalkingAnimationID;
	int				m_flashlightMeleeAnimationID;

	int				m_knifeIdleAnimationID;
	int				m_knifeWalkingAnimationID;
	int				m_knifeMeleeAnimationID;

	int				m_pistolIdleAnimationID;
	int				m_pistolWalkingAnimationID;
	int				m_pistolMeleeAnimationID;
	int				m_pistolShootAnimationID;

	int				m_rifleIdleAnimationID;
	int				m_rifleWalkingAnimationID;
	int				m_rifleMeleeAnimationID;
	int				m_rifleShootAnimationID;

	bool			m_readyToShoot;
	float			m_rangeWeaponCooldown;
	float			m_timeSinceLastShoot;

	BulletSpriteObject* shoot();

};

