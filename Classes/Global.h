#ifndef Global_h
#define Global_h

#include "cocos2d.h"
class Global
{
private:
    Global();
    ~Global();
    
public:
    static Global* getInstance();
    static float calDistance(cocos2d::Vec2 p1, cocos2d::Vec2 p2);
    
    //images
    const std::string PlayerImage = "Player.png";
    const std::string EnemyImage = "Enemy.png";
    const std::string BossImage = "Boss.png";
    const std::string DotCircleImage = "dotCircle.png";
    const std::string Light1Image = "light1.png";
    const std::string Light2Image = "light2.png";
    const std::string FireButtonImage = "FireButton.png";
    const std::string FireButtonDownImage = "FireButtonDown.png";
    const std::string JoystickBaseImage = "JoystickBase.png";
    const std::string JoystickButtonImage = "JoystickButton.png";
    const std::string WhiteTextureImage = "whiteTexture.png";
    //const std::string Image = ".png";
    
    //settings
    const int MovingVecBase = 200;
    const int PlayerSpeedRate = 50;
    const int BulletAngleMin = -25;
    const int BulletAngleMax = 25;
    const int BulletSpeedRate = 150;
    
    //enemy strategy
    CC_SYNTHESIZE(cocos2d::Vec2, moveTarget, MoveTarget);
    CC_SYNTHESIZE(cocos2d::Vec2, moveVec, MoveVec);
    CC_SYNTHESIZE(cocos2d::Vec2, fireTarget, FireTarget);
    
    //game controls
    CC_SYNTHESIZE(bool, canFire, CanFire);
    
    //scores
    CC_SYNTHESIZE(int, scoreValue, ScoreValue);
};

#endif /* Global_h */
