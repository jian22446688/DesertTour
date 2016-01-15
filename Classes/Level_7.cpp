//
//  Level_7.cpp
//  DesertTour
//
//  Created by Cary on 15/12/26.
//
//

#include "Level_7.hpp"


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



Scene* Level_7::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->setName("level_7");
    
    /** 吧物理世界设置成式调模式
     *  @2015/12/16 11:15
     */
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    scene->getPhysicsWorld()->setGravity(Vec2(0 , -800.0f));
    auto layer = Level_7::create();
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Level_7::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visiblePoint = Director::getInstance()->getVisibleOrigin();
    
    auto root_level = CSLoader::createNode("Scene/LevelScene/Level_7.csb");
    root_level->setTag(100001);
    this->addChild(root_level);
    
    
    //设置物理 空心世界
    PhysicsBody* psworld =PhysicsBody::createEdgeBox(Size(visibleSize.width * 1.5f,visibleSize.height),PHYSICSBODY_MATERIAL_DEFAULT,2);
    psworld->setCategoryBitmask(0x01);
    psworld->setCollisionBitmask(0x01);
    psworld->setContactTestBitmask(0x01);
    root_level->setPhysicsBody(psworld);
    
    //火把
    Node* hb1 = root_level->getChildByName<Node*>("FileNode_3");
    //火把
    Node* hb2 = root_level->getChildByName<Node*>("FileNode_3_0");
    fire_x* fhb1 = fire_x::create();
    fhb1->setObject(hb1);
    addChild(fhb1);
    fire_x* fhb2 = fire_x::create();
    fhb2->setObject(hb2);
    addChild(fhb2);
    
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
    Sprite* gound_1 = root_level->getChildByName<Sprite*>("l7_gound_1");
    Sprite* gound_3 = root_level->getChildByName<Sprite*>("l7_gound_3");
    Sprite* gound_4 = root_level->getChildByName<Sprite*>("l7_gound_4");
    Sprite* gound_5 = root_level->getChildByName<Sprite*>("l7_gound_5");
    Sprite* gound_6 = root_level->getChildByName<Sprite*>("l7_gound_6");
    ToolsFunction::setPhyDynamicSpriteBox(gound_1);
    ToolsFunction::setPhyDynamicSpriteBox(gound_3);
    ToolsFunction::setPhyDynamicSpriteBox(gound_4);
    ToolsFunction::setPhyDynamicSpriteBox(gound_6);
    gound_3->getPhysicsBody()->setLinearDamping(0.9f);
    gound_4->getPhysicsBody()->setLinearDamping(0.9f);
    
    //四个二维数组点 组成多边形
    Vec2 pa[3] = {
        Vec2(-gound_5->getContentSize().width/2,-gound_5->getContentSize().height/2),
        Vec2(-gound_5->getContentSize().width/2+2,gound_5->getContentSize().height/2-2),
        Vec2(-gound_5->getContentSize().width/3+120 ,-gound_5->getContentSize().height/2)};
    auto aa = PhysicsBody::createPolygon(pa, 3);
    aa->setCategoryBitmask(0x03);
    aa->setCollisionBitmask(0x03);
    aa->setContactTestBitmask(0x03);
    aa->setDynamic(false);
    aa->setLinearDamping(5000.0f);
    gound_5->setPhysicsBody(aa);
    
    
    Sprite* gound_7 = root_level->getChildByName<Sprite*>("l7_gound_7_8");
    
    //按钮 1
    Button* b1 = root_level->getChildByName<Button*>("Button_1");
    Button* b2 = root_level->getChildByName<Button*>("Button_2");
    Button* b3 = root_level->getChildByName<Button*>("Button_3");
    //    Button* b4 = root_level->getChildByName<Button*>("Button_4");
    //    Sprite* b5 = root_level->getChildByName<Sprite*>("Button_5");
    //按钮问题
    Sprite* q1 = root_level->getChildByName<Sprite*>("question_1");
    Sprite* q2 = root_level->getChildByName<Sprite*>("question_2");
    Sprite* q3 = root_level->getChildByName<Sprite*>("question_3");
    //    Sprite* q4 = root_level->getChildByName<Sprite*>("question_4");
    //    Sprite* q5 = root_level->getChildByName<Sprite*>("question_5");
    //Sprite* q6 = root_level->getChildByName<Sprite*>("ar_50");
    //创建颜色按钮 4个按钮
    Btn_Standard* btn_1 = Btn_Standard::create();
    btn_1->setObj(b1);
    addChild(btn_1);
    QuestionButton* btn_2 = QuestionButton::create();
    btn_2->setObj(b2);
    addChild(btn_2);
    QuestionButton* btn_3 = QuestionButton::create();
    btn_3->setObj(b3);
    addChild(btn_3);
    //    QuestionButton* btn_4 = QuestionButton::create();
    //    btn_4->setObj(b4);
    //    addChild(btn_4);
    //    Btn_Standard* btn_5 = Btn_Standard::create();
    //    btn_5->setObj(b5);
    //    addChild(btn_5);
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
    //    Btn_QuestionSelect* qbtn_4 = Btn_QuestionSelect::create();
    //    qbtn_4->setObj(q4);
    //    qbtn_4->setIBtnMainUI(mainui, btn_4);
    //    addChild(qbtn_4);
    //    Btn_QuestionSelect* qbtn_5 = Btn_QuestionSelect::create();
    //    qbtn_5->setObj(q5);
    //    qbtn_5->setIBtnMainUI(mainui, btn_5);
    //    addChild(qbtn_5);
    Sprite* gound_9 = root_level->getChildByName<Sprite*>("Button_1_0_0");
    
    Sprite* gound_10 = root_level->getChildByName<Sprite*>("Button_1_0");
    Sprite* gound_11 = root_level->getChildByName<Sprite*>("l7_gound_7_8");
    
    maincar_r->setChange(gound_9);
    
    
    btn_1->getBtn()->addTouchEventListener([=](Ref* reft,Widget::TouchEventType type)
                                           {
                                               if (type == Widget::TouchEventType::ENDED) {
                                                   Archery* a = Archery::create();
                                                   a->setPosition(gound_7->getPosition());
                                                   addChild(a);
                                                   a->setTexture(gound_11->getTexture());
                                                   //maincar_r->setObj(gound_9);
                                               }
                                           });
    btn_2->getBtn()->addTouchEventListener([=](Ref* reft,Widget::TouchEventType type)
                                           {
                                               if (type == Widget::TouchEventType::ENDED) {
                                                   btn_2->getBtn()->loadTextureNormal("DesertUI/Level/level_7/animation/btnopen0002.png");
                                                   auto ms = RotateTo::create(0.8f, 24.0f);
                                                   gound_3->runAction(ms);
                                               }
                                           });
    
    btn_3->getBtn()->addTouchEventListener([=](Ref* reft,Widget::TouchEventType type)
                                           {
                                               if (type == Widget::TouchEventType::ENDED) {
                                                   btn_3->getBtn()->loadTextureNormal("DesertUI/Level/level_7/animation/btnrl0002.png");
                                                   auto sx = ScaleTo::create(0.9f, 1.0f, 1.0f);
                                                   gound_5->runAction(sx);
                                               }
                                           });
    
    
    CarChangePosition* ccp = CarChangePosition::create();
    ccp->setObj(gound_10);
    //ccp->setChangePosition(maincar_r, gound_9);
    addChild(ccp);
    ccp->addEvent([=]()
                  {
                      maincar_r->setObj(gound_9);
                  });
    
    
    
    
    
    
    return true;
}















