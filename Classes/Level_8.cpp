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
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
    root_level = CSLoader::createNode("Scene/LevelScene/Level_8.csb");
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
    Sprite* gound_14 = root_level->getChildByName<Sprite*>("l8_gound_14_1");
    //////////////////////////////////////////////////////////////////////
    Sprite* gound_8 = root_level->getChildByName<Sprite*>("l8_gound_8_1");
    Sprite* gound_9 = root_level->getChildByName<Sprite*>("l8_gound_9_1");
    Sprite* gound_10 = root_level->getChildByName<Sprite*>("l8_gound_10_1");
    Sprite* gound_11 = root_level->getChildByName<Sprite*>("l8_gound_11_1");
    Sprite* gound_12 = root_level->getChildByName<Sprite*>("l8_gound_12_1");
    Sprite* gound_13 = root_level->getChildByName<Sprite*>("l8_gound_13_1");
    ToolsFunction::setPhyDynamicSpriteBox(gound_1);
    ToolsFunction::setPhyDynamicSpriteBox(gound_2);
    ToolsFunction::setPhyDynamicSpriteBox(gound_3);
    ToolsFunction::setPhyDynamicSpriteBox(gound_4);
    ToolsFunction::setPhyDynamicSpriteBox(gound_5);
    ToolsFunction::setPhyDynamicSpriteBox(gound_6);
    ToolsFunction::setPhyDynamicSpriteBox(gound_7);
    ToolsFunction::setPhyDynamicSpriteBox(gound_14);
    //四个二维数组点 组成多边形
    Vec2 pa[3] = {
        Vec2(-gound_13->getContentSize().width/2,-gound_13->getContentSize().height/2),
        Vec2(-gound_13->getContentSize().width/2+2,gound_13->getContentSize().height/2-2),
        Vec2(-gound_13->getContentSize().width/3+120 ,-gound_13->getContentSize().height/2)};
    auto aa = PhysicsBody::createPolygon(pa, 3);
//    aa->setCategoryBitmask(0x03);
//    aa->setCollisionBitmask(0x03);
//    aa->setContactTestBitmask(0x03);
    aa->setDynamic(false);
    //aa->setLinearDamping(5000.0f);
    gound_13->setPhysicsBody(aa);
    //按钮 1
    Button* b1 = root_level->getChildByName<Button*>("Button_1");
    Button* b2 = root_level->getChildByName<Button*>("Button_2");
    Button* b3 = root_level->getChildByName<Button*>("Button_3");
    Sprite* b4 = root_level->getChildByName<Sprite*>("Button_4");
    Sprite* b5 = root_level->getChildByName<Sprite*>("Button_5");
    //按钮问题
    Sprite* q1 = root_level->getChildByName<Sprite*>("question_1");
    Sprite* q2 = root_level->getChildByName<Sprite*>("question_2");
    Sprite* q3 = root_level->getChildByName<Sprite*>("question_3");
    Sprite* q4 = root_level->getChildByName<Sprite*>("question_4");
    Sprite* q5 = root_level->getChildByName<Sprite*>("question_5");
    //创建颜色按钮 4个按钮
    QuestionButton* btn_1 = QuestionButton::create();
    btn_1->setObj(b1);
    addChild(btn_1,5);
    QuestionButton* btn_2 = QuestionButton::create();
    btn_2->setObj(b2);
    addChild(btn_2,5);
    QuestionButton* btn_3 = QuestionButton::create();
    btn_3->setObj(b3);
    addChild(btn_3,5);
    Btn_Standard* btn_4 = Btn_Standard::create();
    btn_4->setObj(b4);
    addChild(btn_4,5);
    Btn_Standard* btn_5 = Btn_Standard::create();
    btn_5->setObj(b5);
    addChild(btn_5,5);
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
    qbtn_3->setIBtnMainUI(mainui, btn_3);
    addChild(qbtn_3,8);
    Btn_QuestionSelect* qbtn_4 = Btn_QuestionSelect::create();
    qbtn_4->setObj(q4);
    qbtn_4->setIBtnMainUI(mainui, btn_4);
    addChild(qbtn_4,8);
    Btn_QuestionSelect* qbtn_5 = Btn_QuestionSelect::create();
    qbtn_5->setObj(q5);
    qbtn_5->setIBtnMainUI(mainui, btn_5);
    addChild(qbtn_5,8);
    ParticleSystemQuad* qp5 = root_level->getChildByName<ParticleSystemQuad*>("Particle_2");
    PhysicsBody* qpphy = PhysicsBody::createBox(Size(200.0f,10.0f));
    qpphy->setPositionOffset(Vec2(-100.0f, 0.0f));
    //火的碰撞掩码
    qpphy->setTag(PHY_TAG_KILL_FIRE);
    //设置触发 掩码
    qpphy->setContactTestBitmask(0x01);
    qpphy->setCollisionBitmask(0x02);
    qpphy->setDynamic(false);
    qp5->setPhysicsBody(qpphy);
    qp6 = root_level->getChildByName<ParticleSystemQuad*>("Particle_1");
    PhysicsBody* qpphy6 = PhysicsBody::createBox(Size(60.0f,60.0f));
    qpphy6->setPositionOffset(Vec2(0.0f, 0.0f));
    //火的碰撞掩码
    qpphy6->setTag(PHY_TAG_KILL_FIRE);
    //设置触发 掩码
    qpphy6->setContactTestBitmask(0x01);
    qpphy6->setCollisionBitmask(0x02);
    qpphy6->setDynamic(true);
    qpphy6->setRotationEnable(false);
    qp6->setPhysicsBody(qpphy6);
    //车变换位置
    mainui->setMovePosition(gound_8, gound_9,true);
    //添加怪物
    Scorpion_gw* scor = Scorpion_gw::create();
    scor->setObj(gound_11);
    scor->setMovePosition(gound_10,gound_12, 26.2f);
    addChild(scor);
    //弹簧
    Sprite* th = root_level->getChildByName<Sprite*>("tur0001_91");
    objSpring* ths = objSpring::create();
    ths->setPhysicsTag(600002);
    ths->setObj(th);
    addChild(ths);
    //弹簧
    Sprite* th1 = root_level->getChildByName<Sprite*>("tur0001_91_1");
    objSpring* ths1 = objSpring::create();
    ths1->setPhysicsTag(600003);
    ths1->setObj(th1);
    addChild(ths1);
    Layer* ly = Layer::create();
    ly->addChild(gound_7);
    addChild(ly);
    //冰块
    Node* iceoo = root_level->getChildByName<Node*>("FileNode_2");
    iceoo->setContentSize(Size(80.0f,200.0f));
    PhysicsBody* phyice = PhysicsBody::createBox(Size(80.0f,200.0f));
    phyice->setTag(PHY_TAG_ICE);
    phyice->setPositionOffset(Vec2(-30.0f, -80.0f));
    phyice->setDynamic(false);
    phyice->setCategoryBitmask(0x03);
    phyice->setCollisionBitmask(0x03);
    phyice->setContactTestBitmask(0x03);
    iceoo->setPhysicsBody(phyice);
    Layer* iceot = Layer::create();
    iceot->addChild(iceoo);
    addChild(iceot,12);
    auto coillsEvent = EventListenerPhysicsContact::create();
    coillsEvent->onContactBegin = CC_CALLBACK_1(Level_8::onCollisionBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(coillsEvent, this);
    //按钮添加事件
    btn_1->getBtn()->addTouchEventListener([=](Ref* reft, Widget::TouchEventType type)
                                           {
                                               if (type == Widget::TouchEventType::ENDED) {
                                                   btn_1->getBtn()->loadTextureNormal("DesertUI/Level/level_7/animation/btnopen0002.png");
                                                   auto tato = MoveTo::create(1.0f, Vec2(469.0f, gound_2->getPosition().y));
                                                   gound_2->runAction(tato);
                                               }
                                           });
    btn_2->getBtn()->addTouchEventListener([=](Ref* reft, Widget::TouchEventType type)
                                           {
                                               if (type == Widget::TouchEventType::ENDED) {
                                                   if (gound_13->getRotation() >= 0.0f && gound_13->getRotation() <= 80.0f) {
                                                       btn_2->getBtn()->loadTextureNormal("DesertUI/Level/level_8/btn_fire0001.png");
                                                       auto sx = RotateTo::create(1.0f,90.0f);
                                                       gound_13->runAction(sx);
                                                   }else{
                                                       btn_2->getBtn()->loadTextureNormal("DesertUI/Level/level_8/btn_fire0002.png");
                                                       auto sx = RotateTo::create(1.0f,0.0f);
                                                       gound_13->runAction(sx);
                                                   }
                                               }
                                           });
    btn_3->getBtn()->addTouchEventListener([=](Ref* reft, Widget::TouchEventType type)
                                           {
                                               if (type == Widget::TouchEventType::ENDED) {
                                                   btn_3->getBtn()->loadTextureNormal("DesertUI/Level/level_7/animation/btnopen0002.png");
                                                   auto rotato = RotateTo::create(3.0f, 28.0f);
                                                   gound_6->runAction(rotato);
                                               }
                                           });
    btn_4->getBtn()->addTouchEventListener([=](Ref* reft, Widget::TouchEventType type)
                                           {
                                               if (type == Widget::TouchEventType::ENDED) {
                                                   ths1->addForce(Vec2(-260.0f, 300.0f));
                                               }
                                           });
    btn_5->getBtn()->addTouchEventListener([=](Ref* reft, Widget::TouchEventType type)
                                           {
                                               if (type == Widget::TouchEventType::ENDED) {
                                                   ths->addForce(Vec2(-260.0f, 300.0f));
                                               }
                                           });
    
    Sprite* carmask = root_level->getChildByName<Sprite*>("img_maincarbody_17_0");
    carmask->setVisible(false);
    masklayer = Layer::create();
    masklayer->setContentSize(carmask->getContentSize());
    masklayer->addChild(carmask);
    addChild(masklayer,10);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event){
        /* get the target bind by the touch event listener */
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
        /* judge if the touch position inside the bounding box of sprite */
        if (target->getBoundingBox().containsPoint(pos))
        {
            /* set the opacity of the sprite */
            //target->setOpacity(100);
            return true;
        }
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, carmask);
    return true;
}

/** 碰撞开始事件
 *  @2015/01/19 14:14
 */
bool Level_8::onCollisionBegin(const cocos2d::PhysicsContact& contact)
{
    PhysicsBody* bodyA = contact.getShapeA()->getBody();
    PhysicsBody* bodyB = contact.getShapeB()->getBody();
    PhysicsBody* temp =nullptr;
    //log("A:%d B:%d",bodyA->getTag(),bodyB->getTag());
    if(bodyA->getTag() == 600050)
    {
        temp = bodyB;
        bodyB = bodyA;
        bodyA = temp;
    }
    if(bodyB->getTag() == 600050)
    {
        if (bodyA->getTag() == 400010) {
            log("火碰到冰块了  》》》》》》》》》》》》》");
            auto anim_iceo = CSLoader::createTimeline("Node/level_animation/l8_ice.csb");
            anim_iceo->gotoFrameAndPlay(0, 70, false);
            masklayer->removeFromParent();
            root_level->runAction(anim_iceo);
        }
    }
    return false;
}

















