#include "Global.h"

USING_NS_CC;

static Global* global = nullptr;

Global::Global()
{
    enemyMoving = false;
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
    return hypotf(p2.x - p1.x, p2.y - p1.y);
}

int Global::calDisclosure(cocos2d::Vec2 item_pos, int item_radius, cocos2d::Vec2 window_pos, int window_radius, int cloud_radius)
{
    int result = 0;
    float distance = Global::calDistance(item_pos, window_pos);
    if (distance < (item_radius + window_radius)) {
        // from 50 to 100
        result = 50 + (window_radius - (distance - item_radius)) * 50 / (window_radius * 2);
    } else if (distance < (item_radius + cloud_radius)) {
        // from 0 to 50: (Could Radius - abs(Distance - Item Radius)) * 50 / (Cloud Radius - Window Radius)
        result = (cloud_radius - std::abs(distance - item_radius)) * 50 / (cloud_radius - window_radius);
    }
    return result;
}

int Global::calDamage(cocos2d::Vec2 bullet_pos, cocos2d::Vec2 item_pos, int item_radius)
{
    int disclosure = Global::calDisclosure(bullet_pos, Global::BulletRadius, item_pos, item_radius, item_radius);
    if (disclosure > 50)
        return (disclosure -50) * 2;
    else
        return 0;
}