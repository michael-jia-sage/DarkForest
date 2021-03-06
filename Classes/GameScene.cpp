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
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) ) //Color4B(12,27,10,46)
    {
        return false;
    }
    
    /////////////////////////////
    // add edge
    //auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
//    auto edgeNode = Node::create();
//    edgeNode->setPosition( Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    //edgeNode->setPhysicsBody(edgeBody);
//    this->addChild(edgeNode);
    
    /////////////////////////////
    // add enemy
    enemy = Sprite::create(_gm->EnemyImage);
    enemy->setScale(0.5f, 0.5f);
    enemy->setPosition(Vec2(visibleSize.width/2 + origin.x + 150, visibleSize.height/2 + origin.y));
    enemyPhysicsBody = PhysicsBody::createCircle(enemy->getContentSize().width/2, PhysicsMaterial(0.0f, 1.0f, 0.0f));
    enemyPhysicsBody->setGravityEnable(false);
    enemyPhysicsBody->setCollisionBitmask(3);
    //enemyPhysicsBody->setContactTestBitmask(true);
    enemy->setPhysicsBody(enemyPhysicsBody);
    this->addChild(enemy, 90);
//    auto fadeOut = FadeOut::create(1.0f);
//    enemy->runAction(fadeOut);
    //add listner
    auto _listener = EventListenerCustom::create("player_fired", [=](EventCustom* event){
        log("Event triggered: %s", event->getEventName().c_str());
    });
    enemy->getEventDispatcher()->addEventListenerWithFixedPriority(_listener, 30);
    
    boss = Sprite::create(_gm->BossImage);
    boss->setScale(0.5f, 0.5f);
    boss->setPosition(Vec2(visibleSize.width/2 + origin.x + 200, visibleSize.height/2 + origin.y));
    this->addChild(boss, 95);
    
    /////////////////////////////
    // add window layer
    windowLayer = Sprite::create(_gm->WindowImage);
    windowLayer->setScale(2.0f, 2.0f);
    windowLayer->setPosition(Vec2(0, visibleSize.height));
    windowPosition = Vec2(windowLayer->getPosition().x - Global::WindowRadius, windowLayer->getPosition().y - Global::WindowRadius);
    this->addChild(windowLayer, 100);
    
    // add button to the right corner
    this->AddButton();
    
    // add joystick to the left corner
    this->AddJoystick();

    // Enable scheduler
    scheduleUpdate();
    
    /////////////////////////////
    // add player
    player = Sprite::create(_gm->PlayerImage);
    player->setScale(0.5f, 0.5f);
    player->setPosition(Vec2(visibleSize.width/2 + origin.x - 150, visibleSize.height/2 + origin.y));
    playerPhysicsBody = PhysicsBody::createCircle(player->getContentSize().width/2, PhysicsMaterial(0.0f, 1.0f, 0.0f));
    playerPhysicsBody->setGravityEnable(false);
    playerPhysicsBody->setCollisionBitmask(2);
    playerPhysicsBody->setContactTestBitmask(true);
    //playerPhysicsBody->setVelocity(Vec2(cocos2d::random(-500,500),
    //                              cocos2d::random(-500,500)));
    //playerPhysicsBody->setTag(DRAG_BODYS_TAG);
    
    player->setPhysicsBody(playerPhysicsBody);
    this->addChild(player, 105);
    
    /////////////////////////////
    // touch anywhere to fire a light ball
    this->Fire();
    
    //contact listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    /////////////////////////////
    // add information bar
    AddInformationBar();

    test();

    return true;
}

void GameScene::update(float dt){
    if (!_gm->getEnemyMoving()) {
        randomizeEnemyMovingInfo();
        movingEnemy();
        // fades in and out the sprite in 1 seconds
        auto fadeIn = FadeIn::create(0.5f);
        auto fadeOut = FadeOut::create(0.5f);
        Sequence *fadeSequence = Sequence::create(fadeIn, fadeOut, NULL);
        enemy->runAction(fadeSequence);
    }
    
    auto playerPos = player->getPosition();
    float xVec = leftJoystick->getVelocity().x;
    if ((playerPos.x <= player->getBoundingBox().size.width && xVec < 0) || (playerPos.x >= visibleSize.width - 10 && xVec > 0))
        xVec = 0;
    float yVec = leftJoystick->getVelocity().y;
    if ((playerPos.y <= player->getBoundingBox().size.height && yVec < 0) || (playerPos.y >= visibleSize.height && yVec > 0))
        yVec = 0;
    float speed = sqrtf(xVec * xVec + yVec * yVec);
    playerPhysicsBody->setVelocity( Vect( _gm->MovingVecBase * xVec * speed, _gm->MovingVecBase * yVec * speed ) );
    if (xVec != 0 && yVec != 0)
        log("xVec %f, yVec %f, x %f, y %f \n", xVec, yVec, playerPos.x, playerPos.y);
    
    if(attackButton->getValue()){
        player->setPosition(Vec2(visibleSize.width/2 + origin.x - 150, visibleSize.height/2 + origin.y));
        
        test();
        //playerPhysicsBody->applyImpulse(Vec2(0, 200));
        //playerPhysicsBody->setVelocity(Vec2(0,100));
    }
    
    // Update distance
    distance = Global::calDistance(enemy->getPosition(), player->getPosition());
    lblDistance->setString(__String::createWithFormat("%d", distance)->getCString());
    
    // Update disclosure
//    disclosure = Global::calDisclosure(enemy->getPosition(), _gm->PlayerRadius, windowPosition, Global::WindowRadius, Global::CloudRadius);
//    lblDisclosure->setString(__String::createWithFormat("%d", disclosure)->getCString());
}

void GameScene::AddButton() {
    Rect attackButtonDimensions = Rect(0, 0, 64.0f, 64.0f);
    Point attackButtonPosition;
    attackButtonPosition = Vec2(visibleSize.width * 0.85f, visibleSize.height * 0.25f);
    
    SneakyButtonSkinnedBase *attackButtonBase = new SneakyButtonSkinnedBase();
    attackButtonBase->init();
    attackButtonBase->setPosition(attackButtonPosition);
    
    attackButtonBase->setDefaultSprite(Sprite::create(_gm->FireButtonImage));
    attackButtonBase->setActivatedSprite(Sprite::create(_gm->FireButtonDownImage));
    attackButtonBase->setDisabledSprite(Sprite::create(_gm->FireButtonImage));
    attackButtonBase->setPressSprite(Sprite::create(_gm->FireButtonDownImage));
    
    SneakyButton *aAttackButton = new SneakyButton();
    aAttackButton->initWithRect(attackButtonDimensions);
    aAttackButton->autorelease();
    
    attackButtonBase->setButton(aAttackButton);
    attackButtonBase->setPosition(attackButtonPosition);
    
    attackButton = attackButtonBase->getButton();
    attackButton->retain();
    this->addChild(attackButtonBase, 101);
}

void GameScene::AddJoystick() {
    Rect joystickBaseDimensions;
    joystickBaseDimensions = Rect(0, 0, 160.0f, 160.0f);
    
    Point joystickBasePosition;
    joystickBasePosition = Vec2(visibleSize.width * 0.15f, visibleSize.height*0.3f);
    
    SneakyJoystickSkinnedBase *joystickBase = new SneakyJoystickSkinnedBase();
    joystickBase->init();
    joystickBase->setPosition(joystickBasePosition);
    joystickBase->setBackgroundSprite(Sprite::create(_gm->JoystickBaseImage));
    joystickBase->setThumbSprite(Sprite::create(_gm->JoystickButtonImage));
    
    SneakyJoystick *aJoystick = new SneakyJoystick();
    aJoystick->initWithRect(joystickBaseDimensions);
    aJoystick->autorelease();
    joystickBase->setJoystick(aJoystick);
    joystickBase->setPosition(joystickBasePosition);
    
    leftJoystick = joystickBase->getJoystick();
    leftJoystick->retain();
    this->addChild(joystickBase, 102);
}

void GameScene::Fire() {
    //Create a "one by one" touch event listener (processes one touch at a time)
    auto touchListener = EventListenerTouchOneByOne::create();
    // When "swallow touches" is true, then returning 'true' from the onTouchBegan method will "swallow" the touch event, preventing other listeners from using it.
    touchListener->setSwallowTouches(true);
    
    // Example of using a lambda expression to implement onTouchBegan event callback function
    touchListener->onTouchBegan = [=](Touch* touch, Event* event){
        log("touch began... x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
        dotCircle = Sprite::create(_gm->DotCircleImage);
        dotCircle->setScale(3, 3);
        dotCircle->setPosition(touch->getLocation());
        this->addChild(dotCircle, 0);

        return true;
    };

    //Trigger when moving touch
    touchListener->onTouchMoved = [=](Touch* touch, Event* event){
        log("touch moved... x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
        dotCircle->setPosition(touch->getLocation());
    };
    
    //Process the touch end event
    touchListener->onTouchEnded = [=](Touch* touch, Event* event){
        log("touch end... x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
        dotCircle->removeFromParentAndCleanup(true);
        
        if (!_gm->getCanFire())
            return false;
        
        //Trigger event
        char* buf = new char[10];
        sprintf(buf, "%s", "test");
        auto event1 = EventCustom("player_fired");
        event1.setUserData(buf);
        _eventDispatcher->dispatchEvent(&event1);
        CC_SAFE_DELETE_ARRAY(buf);
        
        //Create bullet sprite
        auto bullet = Sprite::create(_gm->Light1Image);
        bullet->setScale(2.0f, 2.0f);
        auto playerPos = player->getPosition();
        auto touchPos = touch->getLocation();
        bullet->setPosition(playerPos);
        playerBulletPhysicsBody = PhysicsBody::createCircle(bullet->getContentSize().width/2, PhysicsMaterial(0.0f, 1.0f, 0.0f));
        playerBulletPhysicsBody->setGravityEnable(false);
        playerBulletPhysicsBody->setCollisionBitmask(4);
        playerBulletPhysicsBody->setContactTestBitmask(true);
        bullet->setPhysicsBody(playerBulletPhysicsBody);
        this->addChild(bullet, 106);
        
        //Calculate speed
        auto distance = Global::calDistance(touchPos, playerPos);
        auto duration = distance / _gm->BulletSpeedRate;
        
        //Move from player to target
        auto jumpTo = JumpTo::create(duration, touchPos, cocos2d::RandomHelper::random_int(_gm->BulletAngleMin, _gm->BulletAngleMax), 1);
        Sequence *bulletFlySequence = Sequence::create(jumpTo, CallFuncN::create(std::bind(&GameScene::onBulletArrived, this, bullet, true)), NULL);
        bullet->runAction(bulletFlySequence);
        
        //Tail effect
        auto motionstreak = MotionStreak::create(1.0f, 1.0f, 10.0f, Color3B(255, 255, 255), _gm->WhiteTextureImage);
        motionstreak->setPosition(playerPos);
        this->addChild(motionstreak, 107);
        auto tailJumpTo = jumpTo->clone();
        //tailJumpTo->setDuration(2.0f);
        Sequence *tailFlySequence = Sequence::create(tailJumpTo, CallFuncN::create(std::bind(&GameScene::onMotionStreakArrived, this, motionstreak)), NULL);
        motionstreak->runAction(tailFlySequence);
        
        //check if any damage
//        enemyHealth -= Global::calDamage(enemy->getPosition(), Global::EnemyRadius, touchPos);
//        lblEnemyHealth->setString(__String::createWithFormat("%d%%", enemyHealth)->getCString());
        
        _gm->setCanFire(false);
    };
    
    //Add listener
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

}

bool GameScene::onContactBegin (cocos2d::PhysicsContact &contact) {
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    log("a is %d, b is %d", a->getCollisionBitmask(), b->getCollisionBitmask());
    if ( (3 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask()) || (4 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask())) {
        log("Bingo!");
    }
    
    return true;
}

void GameScene::onBulletArrived(Sprite *item, bool resetCanFire) {
    //explode
    auto scaleTo = ScaleTo::create(1.0f, item->getScale() * 3.0f);
    auto fadeOut = FadeOut::create(1.0f);
    item->runAction(Sequence::create(CallFuncN::create(std::bind(&GameScene::movingWindow, this, item->getPosition())),
                                     scaleTo, fadeOut, CallFuncN::create(std::bind(&GameScene::removeSprite, this, item)),
                                      NULL));
    int damage = Global::calDamage(item->getPosition(), enemy->getPosition(), Global::BossRadius);
    if (damage < enemyHealth) {
        enemyHealth -= damage;
    } else {
        enemyHealth = 0;
        //Game winning
    }
    lblEnemyHealth->setString(__String::createWithFormat("%d%%", enemyHealth)->getCString());
    
    if (resetCanFire)
        _gm->setCanFire(true);
}

void GameScene::onMotionStreakArrived(MotionStreak *item) {
    item->removeFromParentAndCleanup(true);
}

void GameScene::removeSprite(Sprite *sprite) {
    sprite->removeFromParentAndCleanup(true);
}

void GameScene::movingEnemy() {
    log("Enemy is moving to: %f %f at %f", _gm->getMoveTarget().x, _gm->getMoveTarget().y, enemyMovingDuration);
    enemy->runAction(Sequence::create(CallFuncN::create(std::bind(&Global::setEnemyMoving, _gm, true)),
                                      MoveTo::create(enemyMovingDuration, _gm->getMoveTarget()),
                                      CallFuncN::create(std::bind(&Global::setEnemyMoving, _gm, false)), NULL));
}

void GameScene::randomizeEnemyMovingInfo() {
    enemyMovingSpeed = arc4random() % 50 + 50;  //moving speed from 50 ~ 100
    enemyMoveToX = arc4random() % 100;
    enemyMoveToY = arc4random() % 100;
    _gm->setMoveTarget(Vec2(enemyMoveToX * visibleSize.width / 100, enemyMoveToY * visibleSize.height / 100));
    enemyMovingDuration = Global::calDistance(_gm->getMoveTarget(), enemy->getPosition()) / (_gm->PlayerSpeedRate * enemyMovingSpeed / 100);
    log("Enemy should move to: %f %f at %f", _gm->getMoveTarget().x, _gm->getMoveTarget().y, enemyMovingDuration);
}

void GameScene::movingWindow(Vec2 pos) {
    windowLayer->setPosition(pos.x + Global::WindowRadius, pos.y - Global::WindowRadius);
    windowPosition = Vec2(windowLayer->getPosition().x - Global::WindowRadius, windowLayer->getPosition().y - Global::WindowRadius);
}

void GameScene::AddInformationBar() {
    Label *lblTitle = Label::createWithTTF("Health: ", _gm->Font, _gm->FontSize);
    lblTitle->setPosition(Vec2(10 + lblTitle->getContentSize().width / 2, visibleSize.height - lblTitle->getContentSize().height / 2));
    this->addChild(lblTitle, 999);
    lblPlayerHealth = Label::createWithTTF(__String::createWithFormat("%d%%", playerHealth)->getCString(), _gm->Font, _gm->FontSize);
    lblPlayerHealth->setPosition(Vec2(10 + lblTitle->getPosition().x + lblTitle->getContentSize().width, lblTitle->getPosition().y));
    this->addChild(lblPlayerHealth, 999);
    
    lblTitle = Label::createWithTTF("Disclosure: ", _gm->Font, _gm->FontSize);
    lblTitle->setPosition(Vec2(10 + lblTitle->getContentSize().width / 2, lblPlayerHealth->getPosition().y - lblTitle->getContentSize().height));
    this->addChild(lblTitle, 999);
    lblDisclosure = Label::createWithTTF(__String::createWithFormat("%d%%", disclosure)->getCString(), _gm->Font, _gm->FontSize);
    lblDisclosure->setPosition(Vec2(10 + lblTitle->getPosition().x + lblTitle->getContentSize().width, lblTitle->getPosition().y));
    this->addChild(lblDisclosure, 999);
    
    lblTitle = Label::createWithTTF("Distance: ", _gm->Font, _gm->FontSize);
    lblTitle->setPosition(Vec2(10 + lblTitle->getContentSize().width / 2, lblDisclosure->getPosition().y - lblTitle->getContentSize().height));
    this->addChild(lblTitle, 999);
    lblDistance = Label::createWithTTF(__String::createWithFormat("%d", distance)->getCString(), _gm->Font, _gm->FontSize);
    lblDistance->setPosition(Vec2(10 + lblTitle->getPosition().x + lblTitle->getContentSize().width, lblTitle->getPosition().y));
    this->addChild(lblDistance, 999);
    
    lblTitle = Label::createWithTTF("Enemy: ", _gm->Font, _gm->FontSize);
    lblTitle->setPosition(Vec2(visibleSize.width - 10 - lblTitle->getContentSize().width / 2 - lblPlayerHealth->getContentSize().width, lblPlayerHealth->getPosition().y - lblTitle->getContentSize().height));
    this->addChild(lblTitle, 999);
    lblEnemyHealth = Label::createWithTTF(__String::createWithFormat("%d%%", enemyHealth)->getCString(), _gm->Font, _gm->FontSize);
    lblEnemyHealth->setPosition(Vec2(10 + lblTitle->getPosition().x + lblTitle->getContentSize().width, lblTitle->getPosition().y));
    this->addChild(lblEnemyHealth, 999);
    
}

void GameScene::test() {
    //test information bar
    
    disclosure = Global::calDisclosure(enemy->getPosition(), _gm->PlayerRadius, windowPosition, Global::WindowRadius, Global::CloudRadius);
    lblDisclosure->setString(__String::createWithFormat("%d", disclosure)->getCString());

}