#include "GameWorld.h"
GameWorld::GameWorld(int windowWidth, int windowHeight, sf::RenderWindow* parentWindow)
	: wWidth(windowWidth)
	, wHeight(windowHeight)
	, m_camera(wWidth, wHeight)
{
	GameWorldLayer* background = new GameWorldLayer( "media/textures/ground.jpg", 1.0f, wWidth, wHeight);
	GameWorldLayer* wire = new GameWorldLayer("media/textures/wire.png", 0.5f, wWidth, wHeight);
	GameWorldLayer* foreground = new GameWorldLayer( "media/textures/fog.png", 0.3f, wWidth, wHeight);

	m_gameWorldLayerList.push_back(background);
	m_gameWorldLayerList.push_back(wire);
	m_gameWorldLayerList.push_back(foreground);
	m_camPos = sf::Vector2f(0, 0);
	
	//sprite
	
	m_spriteObject2.setDefTexture("media/textures/flashoverlay.png");
	m_hBar.setDefTexture("media/textures/health.png");
	m_icon.setDefTexture("media/textures/icon.png");
	m_weaponGun.setDefTexture("media/textures/gunicon.png");
	m_weaponKnife.setDefTexture("media/textures/knifeicon.png");
	m_spriteObject2.setPosition(4, 0);
	m_hBar.setPosition(0, 0);
	
	
	m_numOfEnemies = 3;
	for (int i = 0; i < m_numOfEnemies; i++) {
		NPCSpriteObject* npcSprite = new NPCSpriteObject();
		npcSprite->setIdleAnimation("media/textures/enemyidle.png", "media/textures/generic.txt", 1.0f);
		npcSprite->setWalkingAnimation("media/textures/enemywalk.png", "media/textures/generic.txt", 1.0f);
		npcSprite->setAttackingAnimation("media/textures/enemywalk.png", "media/textures/generic.txt", 1.0f);
		npcSprite->setPosition(rand() % 4000 - 2000, rand() % 4000 - 2000);
		npcSprite->setTargetLocation(sf::Vector2f(rand() % 4000 - 2000, rand() % 4000 - 2000));
		npcSprite->setScale(10, 10);
		m_enemyCharList.push_back(npcSprite);
	}
	
	m_playerCharacter = new PlayableSpriteObject();
	m_playerCharacter->setScale(10, 10);
	m_playerCharacter->setKnifeIdleAnimation("media/textures/idleknife.png", "media/textures/generic.txt", 1.0f);
	m_playerCharacter->setKnifeWalkingAnimation("media/textures/walkknife.png", "media/textures/generic.txt", 1.0f);
	m_playerCharacter->setKnifeMeleeAnimation("media/textures/attackknife.png", "media/textures/generic.txt", 1.0f);
	m_playerCharacter->setPistolIdleAnimation("media/textures/idlegun.png", "media/textures/generic.txt", 1.0f);
	m_playerCharacter->setPistolWalkingAnimation("media/textures/walkgun.png", "media/textures/generic.txt", 1.0f);
	m_playerCharacter->setPistolMeleeAnimation("media/textures/attackgun.png", "media/textures/generic.txt", 1.0f);

	m_playerCharacter->equipKnife();
	m_playerCharacter->toIdleState();
	m_parentWindow = parentWindow;
	m_playerCharacter->setPosition(0, 0);
	m_playerHP = 100;
	m_hBar.setScale(m_playerHP, 1);
	m_icon.setScale(0.35, 0.35);
}
GameWorld::~GameWorld() {
	for (std::vector<GameWorldLayer*>::iterator it = m_gameWorldLayerList.begin();
		it != m_gameWorldLayerList.end(); it++)
	{
		delete (*it);
	}
	m_gameWorldLayerList.clear();
	
}
void GameWorld::processEvents(float elapsedTime) {
	float camPanSpeed = 200.0f;
	sf::Transform transform;

	transform = m_camera.getProjTransform() * m_camera.getViewTransform();
	sf::Transform inv = transform.getInverse();

	sf::Vector2f mouseScreenPosition = sf::Vector2f(sf::Mouse::getPosition(*m_parentWindow));
	sf::Vector2f wp = inv.transformPoint(mouseScreenPosition);
	
	/*
							   if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_camPos.x = m_camPos.x - camPanSpeed * elapsedTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_camPos.x = m_camPos.x + camPanSpeed * elapsedTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_camPos.y = m_camPos.y - camPanSpeed * elapsedTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_camPos.y = m_camPos.y + camPanSpeed * elapsedTime;
	}
	
	}
							   
							   */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		m_camera.zoomUp();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		m_camera.zoomDown();
	}

	
	m_spriteObject2.setPosition(m_playerCharacter->getPosition());
	m_spriteObject2.setRotation(m_playerCharacter->getRotation());
	BulletSpriteObject* bullet = m_playerCharacter->processEvents(elapsedTime, transform, mouseScreenPosition);
	if (bullet) m_bulletList.push_back(bullet);
}
void GameWorld::update(float elapsedTime) {
	processEvents(elapsedTime);
	m_playerCharacter->setColor(sf::Color(255, 255, 255));
	m_spriteObject2.update(elapsedTime);
	m_hBar.update(elapsedTime);
	m_icon.update(elapsedTime);
	m_weaponGun.update(elapsedTime);
	m_weaponKnife.update(elapsedTime);
	//m_camera.setPosition(m_camPos);
	for (int count = 0; count < m_gameWorldLayerList.size(); count++) {
		m_gameWorldLayerList[count]->followCam(&m_camera);
	}

	for (unsigned int count = 0; count < m_enemyCharList.size(); count++) {

		m_enemyCharList[count]->update(elapsedTime, m_playerCharacter->getPosition());
		if (m_enemyCharList[count]->inInVision(m_playerCharacter->getPosition())) {
			m_enemyCharList[count]->setColor(sf::Color(255,100,100));
			
		}
		else {
			m_enemyCharList[count]->setColor(sf::Color(255, 255, 255));
		}
		boundingBoxEnemy = m_enemyCharList[count]->getGlobalBounds();
		if (boundingBoxEnemy.intersects(boundingBoxPlayer)) {
			m_playerHP--;
			m_playerCharacter->setColor(sf::Color(255, 0, 0));
		}
		 
	}

	m_playerCharacter->update(elapsedTime);
	m_camera.setPosition(m_playerCharacter->getPositionWorld());

	for (unsigned int count = 0; count < m_bulletList.size(); count++) {
		m_bulletList[count]->update(elapsedTime);
		boundingBoxBullet = m_bulletList[count]->getGlobalBounds();
		for (unsigned int enemyCount = 0; enemyCount < m_enemyCharList.size(); enemyCount++) {
			boundingBoxEnemy = m_enemyCharList[enemyCount]->getGlobalBounds();
			if (boundingBoxBullet.intersects(boundingBoxEnemy)) {
				m_enemyCharList[enemyCount]->setColor(sf::Color(255, 0, 0, 255));
				m_bulletList[count]->setColor(sf::Color(0, 0, 0, 0));
			}

		}
	}
	boundingBoxPlayer = m_playerCharacter->getGlobalBounds();
	m_hBar.setPosition(m_playerCharacter->getPositionWorld().x - 700, m_playerCharacter->getPositionWorld().y - 450);
	m_icon.setPosition(m_playerCharacter->getPositionWorld().x + 700, m_playerCharacter->getPositionWorld().y - 400);
	m_weaponGun.setPosition(m_playerCharacter->getPositionWorld().x, m_playerCharacter->getPositionWorld().y - 400);
	m_weaponKnife.setPosition(m_playerCharacter->getPositionWorld().x, m_playerCharacter->getPositionWorld().y - 400);
	m_hBar.setScale(m_playerHP / 2, 0.5f);
	
}
void GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	

	//for (int count = 0; count < m_gameWorldLayerList.size(); count++) {
	//	target.draw(*m_gameWorldLayerList[count], states);
	//}
	target.draw(*m_gameWorldLayerList[0], states);
	sf::RenderStates renderState;
	renderState.transform = m_camera.getProjTransform() * m_camera.getViewTransform();
	for (unsigned int count = 0; count < m_enemyCharList.size(); count++) {
		target.draw(*m_enemyCharList[count], renderState);
	}
	target.draw(*m_playerCharacter, renderState);
	for (unsigned int count = 0; count < m_bulletList.size(); count++) {
		target.draw(*m_bulletList[count], renderState);
	}
	target.draw(*m_gameWorldLayerList[1], states);
	target.draw(*m_gameWorldLayerList[2], states);
	target.draw(m_spriteObject2, renderState);
	target.draw(m_hBar, renderState);
	target.draw(m_icon, renderState);
	if(m_playerCharacter->getCurrentWeapon()) target.draw(m_weaponKnife, renderState);
	else target.draw(m_weaponGun, renderState);
}
void GameWorld::Reset() {
	m_playerCharacter->setPosition(0, 0);
	m_playerHP = 100;
	for (unsigned int enemyCount = 0; enemyCount < m_enemyCharList.size(); enemyCount++) {
		m_enemyCharList[enemyCount]->setPosition(rand() % 4000 - 2000, rand() % 4000 - 2000);
		m_enemyCharList[enemyCount]->setTargetLocation(sf::Vector2f(rand() % 4000 - 2000, rand() % 4000 - 2000));
	}
}