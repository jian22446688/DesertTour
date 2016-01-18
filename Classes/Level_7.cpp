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
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
    addChild(maincar_r,10);
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
     gound_7 = root_level->getChildByName<Sprite*>("l7_gound_7_8");
    Sprite* gound_9 = root_level->getChildByName<Sprite*>("Button_1_0_0");
    Sprite* gound_10 = root_level->getChildByName<Sprite*>("Button_1_0");
    gound_11 = root_level->getChildByName<Sprite*>("l7_gound_7_8");
    gound_5->setRotation(90.0f);
    btn_2->getBtn()->addTouchEventListener([=](Ref* reft,Widget::TouchEventType type)
                                           {
                                               if (type == Widget::TouchEventType::ENDED) {
                                                   btn_2->getBtn()->loadTextureNormal("DesertUI/Level/level_7/animation/btnopen0002.png");
                                                   auto ms = RotateTo::create(3.2f, 24.0f);
                                                   gound_3->runAction(ms);
                                               }
                                           });
    
    btn_3->getBtn()->addTouchEventListener([=](Ref* reft,Widget::TouchEventType type)
                                           {
                                               if (type == Widget::TouchEventType::ENDED) {
                                                   if (gound_5->getRotation() >= 0.0f && gound_5->getRotation() <= 80.0f) {
                                                       btn_3->getBtn()->loadTextureNormal("DesertUI/Level/level_7/animation/btnrl0002.png");
                                                       auto sx = RotateTo::create(1.0f,90.0f);
                                                       gound_5->runAction(sx);
                                                   }else{
                                                       btn_3->getBtn()->loadTextureNormal("DesertUI/Level/level_7/animation/btnrl0001.png");
                                                       auto sx = RotateTo::create(1.0f,0.0f);
                                                       gound_5->runAction(sx);
                                                   }
                                               }
                                           });
    Sprite* g1 = root_level->getChildByName<Sprite*>("Button_1_1");
    Sprite* g2 = root_level->getChildByName<Sprite*>("Button_1_2");
    Sprite* g3 = root_level->getChildByName<Sprite*>("Button_1_3");
    Scorpion_gw* scor = Scorpion_gw::create();
    scor->setObj(g3);
    scor->setMovePosition(g1, g2, 26.2f);
    addChild(scor);
    Btn_QuestionSelect* qbtn_1 = Btn_QuestionSelect::create();
    qbtn_1->setObj(q1);
    qbtn_1->setIBtnMainUI(mainui, scor);
    addChild(qbtn_1);
    mainui->setMovePosition(gound_10, gound_9,true);
    scheduleUpdate();
    return true;
}

void Level_7::update(float ft)
{
    schedule([=](float ft)
    {
        Archery* a = Archery::create();
        a->setPosition(gound_7->getPosition());
        addChild(a);
        a->setTexture(gound_11->getTexture());
        
    }, 3.0f, "a");
}



























