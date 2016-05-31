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
    Sprite *windowLayer, *player, *enemy, *boss, *bullet, *dotCircle;
    Label *lblPlayerHealth, *lblDisclosure, *lblDistance, *lblEnemyHealth;
    PhysicsBody *playerPhysicsBody, *enemyPhysicsBody, *playerBulletPhysicsBody, *enemyBulletPhysicsBody;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 windowPosition;
    int enemyMovingSpeed, enemyMoveToX, enemyMoveToY;
    int playerHealth = 100, disclosure = 0, distance = 0, enemyHealth = 100;
    int playerDisclosure = 0;
    float enemyMovingDuration;
    
    void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };
    void Fire();
    void AddButton();
    void AddJoystick();
    void AddInformationBar();
    
    void removeSprite(Sprite *sprite);
    bool onContactBegin (cocos2d::PhysicsContact &contact);
    void onBulletArrived(Sprite *item, bool resetCanFire=false);
    void onMotionStreakArrived(MotionStreak *item);
    void movingEnemy();
    void randomizeEnemyMovingInfo();
    void movingWindow(Vec2 pos);
    
    void test();
};


#endif /* GameScene_h */
