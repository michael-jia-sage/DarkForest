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
    static int calDisclosure(cocos2d::Vec2 item_pos, int item_radius, cocos2d::Vec2 window_pos, int window_radius, int cloud_radius);
    
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
    const std::string WindowImage = "hole.png";
    const int WindowRadius = 25;
    const int CloudRadius = 50;
    const int PlayerRadius = 25;
    const int EnemyRadius = 25;
    //const std::string Image = ".png";
    
    //font and sizes
    const std::string Font = "fonts/Marker Felt.ttf";
    const int FontSize = 10;
    
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
    CC_SYNTHESIZE(bool, enemyMoving, EnemyMoving);
    CC_SYNTHESIZE(bool, canFire, CanFire);
    
    //scores
    CC_SYNTHESIZE(int, scoreValue, ScoreValue);
};

#endif /* Global_h */
