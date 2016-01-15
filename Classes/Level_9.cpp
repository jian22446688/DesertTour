//
//  Level_9.cpp
//  DesertTour
//
//  Created by Cary on 15/12/26.
//
//

#include "Level_9.hpp"


#include "MainUI.hpp"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;



Scene* Level_9::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->setName("level_9");
    
    /** 吧物理世界设置成式调模式
     *  @2015/12/16 11:15
     */
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    scene->getPhysicsWorld()->setGravity(Vec2(0 , -800.0f));
    
    auto layer = Level_9::create();
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Level_9::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visiblePoint = Director::getInstance()->getVisibleOrigin();
    
    auto root_level = CSLoader::createNode("Scene/LevelScene/Level_9.csb");
    root_level->setTag(100001);
    this->addChild(root_level);
    
    
    //设置物理 空心世界
    PhysicsBody* psworld =PhysicsBody::createEdgeBox(visibleSize*1.5,PHYSICSBODY_MATERIAL_DEFAULT,2);
    psworld->setCategoryBitmask(0x01);
    psworld->setCollisionBitmask(0x01);
    psworld->setContactTestBitmask(0x01);
    root_level->setPhysicsBody(psworld);

    //车
    Sprite* maincar = root_level->getChildByName<Sprite*>("FileNode_1");
    //退出
    Sprite* mainexit = root_level->getChildByName<Sprite*>("FileNode_1_0");
    
    //创建主要UI界面
    mainui = MainUI::create();
    auto maincar_r = MainCar_R::create();
    mainui->setCar_R(maincar_r);
    maincar_r->setMainUI(mainui);
    maincar_r->setObj(maincar);
    addChild(maincar_r);
    addChild(mainui,3000);
    //退出
    Exit* eit = Exit::create();
    eit->setObj(mainexit);
    addChild(eit);
    
    
    return true;
}























