//
//  SneakyJoystickSkinnedBase.h
//  DarkForest
//
//  Created by Jia, Michael on 2016-05-17.
//
//

#ifndef SneakyJoystickSkinnedBase_h
#define SneakyJoystickSkinnedBase_h
#include "cocos2d.h"
#include "SneakyJoystick.h"

class SneakyJoystickSkinnedBase : public cocos2d::Layer
{
public:
    CC_SYNTHESIZE_READONLY(cocos2d::Sprite *, backgroundSprite, BackgroundSprite);
    CC_SYNTHESIZE_READONLY(cocos2d::Sprite *, thumbSprite, ThumbSprite);
    CC_SYNTHESIZE_READONLY(SneakyJoystick *, joystick, Joystick);
    
    //Public methods
    CREATE_FUNC(SneakyJoystickSkinnedBase);
    virtual ~SneakyJoystickSkinnedBase();
    bool init();
    void updatePositions(float delta);
    void setContentSize(cocos2d::Size s);
    void setBackgroundSprite(cocos2d::Sprite *aSprite);
    void setThumbSprite(cocos2d::Sprite *aSprite);
    void setJoystick(SneakyJoystick *aJoystick);
};
#endif /* SneakyJoystickSkinnedBase_h */
