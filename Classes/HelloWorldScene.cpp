#include "HelloWorldScene.h"
#include "GameScene.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto itemLabel = Label::createWithTTF("Start Game", "fonts/Marker Felt.ttf", 18);
    itemLabel->setColor(Color3B(12,27,10));
    auto startItem = MenuItemLabel::create(itemLabel, CC_CALLBACK_1(HelloWorld::transitionToGameScene,this));
    startItem->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 - startItem->getContentSize().height));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(startItem, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Dark Forest"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Dark Forest", "fonts/Marker Felt.ttf", 48);
    label->setColor(Color3B(128,128,128));
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::startGame()
{
    //get the game scene and run it.
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void HelloWorld::transitionToGameScene(Ref* pSender)
{
    auto size = Director::getInstance()->getWinSize();      //get the windows size.
    
    auto clipper = ClippingNode::create();      // create the ClippingNode object
    
    auto stencil = DrawNode::create();      // create the DrawNode object which can draw dots, segments and polygons.
    
    Point triangle[3];      // init the  triangle vertexes. here my win size is 360x640, so my triangle vertexes init by these values. You can change the values to adapt your scree.
    triangle[0] = Point(-size.width * 1.5f, -size.height / 2);
    triangle[1] = Point(size.width * 1.5f, -size.height / 2);
    triangle[2] = Point(0, size.height);
    Color4F green(0, 1, 0, 1);
    
    stencil->drawPolygon(triangle, 3, green, 0, green);     //use the drawNode to draw the triangle to cut the ClippingNode.
    
    clipper->setAnchorPoint(Point(0.5f, 0.5f));     // set the ClippingNode anchorPoint, to make sure the drawNode at the center of ClippingNode
    clipper->setPosition(size.width / 2, size.height / 2);
    clipper->setStencil(stencil);   //set the cut triangle in the ClippingNode.
    clipper->setInverted(true);     //make sure the content is show right side.
    
    Sprite* blackRect = Sprite::create("HelloWorld.png");     //create a black screen sprite to make sure the bottom is black. the"black_screen.png" is a "black screen" png.
    
    clipper->addChild(blackRect);   //to make sure the cover is black.
    
    this->addChild(clipper, 500);
    
    // the Clipping node triangle  add some actions to make the triangle scale and rotate.
    stencil->runAction(EaseSineOut::create(Spawn::create(ScaleTo::create(2.5f, 0.0f, 0.0f), RotateBy::create(2.5f, 540),
                                                         Sequence::create(DelayTime::create(2.5), CallFunc::create(this, callfunc_selector(HelloWorld::startGame)), NULL), NULL)));
    
}
