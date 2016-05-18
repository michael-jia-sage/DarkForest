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

class GameScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};


#endif /* GameScene_h */
