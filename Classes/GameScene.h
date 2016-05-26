//
//  GameScene.h
//  DarkForest
//
//  Created by Jia, Michael on 2016-05-16.
//
//

#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"
#include "SneakyJoystick.h"
#include "SneakyButton.h"
#include "Global.h"

class GameScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    void update(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
private:
    Global *_gm = Global::getInstance();
    cocos2d::PhysicsWorld *sceneWorld;
    SneakyJoystick *leftJoystick;
    SneakyButton *attackButton;
    Sprite *player, *enemy, *bullet, *dotCircle;
    PhysicsBody *playerPhysicsBody, *enemyPhysicsBody, *playerBulletPhysicsBody, *enemyBulletPhysicsBody;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    int enemyMovingSpeed, enemyMoveToX, enemyMoveToY;
    float enemyMovingDuration;
    
    void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };
    void Fire();
    void AddButton();
    void AddJoystick();
    
    void removeSprite(Sprite *sprite);
    bool onContactBegin (cocos2d::PhysicsContact &contact);
    void onBulletArrived(Sprite *item, bool resetCanFire=false);
    void onMotionStreakArrived(MotionStreak *item);
    void movingEnemy();
    void randomizeEnemyMovingInfo();
};


#endif /* GameScene_h */
