#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameWorldLayer.h"
#include "SpriteObject.h"
#include "AnimSpriteObject.h"
#include "NPCSpriteObject.h"
#include "PlayableSpriteObject.h"
#include "BulletSpriteObject.h"
class GameWorld :
    public sf::Drawable
{
public:
    GameWorld(int windowWidth, int windowHeight, sf::RenderWindow* parentWindow);
    ~GameWorld();
    void update(float elapsedTime);
    void processEvents(float elapsedTime);
    void Reset();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    int wHeight;
    int wWidth;
    std::vector<GameWorldLayer*> m_gameWorldLayerList;
    Camera m_camera;
    sf::Vector2f m_camPos;
    
    SpriteObject m_spriteObject2;
    SpriteObject m_hBar;
    SpriteObject m_icon;
    SpriteObject m_weaponKnife;
    SpriteObject m_weaponGun;
    sf::FloatRect boundingBoxEnemy;
    sf::FloatRect boundingBoxPlayer;
    sf::FloatRect boundingBoxBullet;
    float m_playerHP;
    std::vector<NPCSpriteObject*> m_enemyCharList;
    int m_numOfEnemies;
    PlayableSpriteObject* m_playerCharacter;
    std::vector<BulletSpriteObject*> m_bulletList;
    sf::RenderWindow* m_parentWindow;
};

