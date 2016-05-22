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
