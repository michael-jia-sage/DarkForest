#include "Global.h"

USING_NS_CC;

static Global* global = nullptr;

Global::Global()
{
    canFire = true;
    scoreValue = 0;
}

Global* Global::getInstance()
{
    if (!global) {
        global = new (std::nothrow)Global();
    }
    
    return global;
}

float Global::calDistance(cocos2d::Vec2 p1, cocos2d::Vec2 p2)
{
    return hypotf(p2.x - p1.x, p2.y - p2.y);
}
