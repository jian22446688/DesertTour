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
    if ( !Layer::init() ){
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visiblePoint = Director::getInstance()->getVisibleOrigin();
    auto root_level = CSLoader::createNode("Scene/LevelScene/Level_9.csb");
    root_level->setTag(100001);
    this->addChild(root_level);
    //设置物理 空心世界
    PhysicsBody* psworld =PhysicsBody::createEdgeBox(visibleSize*2,PHYSICSBODY_MATERIAL_DEFAULT,2);
    psworld->setTag(100001);
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
    Sprite* gound_1 = root_level->getChildByName<Sprite*>("l9_gound_1");
    Sprite* gound_2 = root_level->getChildByName<Sprite*>("l9_gound_2");
    Sprite* gound_3 = root_level->getChildByName<Sprite*>("l9_gound_3");
    Sprite* gound_4 = root_level->getChildByName<Sprite*>("l9_gound_4");
    Sprite* gound_5 = root_level->getChildByName<Sprite*>("l9_gound_5");
    Sprite* gound_6 = root_level->getChildByName<Sprite*>("l9_gound_6");
    Sprite* gound_7 = root_level->getChildByName<Sprite*>("l9_gound_7");
    Sprite* gound_8 = root_level->getChildByName<Sprite*>("l9_gound_8");
    Sprite* gound_9 = root_level->getChildByName<Sprite*>("l9_gound_9");
    Node* gound_10 = root_level->getChildByName<Node*>("l9_gound_10");
    Sprite* gound_11 = root_level->getChildByName<Sprite*>("l9_gound_11");
    Sprite* gound_12 = root_level->getChildByName<Sprite*>("l9_gound_12");
    ToolsFunction::setPhyDynamicSpriteBox(gound_1);
    ToolsFunction::setPhyDynamicSpriteBox(gound_2);
    ToolsFunction::setPhyDynamicSpriteBox(gound_3);
    ToolsFunction::setPhyDynamicSpriteBox(gound_4);
    ToolsFunction::setPhyDynamicSpriteBox(gound_5);
    PhysicsBody* gua = PhysicsBody::createBox(gound_9->getContentSize());
    gua->setTag(400030);
    gua->setRotationEnable(false);
    gua->setCategoryBitmask(0x01);
    gua->setCollisionBitmask(0x02);
    gua->setContactTestBitmask(0x01);
    gua->setDynamic(true);
    gound_9->setPhysicsBody(gua);
    PhysicsBody* gua1 = PhysicsBody::createBox(gound_8->getContentSize());
    gua1->setRotationEnable(false);
    gua1->setCategoryBitmask(0x01);
    gua1->setCollisionBitmask(0x02);
    gua1->setContactTestBitmask(0x01);
    gua1->setDynamic(true);
    gound_8->setPhysicsBody(gua1);
    //按钮
    Sprite* b1 = root_level->getChildByName<Sprite*>("Button_1");
    Sprite* b2 = root_level->getChildByName<Sprite*>("Button_2");
    //按钮问题
    Sprite* q1 = root_level->getChildByName<Sprite*>("question_1");
    Sprite* q2 = root_level->getChildByName<Sprite*>("question_2");
    Sprite* q3 = root_level->getChildByName<Sprite*>("question_3");
    Sprite* q4 = root_level->getChildByName<Sprite*>("question_4");
    Btn_Standard* btn_1 = Btn_Standard::create();
    btn_1->setObj(b1);
    addChild(btn_1,5);
    Btn_Standard* btn_2 = Btn_Standard::create();
    btn_2->setObj(b2);
    addChild(btn_2,5);
    //升降台
    L9_Lifting* lifting_1 = L9_Lifting::create();
    lifting_1->setObj(gound_6);
    addChild(lifting_1);
    L9_Lifting* lifting_2 = L9_Lifting::create();
    lifting_2->setObj(gound_7);
    addChild(lifting_2);
    //给按钮设置问题 4个问题
    Btn_QuestionSelect* qbtn_1 = Btn_QuestionSelect::create();
    qbtn_1->setObj(q1);
    qbtn_1->setIBtnMainUI(mainui, btn_1);
    addChild(qbtn_1,8);
    Btn_QuestionSelect* qbtn_2 = Btn_QuestionSelect::create();
    qbtn_2->setObj(q2);
    qbtn_2->setIBtnMainUI(mainui, btn_2);
    addChild(qbtn_2,8);
    Btn_QuestionSelect* qbtn_3 = Btn_QuestionSelect::create();
    qbtn_3->setObj(q3);
    qbtn_3->setIBtnMainUI(mainui, lifting_1);
    addChild(qbtn_3,8);
    Btn_QuestionSelect* qbtn_4 = Btn_QuestionSelect::create();
    qbtn_4->setObj(q4);
    qbtn_4->setIBtnMainUI(mainui, lifting_2);
    addChild(qbtn_4,8);
    btn_1->getBtn()->addTouchEventListener([=](Ref* reft, Widget::TouchEventType type)
                                           {
                                               if (type == Widget::TouchEventType::ENDED) {
                                                   btn_1->PlayEffect();
                                                   if (isopen) {
                                                       if (lifting_1->IsEn() && lifting_2->IsEn()) {
                                                           if (keyup) {
                                                               
                                                               auto moto = MoveTo::create(2.0f, Vec2(lifting_1->getPosition().x, 642.56f));
                                                               lifting_1->runAction(moto);
                                                               auto moto1 = MoveTo::create(2.0f, Vec2(lifting_2->getPosition().x, 642.56f));
                                                               lifting_2->runAction(moto1);
                                                               keyup = false;
                                                           }else{
                                                               auto moto = MoveTo::create(2.0f, Vec2(lifting_1->getPosition().x, 842.56f));
                                                               lifting_1->runAction(moto);
                                                               auto moto1 = MoveTo::create(2.0f, Vec2(lifting_2->getPosition().x, 396.56f));
                                                               lifting_2->runAction(moto1);
                                                               keyup = true;
                                                           }
                                                       }
                                                   }
                                               }
                                           });
    btn_2->getBtn()->addTouchEventListener([=](Ref* reft, Widget::TouchEventType type)
                                           {
                                               if (type == Widget::TouchEventType::ENDED) {
                                                   btn_2->PlayEffect();
                                                   btn_2->getBtn()->setEnabled(false);
                                                   auto anim = CSLoader::createTimeline("Node/animation/L3_e.csb");
                                                   anim->gotoFrameAndPlay(0, 210, false);
                                                   root_level->runAction(anim);
                                                   anim->addFrameEndCallFunc(52, "a", [=]()
                                                                             {
                                                                                 auto mov = MoveTo::create(0.5f, Vec2(gound_4->getPosition().x, 130.6f));
                                                                                 gound_4->runAction(mov);
                                                                             });
                                                   anim->addFrameEndCallFunc(105, "b", [=]()
                                                                             {
                                                                                 auto mov = MoveTo::create(0.5f, Vec2(gound_4->getPosition().x, 80.6f));
                                                                                 gound_4->runAction(mov);
                                                                             });
                                                   anim->addFrameEndCallFunc(151, "c", [=]()
                                                                             {
                                                                                 auto mov = MoveTo::create(0.5f, Vec2(gound_4->getPosition().x, 40.6f));
                                                                                 gound_4->runAction(mov);
                                                                             });
                                                   anim->addFrameEndCallFunc(191, "d", [=]()
                                                                             {
                                                                                 auto mov = MoveTo::create(0.5f, Vec2(gound_4->getPosition().x, -12.31f));
                                                                                 gound_4->runAction(mov);
                                                                             });
                                               }
                                               isopen = true;
                                           });
    
    Guard_gu* guard = Guard_gu::create();
    guard->setObj(gound_10);
    guard->setMovePosition(gound_11, gound_12, 26.0f);
    addChild(guard);
    
    return true;
}























