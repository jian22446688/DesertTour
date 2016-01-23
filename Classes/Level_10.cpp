//
//  Level_10.cpp
//  DesertTour
//
//  Created by Cary on 15/12/26.
//
//

#include "Level_10.hpp"


#include "MainUI.hpp"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;



Scene* Level_10::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->setName("level_10");
    
    /** 吧物理世界设置成式调模式
     *  @2015/12/16 11:15
     */
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0 , -800.0f));
    scene->getPhysicsWorld()->setAutoStep(false);
    auto layer = Level_10::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Level_10::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visiblePoint = Director::getInstance()->getVisibleOrigin();
    auto root_level = CSLoader::createNode("Scene/LevelScene/Level_10.csb");
    root_level->setTag(100001);
    this->addChild(root_level);

    //设置物理 空心世界
    PhysicsBody* psworld =PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,2);
    psworld->setCategoryBitmask(0x01);
    psworld->setCollisionBitmask(0x01);
    psworld->setContactTestBitmask(0x01);
    root_level->setPhysicsBody(psworld);
    //车
    Sprite* maincar = root_level->getChildByName<Sprite*>("img_maincarbody_17");
    //退出
    Sprite* mainexit = root_level->getChildByName<Sprite*>("img_next_14");
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
    //添加地面的刚体
    Sprite* gound_1 = root_level->getChildByName<Sprite*>("btn_1");
    Sprite* gound_2 = root_level->getChildByName<Sprite*>("btn_2");
    Sprite* gound_3 = root_level->getChildByName<Sprite*>("l10_gound_3");
    Sprite* gound_4 = root_level->getChildByName<Sprite*>("l10_gound_2");
    Sprite* gound_5 = root_level->getChildByName<Sprite*>("l10_gound_1");
    Sprite* gound_6 = root_level->getChildByName<Sprite*>("l10_gound_1");
    Sprite* gound_7 = root_level->getChildByName<Sprite*>("btn_010001_12_0_0");
   // ToolsFunction::setPhyDynamicSpriteBox(gound_1);
   // ToolsFunction::setPhyDynamicSpriteBox(gound_4);
    ToolsFunction::setPhyDynamicSpriteBox(gound_3);

    //按钮问题
    Sprite* q1 = root_level->getChildByName<Sprite*>("question_1");
    Sprite* q2 = root_level->getChildByName<Sprite*>("question_2");
    Sprite* q3 = root_level->getChildByName<Sprite*>("question_3");
    Sprite* q4 = root_level->getChildByName<Sprite*>("question_4");
    SpriteTweenBase* stb = SpriteTweenBase::create();
    stb->setPosition(467.0f, 500.0f);
    addChild(stb,10);
    Boos_gu* boos = Boos_gu::create();
    boos->setObj(gound_7);
    boos->setMovePosition(gound_2, gound_1, 32.0f);
    addChild(boos);
    
    //给按钮设置问题 4个问题
    Btn_QuestionSelect* qbtn_1 = Btn_QuestionSelect::create();
    qbtn_1->setObj(q1);
    qbtn_1->setIBtnMainUI(mainui, stb);
    addChild(qbtn_1,8);
    Btn_QuestionSelect* qbtn_2 = Btn_QuestionSelect::create();
    qbtn_2->setObj(q2);
    qbtn_2->setIBtnMainUI(mainui, stb);
    addChild(qbtn_2,8);
    Btn_QuestionSelect* qbtn_3 = Btn_QuestionSelect::create();
    qbtn_3->setObj(q3);
    qbtn_3->setIBtnMainUI(mainui, stb);
    addChild(qbtn_3,8);
    Btn_QuestionSelect* qbtn_4 = Btn_QuestionSelect::create();
    qbtn_4->setObj(q4);
    qbtn_4->setIBtnMainUI(mainui, stb);
    addChild(qbtn_4,8);
    
    
    
    
    
    
    scheduleUpdate();
    
    return true;
}


void  Level_10::update(float ft){
    
    for (int i = 0; i < 3; i++) {
        this->getScene()->getPhysicsWorld()->step(1/180.0f);
    }
    
}




























