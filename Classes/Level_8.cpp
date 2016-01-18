//
//  Level_8.cpp
//  DesertTour
//
//  Created by Cary on 15/12/26.
//
//

#include "Level_8.hpp"


#include "MainUI.hpp"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;



Scene* Level_8::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->setName("level_8");
    /** 吧物理世界设置成式调模式
     *  @2015/12/16 11:15
     */
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0 , -800.0f));
    auto layer = Level_8::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Level_8::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visiblePoint = Director::getInstance()->getVisibleOrigin();
    
    auto root_level = CSLoader::createNode("Scene/LevelScene/Level_8.csb");
    root_level->setTag(100001);
    this->addChild(root_level);
    //设置物理 空心世界
    PhysicsBody* psworld =PhysicsBody::createEdgeBox(visibleSize*1.5,PHYSICSBODY_MATERIAL_DEFAULT,2);
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
    addChild(maincar_r,10);
    addChild(mainui,3000);
    //退出
    Exit* eit = Exit::create();
    eit->setObj(mainexit);
    addChild(eit);
    
    //添加地面的刚体
    Sprite* gound_1 = root_level->getChildByName<Sprite*>("l8_gound_1_1");
    Sprite* gound_2 = root_level->getChildByName<Sprite*>("l8_gound_2_1");
    Sprite* gound_3 = root_level->getChildByName<Sprite*>("l8_gound_3_1");
    Sprite* gound_4 = root_level->getChildByName<Sprite*>("l8_gound_4_1");
    Sprite* gound_5 = root_level->getChildByName<Sprite*>("l8_gound_5_1");
    Sprite* gound_6 = root_level->getChildByName<Sprite*>("l8_gound_6_1");
    Sprite* gound_7 = root_level->getChildByName<Sprite*>("l8_gound_7_1");
    ToolsFunction::setPhyDynamicSpriteBox(gound_1);
    ToolsFunction::setPhyDynamicSpriteBox(gound_2);
    ToolsFunction::setPhyDynamicSpriteBox(gound_3);
    ToolsFunction::setPhyDynamicSpriteBox(gound_4);
    ToolsFunction::setPhyDynamicSpriteBox(gound_5);
    ToolsFunction::setPhyDynamicSpriteBox(gound_6);
    //ToolsFunction::setPhyDynamicSpriteBox(gound_7);

    //按钮 1
    Button* b1 = root_level->getChildByName<Button*>("Button_1");
    Button* b2 = root_level->getChildByName<Button*>("Button_2");
    Button* b3 = root_level->getChildByName<Button*>("Button_3");
    //按钮问题
    Sprite* q1 = root_level->getChildByName<Sprite*>("question_1");
    Sprite* q2 = root_level->getChildByName<Sprite*>("question_2");
    Sprite* q3 = root_level->getChildByName<Sprite*>("question_3");
    //创建颜色按钮 4个按钮
    QuestionButton* btn_2 = QuestionButton::create();
    btn_2->setObj(b2);
    addChild(btn_2);
    QuestionButton* btn_3 = QuestionButton::create();
    btn_3->setObj(b3);
    addChild(btn_3);
    //给按钮设置问题 4个问题
    Btn_QuestionSelect* qbtn_2 = Btn_QuestionSelect::create();
    qbtn_2->setObj(q2);
    qbtn_2->setIBtnMainUI(mainui, btn_2);
    addChild(qbtn_2);
    Btn_QuestionSelect* qbtn_3 = Btn_QuestionSelect::create();
    qbtn_3->setObj(q3);
    qbtn_3->setIBtnMainUI(mainui, btn_3);
    addChild(qbtn_3);
    
    
    
    
    
    
    
    
    
    return true;
}



















