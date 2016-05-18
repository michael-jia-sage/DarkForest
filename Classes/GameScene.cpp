//
//  GameScene.cpp
//  DarkForest
//
//  Created by Jia, Michael on 2016-05-16.
//
//

#include "GameScene.h"
#include "SneakyButtonSkinnedBase.h"
#include "SneakyJoystickSkinnedBase.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GameScene::init()
{
    //////////////////////////////
    // super init first
    if ( !LayerColor::initWithColor(Color4B(12,27,10,46)) )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    /////////////////////////////
    // add player
    auto player = Sprite::create("Player.png");
    player->setPosition(Vec2(visibleSize.width/2 + origin.x - 150, visibleSize.height/2 + origin.y));
    this->addChild(player, 0);
    
    /////////////////////////////
    // add enemy
    auto enemy = Sprite::create("Enemy.png");
    enemy->setPosition(Vec2(visibleSize.width/2 + origin.x + 150, visibleSize.height/2 + origin.y));
    this->addChild(enemy, 0);
    
    
    /////////////////////////////
    // add button to the right corner
    Rect attackButtonDimensions = Rect(0, 0, 64.0f, 64.0f);
    Point attackButtonPosition;
    attackButtonPosition = Vec2(visibleSize.width * 0.8f, visibleSize.height * 0.2f);
    
    SneakyButtonSkinnedBase *attackButtonBase = new SneakyButtonSkinnedBase();
    attackButtonBase->init();
    attackButtonBase->setPosition(attackButtonPosition);
    
    attackButtonBase->setDefaultSprite(Sprite::create("Player.png"));
    attackButtonBase->setActivatedSprite(Sprite::create("Enemy.png"));
    attackButtonBase->setDisabledSprite(Sprite::create("Player.png"));
    attackButtonBase->setPressSprite(Sprite::create("Boss.png"));
    
    SneakyButton *aAttackButton = new SneakyButton();
    aAttackButton->initWithRect(attackButtonDimensions);
    aAttackButton->autorelease();
    
    attackButtonBase->setButton(aAttackButton);
    attackButtonBase->setPosition(attackButtonPosition);
    
    auto attackButton = attackButtonBase->getButton();
    attackButton->retain();
    this->addChild(attackButtonBase, 0);
    
    // Enable scheduler
    scheduleUpdate();
    //this->setTouchEnabled(true);
    
    
    /////////////////////////////
    // add joystick to the left corner
    Rect joystickBaseDimensions;
    joystickBaseDimensions = Rect(0, 0, 160.0f, 160.0f);
    
    Point joystickBasePosition;
    joystickBasePosition = Vec2(visibleSize.width * 0.2f, visibleSize.height*0.2f);
    
    SneakyJoystickSkinnedBase *joystickBase = new SneakyJoystickSkinnedBase();
    joystickBase->init();
    joystickBase->setPosition(joystickBasePosition);
    joystickBase->setBackgroundSprite(Sprite::create("HelloWorld.png"));
    joystickBase->setThumbSprite(Sprite::create("Boss.png"));
    
    SneakyJoystick *aJoystick = new SneakyJoystick();
    aJoystick->initWithRect(joystickBaseDimensions);
    aJoystick->autorelease();
    joystickBase->setJoystick(aJoystick);
    joystickBase->setPosition(joystickBasePosition);
    
    auto leftJoystick = joystickBase->getJoystick();
    leftJoystick->retain();
    this->addChild(joystickBase, 0);
    
    
    return true;
}
