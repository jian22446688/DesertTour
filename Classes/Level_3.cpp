//
//  Level_3.cpp
//  DesertTour
//
//  Created by Cary on 15/12/15.
//
//

#include "Level_3.hpp"
#include "MainUI.hpp"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;



Scene* Level_3::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->setName("level_3");
    
    /** 吧物理世界设置成式调模式
     *  @2015/12/16 11:15
     */
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    scene->getPhysicsWorld()->setGravity(Vec2(0 , -800.0f));
    
    auto layer = Level_3::create();
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Level_3::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visiblePoint = Director::getInstance()->getVisibleOrigin();
    
    auto root_level_3 = CSLoader::createNode("Scene/LevelScene/Level_3.csb");
    root_level_3->setTag(100001);
    this->addChild(root_level_3);
    
    //设置物理 空心世界
    PhysicsBody* psworld =PhysicsBody::createEdgeBox(visibleSize*1.1,PHYSICSBODY_MATERIAL_DEFAULT,2);
    psworld->setCategoryBitmask(0x01);
    psworld->setCollisionBitmask(0x01);
    psworld->setContactTestBitmask(0x01);
    root_level_3->setPhysicsBody(psworld);

    //设置物理世界
    Sprite* physics_1 = root_level_3->getChildByName<Sprite*>("Sprite_19");
    Sprite* physics_2 = root_level_3->getChildByName<Sprite*>("di3_20");
    Sprite* physics_3 = root_level_3->getChildByName<Sprite*>("di4_21");
    Sprite* physics_4 = root_level_3->getChildByName<Sprite*>("img_ground_06_23");
    ToolsFunction::setPhyDynamicSpriteBox(physics_1);
    ToolsFunction::setPhyDynamicSpriteBox(physics_2);
    ToolsFunction::setPhyDynamicSpriteBox(physics_3);
    ToolsFunction::setPhyDynamicSpriteBox(physics_4);
    
    
    //完成关卡退出
    Sprite* next = root_level_3->getChildByName<Sprite*>("img_next_35");
    Exit* ne = Exit::create();
    ne->setObj(next);
    addChild(ne);
    
    //怪物移动
    Sprite* gg = root_level_3->getChildByName<Sprite*>("anim_guaiwu_zo0001_31");
    Sprite* ggd1 = root_level_3->getChildByName<Sprite*>("btn_010001_25_0_0_0");
    Sprite* ggd2 = root_level_3->getChildByName<Sprite*>("btn_010001_25_0_0");
    guaiwu_js* gjs = guaiwu_js::create();
    gjs->setGuanwu(gg);
    gjs->setMovePosition(ggd1, ggd2, 18.0f);
    addChild(gjs);
    
    
    //获取车的位置
    Sprite* mycar = root_level_3->getChildByName<Sprite*>("img_maincarbody_1");
    
    //创建主要UI界面
    mainui = MainUI::create();
    auto maincar_r = MainCar_R::create();
    mainui->setCar_R(maincar_r);
    maincar_r->setMainUI(mainui);
    maincar_r->setObj(mycar);
    addChild(maincar_r);
    addChild(mainui,3000);
    
    //地上的按钮
    Sprite* mov = root_level_3->getChildByName<Sprite*>("img_ground_06_23");
    
    //地上的按钮
    Sprite* movup = root_level_3->getChildByName<Sprite*>("td5_24");
    ToolsFunction::setPhyDynamicSpriteBox(movup);
    
    //地上的按钮
    Sprite* dbtn1 = root_level_3->getChildByName<Sprite*>("btn_dicar0001_86");
    Btn_Ground* btng = Btn_Ground::create();
    btng->setObj(dbtn1);
    addChild(btng);
    
    //升降
    Sprite* btn1 = root_level_3->getChildByName<Sprite*>("btn_010001_25");
    Btn_Standard* bs1 = Btn_Standard::create();
    bs1->setObj(btn1);
    addChild(bs1,30);
    //弹簧
    Sprite* th = root_level_3->getChildByName<Sprite*>("tur0001_91");
    objSpring* ths = objSpring::create();
    ths->setObj(th);
    addChild(ths);
    //地面
    Layer* grlayer = Layer::create();
    auto ground = root_level_3->getChildByName<Sprite*>("Sprite_19");
    grlayer->addChild(ground);
    addChild(grlayer);

    //弹簧按钮
    Sprite* btn2 = root_level_3->getChildByName<Sprite*>("btn_010001_25_0");
    Btn_Standard* bs2 = Btn_Standard::create();
    bs2->setObj(btn2);
    addChild(bs2,30);
    //第一个按钮问题
    Sprite* qbtn1 = root_level_3->getChildByName<Sprite*>("anim_question0001_36_0");
    Btn_QuestionSelect* qb1 = Btn_QuestionSelect::create();
    qb1->setObj(qbtn1);
    qb1->setIBtnMainUI(mainui, bs1);
    addChild(qb1,30);
    //第二个按钮问题
    Sprite* qbtn2 = root_level_3->getChildByName<Sprite*>("anim_question0001_36");
    Btn_QuestionSelect* qb2 = Btn_QuestionSelect::create();
    qb2->setObj(qbtn2);
    qb2->setIBtnMainUI(mainui, bs2);
    addChild(qb2,30);
    
    //第二个按钮问题
    Sprite* qbtn3 = root_level_3->getChildByName<Sprite*>("anim_question0001_36_1");
    Btn_QuestionSelect* qb3 = Btn_QuestionSelect::create();
    qb3->setObj(qbtn3);
    qb3->setIBtnMainUI(mainui, btng);
    addChild(qb3,30);
    
    //火的精灵
    Sprite* fire1 = root_level_3->getChildByName<Node*>("FileNode_6")->getChildByName<Sprite*>("anim_huo0001_1");
    //设置刚体
    PhysicsBody* psworld2 =PhysicsBody::createBox(Size(fire1->getContentSize().width-40,fire1->getContentSize().height-20));
    //火的碰撞掩码
    psworld2->setTag(PHY_TAG_KILL_FIRE);
    //设置触发 掩码
    psworld2->setContactTestBitmask(0x01);
    psworld2->setCollisionBitmask(0x02);
    psworld2->setDynamic(false);
    fire1->setPhysicsBody(psworld2);
    
    //帧动画 不能使用精灵运行帧动画
    auto fireh1 = CSLoader::createTimeline("Node/animation/L2_fire.csb");
    fireh1->gotoFrameAndPlay(0, 33, true);
    root_level_3->runAction(fireh1);
    //火的按钮
    Sprite* firs = root_level_3->getChildByName<Sprite*>("btn_010001_25_1");
    //火问题的按钮
    Sprite* qfirs = root_level_3->getChildByName<Sprite*>("anim_question0001_36_0_0");
    Btn_Standard* bfirs = Btn_Standard::create();
    bfirs->setObj(firs);
    addChild(bfirs);
    Btn_QuestionSelect* qbfirs = Btn_QuestionSelect::create();
    qbfirs->setObj(qfirs);
    qbfirs->setIBtnMainUI(mainui, bfirs);
    addChild(qbfirs);
    
    
    
    //添加地雷
    Node* nh2 = root_level_3->getChildByName<Node*>("FileNode_3_001");
    Bombed* bm = Bombed::create();
    bm->setObj(nh2);
    bm->IsBtnEnable(true);
    addChild(bm);
    
    //地雷的按钮
    Sprite* dm1 = root_level_3->getChildByName<Sprite*>("di3_20");
    Layer* dmlayer = Layer::create();
    dmlayer->addChild(dm1);
    addChild(dmlayer);
    //火问题的按钮
    Sprite* dbom = root_level_3->getChildByName<Sprite*>("btn_dicar0001_86_0");
    Btn_Ground_1* dbm = Btn_Ground_1::create();
    dbm->setObj(dbom);
    //dbm->IsBtnEnable(true);
    addChild(dbm);
    
    //地雷的按钮
    Sprite* bombe = root_level_3->getChildByName<Sprite*>("anim_question0001_36_2");
    Btn_QuestionSelect* qbfirse = Btn_QuestionSelect::create();
    qbfirse->setObj(bombe);
    qbfirse->setIBtnMainUI(mainui, dbm);
    addChild(qbfirse);
    
    dbm->onCallbackTest_2([=]()
                          {
                              auto mov = MoveTo::create(0.5f, Vec2(bm->getPosition().x, 315.0f));
                              bm->runAction(mov);
                          });
    
    bfirs->getBtn()->addTouchEventListener([=](Ref* reft,Widget::TouchEventType type)
                                           {
                                               if (type ==Widget::TouchEventType::ENDED)
                                               {
                                                   bfirs->PlayEffect();
                                                   //控制火的按钮
                                                   fireh1->gotoFrameAndPause(36);
                                                   fire1->getPhysicsBody()->setEnabled(false);
                                               }
                                           });
    
    bs2->getBtn()->addTouchEventListener([=](Ref* reft,Widget::TouchEventType type)
                                         {
                                             if (type ==Widget::TouchEventType::ENDED)
                                             {
                                                 bfirs->PlayEffect();
                                                 ths->addForce();
                                             }
                                         });
    
    bs1->getBtn()->addTouchEventListener([=](Ref* reft,Widget::TouchEventType type)
                                         {
                                             if (type ==Widget::TouchEventType::ENDED)
                                             {
                                                 bfirs->PlayEffect();
                                                 bs1->getBtn()->setEnabled(false);
                                                 MoveTo* m = MoveTo::create(2.0f, Vec2(movup->getPosition().x, 229.2f));
                                                 movup->runAction(m);
                                             }
                                         });
    btng->onCallbackTest_2([=]()
                           {
                               bfirs->PlayEffect();
                               MoveTo* mp = MoveTo::create(1.0f, Vec2(860.0f, mov->getPosition().y));
                               mov->runAction(mp);
                           });
    
    
    
    
    return true;
}


































































