//
//  Level_4.cpp
//  DesertTour
//
//  Created by Cary on 15/12/26.
//
//

#include "Level_4.hpp"


#include "MainUI.hpp"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;



Scene* Level_4::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->setName("level_4");
    
    /** 吧物理世界设置成式调模式
     *  @2015/12/16 11:15
     */
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    scene->getPhysicsWorld()->setGravity(Vec2(0 , -800.0f));
    auto layer = Level_4::create();
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Level_4::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visiblePoint = Director::getInstance()->getVisibleOrigin();
    
    auto root_level_4 = CSLoader::createNode("Scene/LevelScene/Level_4.csb");
    root_level_4->setTag(100001);
    this->addChild(root_level_4);
    
    //设置物理 空心世界
    PhysicsBody* psworld =PhysicsBody::createEdgeBox(visibleSize*1.5,PHYSICSBODY_MATERIAL_DEFAULT,2);
    psworld->setCategoryBitmask(0x01);
    psworld->setCollisionBitmask(0x01);
    psworld->setContactTestBitmask(0x01);
    root_level_4->setPhysicsBody(psworld);
    
    //完成退出
    Sprite* exitl4 = root_level_4->getChildByName<Sprite*>("img_next_21");
    //主要车
    Sprite* carl4 = root_level_4->getChildByName<Sprite*>("img_maincarbody_1");
    //按钮一
    Sprite* btnl4_1 = root_level_4->getChildByName<Sprite*>("btn_010001_22");
    //按钮二
    Sprite* btnl4_2 = root_level_4->getChildByName<Sprite*>("btn_010001_22_0");
    //按钮三
    Sprite* btnl4_3 = root_level_4->getChildByName<Sprite*>("btn_010001_22_1");
    //按钮一
    Sprite* monsterl4_1 = root_level_4->getChildByName<Sprite*>("btn_010001_22_2");
    //按钮二
    Sprite* monsterl4_2 = root_level_4->getChildByName<Sprite*>("btn_010001_22_3");
    //按钮三
    Sprite* monsterl4_3 = root_level_4->getChildByName<Sprite*>("btn_010001_22_4");
    //按钮三
    Sprite* monsterl4_4 = root_level_4->getChildByName<Sprite*>("btn_010001_22_2_0");
    //地面上面
    Sprite* groundl4_1 = root_level_4->getChildByName<Sprite*>("td3_4_0");
    //地面下面
    Sprite* groundl4_2 = root_level_4->getChildByName<Sprite*>("td6_1");
    //平移动地面
    Sprite* groundl4_3 = root_level_4->getChildByName<Sprite*>("td4_16");
    //固定柱子
    Sprite* groundl4_4 = root_level_4->getChildByName<Sprite*>("td2_14");
    //地面上面
    Sprite* groundl4_5 = root_level_4->getChildByName<Sprite*>("td3_4");
    //地面上下移动
    Sprite* groundl4_6 = root_level_4->getChildByName<Sprite*>("td5_2");
    //弹簧
    Sprite* springl4 = root_level_4->getChildByName<Sprite*>("tur0001_91");
    //怪物僵死
    Sprite* monsterl4_js = root_level_4->getChildByName<Sprite*>("anim_guaiwu_1");
    //问题1
    Sprite* questionl4_1 = root_level_4->getChildByName<Sprite*>("anim_question0001_25");
    //问题2
    Sprite* questionl4_2 = root_level_4->getChildByName<Sprite*>("anim_question0001_25_0");
    //问题3
    Sprite* questionl4_3 = root_level_4->getChildByName<Sprite*>("anim_question0001_25_1");
    
    monsterl4_1->setVisible(false);
    monsterl4_2->setVisible(false);
    monsterl4_3->setVisible(false);
    monsterl4_4->setVisible(false);
    //设置刚体
    ToolsFunction::setPhyDynamicSpriteBox(groundl4_1);
    ToolsFunction::setPhyDynamicSpriteBox(groundl4_2);
    ToolsFunction::setPhyDynamicSpriteBox(groundl4_3);
    ToolsFunction::setPhyDynamicSpriteBox(groundl4_4);
    ToolsFunction::setPhyDynamicSpriteBox(groundl4_5);
    ToolsFunction::setPhyDynamicSpriteBox(groundl4_6);
    
    //创建主要UI界面
    mainui = MainUI::create();
    auto maincar_r = MainCar_R::create();
    mainui->setCar_R(maincar_r);
    maincar_r->setMainUI(mainui);
    maincar_r->setObj(carl4);
    addChild(maincar_r);
    addChild(mainui,3000);

    //弹簧
    objSpring* ths = objSpring::create();
    ths->setObj(springl4);
    addChild(ths);
    //地面移动到弹簧上面
    Layer* grlayer = Layer::create();
    grlayer->addChild(groundl4_2);
    addChild(grlayer);
    //弹簧按按钮
    Btn_Standard* bs2 = Btn_Standard::create();
    bs2->setObj(btnl4_3);
    addChild(bs2,30);
    Btn_QuestionSelect* qbs2 = Btn_QuestionSelect::create();
    qbs2->setObj(questionl4_3);
    qbs2->setIBtnMainUI(mainui, bs2);
    addChild(qbs2,30);
    //怪物按钮
    Btn_Standard* bs3 = Btn_Standard::create();
    bs3->setObj(btnl4_1);
    addChild(bs3,30);
    Btn_QuestionSelect* qbs3 = Btn_QuestionSelect::create();
    qbs3->setObj(questionl4_1);
    qbs3->setIBtnMainUI(mainui, bs3);
    addChild(qbs3,30);
    //移动按钮
    Btn_Standard* bs4 = Btn_Standard::create();
    bs4->setObj(btnl4_2);
    addChild(bs4,30);
    Btn_QuestionSelect* qbs4 = Btn_QuestionSelect::create();
    qbs4->setObj(questionl4_2);
    qbs4->setIBtnMainUI(mainui, bs4);
    addChild(qbs4,30);
    //怪物
    guaiwu_js* gjs = guaiwu_js::create();
    gjs->setGuanwu(monsterl4_js);
    gjs->setMovePosition(monsterl4_3, monsterl4_2, 22.0f);
    
    addChild(gjs);
    
    //退出
    Exit* eit = Exit::create();
    eit->setObj(exitl4);
    addChild(eit);
    
    groundl4_6->getPhysicsBody()->setTag(PHY_TAG_BARRIER);
    //弹簧按钮
    bs2->getBtn()->addTouchEventListener([=](Ref* reft, Widget::TouchEventType type)
                                         {
                                             if (type==Widget::TouchEventType::ENDED) {
                                                 bs4->PlayEffect();
                                                 ths->addForce(Vec2(0, 3000.0f));
                                             }
                                         });
    //控制按钮
    bs3->getBtn()->addTouchEventListener([=](Ref* reft, Widget::TouchEventType type)
                                         {
                                             if (type==Widget::TouchEventType::ENDED) {
                                                 bs4->PlayEffect();
                                                 bs3->getBtn()->setEnabled(false);
                                                 auto anim = CSLoader::createTimeline("Node/animation/L3_e.csb");
                                                 anim->gotoFrameAndPlay(0, 210, false);
                                                 root_level_4->runAction(anim);
                                                 anim->addFrameEndCallFunc(52, "a", [=]()
                                                                           {
                                                                               if (gjs->getPosition().x <=groundl4_6->getPosition().x) {
                                                                                   //而不皱
                                                                                   gjs->setMovePosition(monsterl4_3,        monsterl4_4, 18.0f);
                                                                               }else{
                                                                                   //而不皱
                                                                                   gjs->setMovePosition(monsterl4_1, monsterl4_2, 18.0f);
                                                                               }
                                                                               auto mov = MoveTo::create(0.5f, Vec2(groundl4_6->getPosition().x, 41.6f));
                                                                               groundl4_6->runAction(mov);
                                                                               
                                                                           });
                                                 anim->addFrameEndCallFunc(105, "b", [=]()
                                                                           {
                                                                               auto mov = MoveTo::create(0.5f, Vec2(groundl4_6->getPosition().x, 82.6f));
                                                                               groundl4_6->runAction(mov);
                                                                           });
                                                 anim->addFrameEndCallFunc(151, "c", [=]()
                                                                           {
                                                                               auto mov = MoveTo::create(0.5f, Vec2(groundl4_6->getPosition().x, 124.6f));
                                                                               groundl4_6->runAction(mov);
                                                                           });
                                                 anim->addFrameEndCallFunc(191, "d", [=]()
                                                                           {
                                                                               auto mov = MoveTo::create(0.5f, Vec2(groundl4_6->getPosition().x, 162.2f));
                                                                               groundl4_6->runAction(mov);
                                                                           });
                                             }
                                         });
    //移动按钮
    bs4->getBtn()->addTouchEventListener([=](Ref* reft, Widget::TouchEventType type)
                                         {
                                             if (type==Widget::TouchEventType::ENDED) {
                                                 bs4->PlayEffect();
                                                 auto move = MoveTo::create(0.5f, Vec2(500.0f, groundl4_3->getPosition().y));
                                                 groundl4_3->runAction(move);
                                             }
                                         });
    return true;
}


























