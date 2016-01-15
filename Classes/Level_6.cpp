//
//  Level_6.cpp
//  DesertTour
//
//  Created by Cary on 15/12/26.
//
//

#include "Level_6.hpp"


#include "MainUI.hpp"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "Archery.hpp"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;



Scene* Level_6::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->setName("level_6");
    
    /** 吧物理世界设置成式调模式
     *  @2015/12/16 11:15
     */
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0 , -800.0f));
    auto layer = Level_6::create();
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Level_6::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visiblePoint = Director::getInstance()->getVisibleOrigin();
    
    auto root_level = CSLoader::createNode("Scene/LevelScene/Level_6.csb");
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
    Sprite* mainexit = root_level->getChildByName<Sprite*>("img_next_27");
    //旋转物体
    Sprite* rota = root_level->getChildByName<Sprite*>("gound_6_6");
    
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
    Sprite* gound_1 = root_level->getChildByName<Sprite*>("gound_5_5");
    Sprite* gound_2 = root_level->getChildByName<Sprite*>("gound_3_4");
    Sprite* gound_3 = root_level->getChildByName<Sprite*>("gound_3_3");
    Sprite* gound_4 = root_level->getChildByName<Sprite*>("gound_6_6");
    Sprite* gound_5 = root_level->getChildByName<Sprite*>("gound_1_1");
    ToolsFunction::setPhyDynamicSpriteBox(gound_2);
    ToolsFunction::setPhyDynamicSpriteBox(gound_3);
    ToolsFunction::setPhyDynamicSpriteBox(gound_4);
    ToolsFunction::setPhyDynamicSpriteBox(gound_5);
    
    //四个二维数组点 组成多边形
    Vec2 pa[6] = {
        Vec2(-gound_1->getContentSize().width/2,gound_1->getContentSize().height/2-72),
        Vec2(-gound_1->getContentSize().width/2,gound_1->getContentSize().height/2-2),
        Vec2(-gound_1->getContentSize().width/3+198 ,gound_1->getContentSize().height/2-2),
        Vec2(gound_1->getContentSize().width/2-2,-gound_1->getContentSize().height/2+81),
        Vec2(gound_1->getContentSize().width/2-2,-gound_1->getContentSize().height/2),
    };
    
    PhysicsBody* aa = PhysicsBody::createPolygon(pa, 5);
    aa->setDynamic(false);
    aa->setLinearDamping(5000.0f);
    gound_1->setPhysicsBody(aa);
    
    //按钮 1
    Button* b1 = root_level->getChildByName<Button*>("Button_1");
    Button* b2 = root_level->getChildByName<Button*>("Button_2");
    Button* b3 = root_level->getChildByName<Button*>("Button_3");
    Button* b4 = root_level->getChildByName<Button*>("Button_4");
    Sprite* b5 = root_level->getChildByName<Sprite*>("Button_5");
    //按钮问题
    Sprite* q1 = root_level->getChildByName<Sprite*>("question_1");
    Sprite* q2 = root_level->getChildByName<Sprite*>("question_2");
    Sprite* q3 = root_level->getChildByName<Sprite*>("question_3");
    Sprite* q4 = root_level->getChildByName<Sprite*>("question_4");
    Sprite* q5 = root_level->getChildByName<Sprite*>("question_5");
    //Sprite* q6 = root_level->getChildByName<Sprite*>("ar_50");
    //创建颜色按钮 4个按钮
    QuestionButton* btn_1 = QuestionButton::create();
    btn_1->setObj(b1);
    addChild(btn_1);
    QuestionButton* btn_2 = QuestionButton::create();
    btn_2->setObj(b2);
    addChild(btn_2);
    QuestionButton* btn_3 = QuestionButton::create();
    btn_3->setObj(b3);
    addChild(btn_3);
    QuestionButton* btn_4 = QuestionButton::create();
    btn_4->setObj(b4);
    addChild(btn_4);
    Btn_Standard* btn_5 = Btn_Standard::create();
    btn_5->setObj(b5);
    addChild(btn_5);
    //给按钮设置问题 4个问题
    Btn_QuestionSelect* qbtn_1 = Btn_QuestionSelect::create();
    qbtn_1->setObj(q1);
    qbtn_1->setIBtnMainUI(mainui, btn_1);
    addChild(qbtn_1);
    Btn_QuestionSelect* qbtn_2 = Btn_QuestionSelect::create();
    qbtn_2->setObj(q2);
    qbtn_2->setIBtnMainUI(mainui, btn_2);
    addChild(qbtn_2);
    Btn_QuestionSelect* qbtn_3 = Btn_QuestionSelect::create();
    qbtn_3->setObj(q3);
    qbtn_3->setIBtnMainUI(mainui, btn_3);
    addChild(qbtn_3);
    Btn_QuestionSelect* qbtn_4 = Btn_QuestionSelect::create();
    qbtn_4->setObj(q4);
    qbtn_4->setIBtnMainUI(mainui, btn_4);
    addChild(qbtn_4);
    Btn_QuestionSelect* qbtn_5 = Btn_QuestionSelect::create();
    qbtn_5->setObj(q5);
    qbtn_5->setIBtnMainUI(mainui, btn_5);
    addChild(qbtn_5);
    
    //4个按钮添加点击事件
    btn_1->getBtn()->addTouchEventListener([=](Ref* reft , Widget::TouchEventType type)
                                 {
                                     if (type == Widget::TouchEventType::ENDED) {

                                         if (ismove)
                                         {
                                             if (isAnim)
                                             {
                                                 //怪物
                                                 auto anim = CSLoader::createTimeline("Node/animation/L3_e.csb");
                                                 anim->gotoFrameAndPlay(0, 76, false);
                                                 root_level->runAction(anim);
                                                 anim->addFrameEndCallFunc(75, "a", [=]()
                                                                           {
                                                                               move_1 =move_1 + 37.5f;
                                                                               auto mt = MoveTo::create(0.8f, Vec2(gound_3->getPositionX(), move_1));
                                                                               gound_3->runAction(mt);
                                                                               ismove = true;
                                                                           });
                                                 isAnim = false;
                                                 ismove = false;
                                             }else{
                                                 if ((move_1+37.5f) < 66.0f) {
                                                     //move_1 = move_1+37.5f;
                                                     move_1 = -47.5f;
                                                     auto mt = MoveTo::create(0.8f, Vec2(gound_3->getPositionX(), move_1));
                                                     gound_3->runAction(mt);
                                                     ismove = true;
                                                 }
                                                 //怪物
                                                 auto anim = CSLoader::createTimeline("Node/animation/L3_e.csb");
                                                 anim->gotoFrameAndPlay(230, 265, false);
                                                 root_level->runAction(anim);
                                             }
                                             
                                         }
                                     }
                                 });
    btn_2->getBtn()->addTouchEventListener([=](Ref* reft,Widget::TouchEventType type)
                                 {
                                     if (type == Widget::TouchEventType::ENDED) {
                                         if (ismove)
                                         {
                                             if (isAnim)
                                             {
                                                 //怪物
                                                 auto anim = CSLoader::createTimeline("Node/animation/L3_e.csb");
                                                 anim->gotoFrameAndPlay(0, 76, false);
                                                 root_level->runAction(anim);
                                                 anim->addFrameEndCallFunc(75, "a", [=]()
                                                                           {
                                                                               move_1 =move_1 + 37.5f;
                                                                               auto mt = MoveTo::create(0.8f, Vec2(gound_3->getPositionX(), move_1));
                                                                               gound_3->runAction(mt);
                                                                               ismove = true;
                                                                           });
                                                 isAnim = false;
                                                 ismove = false;
                                             }else{
                                                 if ((move_1+37.5f) < 66.0f) {
                                                     //move_1 = move_1+37.5f;
                                                     move_1 = -10.0f;
                                                     auto mt = MoveTo::create(0.8f, Vec2(gound_3->getPositionX(), move_1));
                                                     gound_3->runAction(mt);
                                                     ismove = true;
                                                 }
                                                 //怪物
                                                 auto anim = CSLoader::createTimeline("Node/animation/L3_e.csb");
                                                 anim->gotoFrameAndPlay(230, 265, false);
                                                 root_level->runAction(anim);
                                             }
                                             
                                         }

                                     }
                                 });
    btn_3->getBtn()->addTouchEventListener([=](Ref* reft,Widget::TouchEventType type)
                                 {
                                     if (type == Widget::TouchEventType::ENDED) {
                                         if (ismove)
                                         {
                                             if (isAnim)
                                             {
                                                 //怪物
                                                 auto anim = CSLoader::createTimeline("Node/animation/L3_e.csb");
                                                 anim->gotoFrameAndPlay(0, 76, false);
                                                 root_level->runAction(anim);
                                                 anim->addFrameEndCallFunc(75, "a", [=]()
                                                                           {
                                                                               move_1 =move_1 + 37.5f;
                                                                               auto mt = MoveTo::create(0.8f, Vec2(gound_3->getPositionX(), move_1));
                                                                               gound_3->runAction(mt);
                                                                               ismove = true;
                                                                           });
                                                 isAnim = false;
                                                 ismove = false;
                                             }else{
                                                 if ((move_1+37.5f) < 66.0f) {
                                                     //move_1 = move_1+37.5f;
                                                     move_1 = 27.5f;
                                                     auto mt = MoveTo::create(0.8f, Vec2(gound_3->getPositionX(), move_1));
                                                     gound_3->runAction(mt);
                                                     ismove = true;
                                                 }
                                                 //怪物
                                                 auto anim = CSLoader::createTimeline("Node/animation/L3_e.csb");
                                                 anim->gotoFrameAndPlay(230, 265, false);
                                                 root_level->runAction(anim);
                                             }
                                             
                                         }

                                     }
                                 });
    btn_4->getBtn()->addTouchEventListener([=](Ref* reft,Widget::TouchEventType type)
                                 {
                                     if (type == Widget::TouchEventType::ENDED) {
                                         if (ismove)
                                         {
                                             if (isAnim)
                                             {
                                                 //怪物
                                                 auto anim = CSLoader::createTimeline("Node/animation/L3_e.csb");
                                                 anim->gotoFrameAndPlay(0, 76, false);
                                                 root_level->runAction(anim);
                                                 anim->addFrameEndCallFunc(75, "a", [=]()
                                                                           {
                                                                               move_1 =move_1 + 37.5f;
                                                                               auto mt = MoveTo::create(0.8f, Vec2(gound_3->getPositionX(), move_1));
                                                                               gound_3->runAction(mt);
                                                                               ismove = true;
                                                                           });
                                                 isAnim = false;
                                                 ismove = false;
                                             }else{
                                                 if ((move_1+37.5f) < 66.0f) {
                                                     //move_1 = move_1+37.5f;
                                                     move_1 = 65.0f;
                                                     auto mt = MoveTo::create(0.8f, Vec2(gound_3->getPositionX(), move_1));
                                                     gound_3->runAction(mt);
                                                     ismove = true;
                                                 }
                                                 //怪物
                                                 auto anim = CSLoader::createTimeline("Node/animation/L3_e.csb");
                                                 anim->gotoFrameAndPlay(230, 265, false);
                                                 root_level->runAction(anim);
                                             }
                                             
                                         }

                                     }
                                 });
    btn_5->getBtn()->addTouchEventListener([=](Ref* reft,Widget::TouchEventType type)
                                           {
                                               if (type == Widget::TouchEventType::ENDED) {
                                                   auto mov = RotateTo::create(0.8f, 29.22f);
                                                   rota->runAction(mov);
                                               }
                                           });
    
    //射箭动画
    Node* animanode = root_level->getChildByName<Node*>("FileNode_1");
    auto archery = CSLoader::createTimeline("Node/animation/anim_Archery.csb");
    archery->gotoFrameAndPlay(0, 155, true);
    root_level->runAction(archery);
    archery->addFrameEndCallFunc(95, "a", [=]()
                                 {
                                     Archery* a = Archery::create();
                                     a->setPosition(Vec2(animanode->getPositionX(), animanode->getPositionY()));
                                     addChild(a);
                                 });
    
    
    
    
    
    
    
    
    return true;
}





























