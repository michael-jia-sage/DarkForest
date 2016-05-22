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
    const int BulletAngleMin = -25;
    const int BulletAngleMax = 25;
    const int SpeedRate = 100;
    
    //game controls
    CC_SYNTHESIZE(bool, canFire, CanFire);
    
    //scores
    CC_SYNTHESIZE(int, scoreValue, ScoreValue);
};

#endif /* Global_h */
