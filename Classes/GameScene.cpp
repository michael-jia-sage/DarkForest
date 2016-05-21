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
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());
    
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
    // add edge
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    auto edgeNode = Node::create();
    edgeNode->setPosition( Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);
    
    
    /////////////////////////////
    // add player
    player = Sprite::create("Player.png");
    player->setScale(0.5f, 0.5f);
    player->setPosition(Vec2(visibleSize.width/2 + origin.x - 150, visibleSize.height/2 + origin.y));
    playerPhysicsBody = PhysicsBody::createCircle(player->getContentSize().width/2, PhysicsMaterial(0.0f, 1.0f, 0.0f));
    playerPhysicsBody->setGravityEnable(false);
    //playerPhysicsBody->setVelocity(Vec2(cocos2d::random(-500,500),
    //                              cocos2d::random(-500,500)));
    //playerPhysicsBody->setTag(DRAG_BODYS_TAG);
    
    player->setPhysicsBody(playerPhysicsBody);
    this->addChild(player, 0);
    
    /////////////////////////////
    // add enemy
    enemy = Sprite::create("Enemy.png");
    enemy->setScale(0.5f, 0.5f);
    enemy->setPosition(Vec2(visibleSize.width/2 + origin.x + 150, visibleSize.height/2 + origin.y));
    this->addChild(enemy, 0);
    
    // fades in the sprite in 1 seconds
    auto fadeIn = FadeIn::create(2.0f);
    auto fadeOut = FadeOut::create(2.0f);
    Sequence *pulseSequence = Sequence::create(fadeIn, fadeOut, NULL);
    RepeatForever *repeat = RepeatForever::create(pulseSequence);
    enemy->runAction(repeat);
    
    /////////////////////////////
    // add button to the right corner
    Rect attackButtonDimensions = Rect(0, 0, 64.0f, 64.0f);
    Point attackButtonPosition;
    attackButtonPosition = Vec2(visibleSize.width * 0.85f, visibleSize.height * 0.25f);
    
    SneakyButtonSkinnedBase *attackButtonBase = new SneakyButtonSkinnedBase();
    attackButtonBase->init();
    attackButtonBase->setPosition(attackButtonPosition);
    
    attackButtonBase->setDefaultSprite(Sprite::create("FireButton.png"));
    attackButtonBase->setActivatedSprite(Sprite::create("FireButtonDown.png"));
    attackButtonBase->setDisabledSprite(Sprite::create("FireButton.png"));
    attackButtonBase->setPressSprite(Sprite::create("FireButtonDown.png"));
    
    SneakyButton *aAttackButton = new SneakyButton();
    aAttackButton->initWithRect(attackButtonDimensions);
    aAttackButton->autorelease();
    
    attackButtonBase->setButton(aAttackButton);
    attackButtonBase->setPosition(attackButtonPosition);
    
    attackButton = attackButtonBase->getButton();
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
    joystickBasePosition = Vec2(visibleSize.width * 0.15f, visibleSize.height*0.3f);
    
    SneakyJoystickSkinnedBase *joystickBase = new SneakyJoystickSkinnedBase();
    joystickBase->init();
    joystickBase->setPosition(joystickBasePosition);
    joystickBase->setBackgroundSprite(Sprite::create("JoystickBase.png"));
    joystickBase->setThumbSprite(Sprite::create("JoystickButton.png"));
    
    SneakyJoystick *aJoystick = new SneakyJoystick();
    aJoystick->initWithRect(joystickBaseDimensions);
    aJoystick->autorelease();
    joystickBase->setJoystick(aJoystick);
    joystickBase->setPosition(joystickBasePosition);
    
    leftJoystick = joystickBase->getJoystick();
    leftJoystick->retain();
    this->addChild(joystickBase, 0);
    
    
    return true;
}

void GameScene::update(float dt){
    float xVec = leftJoystick->getVelocity().x;
    float yVec = leftJoystick->getVelocity().y;
    float speed = sqrtf(xVec * xVec + yVec * yVec);
    playerPhysicsBody->setVelocity( Vect( 200 * xVec * speed, 200 * yVec * speed ) );
    //log("xVec %f, yVec %f \n", xVec, yVec);
    
    if(attackButton->getValue()){
        playerPhysicsBody->applyImpulse(Vec2(0, 200));
        playerPhysicsBody->setVelocity(Vec2(0,100));
    }
}
