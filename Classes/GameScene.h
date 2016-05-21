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

class GameScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
    SneakyJoystick *leftJoystick;
    SneakyButton *attackButton;
    Sprite *player, *enemy;
    PhysicsBody *playerPhysicsBody;
    
    virtual bool init();
    void update(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
private:
    cocos2d::PhysicsWorld *sceneWorld;
    void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };
};


#endif /* GameScene_h */
