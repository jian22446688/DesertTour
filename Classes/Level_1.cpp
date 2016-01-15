//
//  Level_1.cpp
//  DesertTour
//
//  Created by Cary on 15/12/15.
//
//

#include "Level_1.hpp"
#include "MainUI.hpp"


#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;


Scene* Level_1::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->setName("level_1");
    
    
    /** 吧物理世界设置成式调模式
     *  @2015/12/16 11:15
     */
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    scene->getPhysicsWorld()->setGravity(Vec2(0 , -800.0f));
    
    // 'layer' is an autorelease object
    auto layer = Level_1::create();
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Level_1::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto root_level_1 = CSLoader::createNode("Scene/LevelScene/Level_1.csb");
    root_level_1->setTag(100001);
    this->addChild(root_level_1);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visiblePoint = Director::getInstance()->getVisibleOrigin();
    
    
    //获取车的位置
    Sprite* mycar = root_level_1->getChildByName<Sprite*>("btn_010001_64_1_1");
    //创建车的实例
    auto maincar = MainCar_R::create();
    maincar->setObj(mycar);
    //创建主要UI界面
    mainui = MainUI::create();
    //添加车到UI里
    mainui->setCar_R(maincar);
    mainui->setTag(PHY_TAG_MANUI);
    maincar->setMainUI(mainui);
    this->addChild(maincar);
    addChild(mainui,3000);
    
    //素材火把添加；
    auto hb1 = root_level_1->getChildByName<Sprite*>("FileNode_2_0");
    auto hb2 = root_level_1->getChildByName<Sprite*>("FileNode_2");
    
    //添加一个火把
    auto ohb1 = fire_x::create();
    ohb1->setObject(hb1);
    root_level_1->addChild(ohb1);
    //添加二个火把
    auto ohb2 = fire_x::create();
    ohb2->setObject(hb2);
    root_level_1->addChild(ohb2);
    
    
    //添加第一个怪物
    auto gw1 = root_level_1->getChildByName<Sprite*>("FileNode_5");
    auto gw2 = root_level_1->getChildByName<Sprite*>("btn_010001_64");
    auto gw3 = root_level_1->getChildByName<Sprite*>("btn_010001_64_0");
    auto gw = guaiwu_js::create();
    gw->setGuanwu(gw1);
    gw->setDelete_js(gw);
    gw->setMovePosition(gw2, gw3, 28.0f);
    addChild(gw);
    
    //添加第二个怪物
    auto gw21 = root_level_1->getChildByName<Sprite*>("FileNode_5_0");
    auto gw22 = root_level_1->getChildByName<Sprite*>("btn_010001_64_1");
    auto gw23 = root_level_1->getChildByName<Sprite*>("btn_010001_64_1_0");
    auto gwgw = guaiwu_js::create();
    gwgw->setGuanwu(gw21);
    gwgw->setDelete_js(gwgw);
    gwgw->setMovePosition(gw22, gw23, 20.0f);
    addChild(gwgw);
    
    auto sprite1 = root_level_1->getChildByName<Sprite*>("img_ground_01");
    auto sprite2 = root_level_1->getChildByName<Sprite*>("img_ground_02");
    ToolsFunction::setPhySpriteBox(sprite1);
    ToolsFunction::setPhySpriteBox(sprite2);
    
    auto sprite4 = root_level_1->getChildByName<Sprite*>("img_next_6");
    ToolsFunction::setPhyContactSpriteBox(sprite4);
    sprite4->getPhysicsBody()->setTag(PHY_TAG_FINISHLEVEL);
    
    
    //设置世界世界空心刚体
    PhysicsBody* psworld =PhysicsBody::createEdgeBox(visibleSize*2,PHYSICSBODY_MATERIAL_DEFAULT,2);
    psworld->setCategoryBitmask(0x01);
    psworld->setCollisionBitmask(0x01);
    psworld->setContactTestBitmask(0x01);
    root_level_1->setPhysicsBody(psworld);
    
    //添加问题按钮
    auto a1 = root_level_1->getChildByName<Sprite*>("btn_010001_1");
    auto a2 = root_level_1->getChildByName<Sprite*>("btn_010001_2");
    auto a3 = root_level_1->getChildByName<Sprite*>("btn_010001_3");
    
    auto qq1 = root_level_1->getChildByName<Sprite*>("anim_question0001_12");
    auto qq2 = root_level_1->getChildByName<Sprite*>("anim_question0001_13");
    auto qq3 = root_level_1->getChildByName<Sprite*>("anim_question0001_14");
    
    //控制物体按钮 1；
    Btn_Standard* btn1 = Btn_Standard::create();
    btn1->setName("btn_1");
    btn1->setObj(a1);
    btn1->getBtn()->addTouchEventListener(CC_CALLBACK_2(Level_1::onBtnClick, this));
    addChild(btn1,29);
    
    //控制物体按钮 2；
    Btn_Standard* btn2 = Btn_Standard::create();
    btn2->setName("btn_2");
    btn2->setObj(a2);
    btn2->getBtn()->addTouchEventListener(CC_CALLBACK_2(Level_1::onBtnClick, this));
    addChild(btn2,29);
    
    //控制物体按钮 3；
    Btn_Standard* btn3 = Btn_Standard::create();
    btn3->setName("btn_3");
    btn3->setObj(a3);
    btn3->getBtn()->addTouchEventListener(CC_CALLBACK_2(Level_1::onBtnClick, this));
    addChild(btn3,29);
    
    //出问题按钮 1；
    Btn_QuestionSelect* ques1 = Btn_QuestionSelect::create();
    ques1->setObj(qq1);
    ques1->setIBtnMainUI(mainui, btn1);
    addChild(ques1,30);
    
    //出问题按钮 2；
    Btn_QuestionSelect* ques2 = Btn_QuestionSelect::create();
    ques2->setObj(qq2);
    ques2->setIBtnMainUI(mainui, btn2);
    addChild(ques2,30);
    
    //出问题按钮 3；
    Btn_QuestionSelect* ques3 = Btn_QuestionSelect::create();
    ques3->setObj(qq3);
    ques3->setIBtnMainUI(mainui, btn3);
    addChild(ques3,30);
    
    
    //创建悬浮器
    auto x = root_level_1->getChildByName<Sprite*>("FileNode_4");
    auto x1 = root_level_1->getChildByName<Sprite*>("FileNode_4_0");
    
    log("初始位置  %f  %f",x1->getPosition().x,x1->getPosition().y);
    
    xd1 = other_level_1::create();
    xd1->setObj(x);
    this->addChild(xd1);
    xd2 = other_level_1::create();
    xd2->setObj(x1);
    this->addChild(xd2);
    
    //设置两个悬浮器 一个可以用。另一个不可以用
    xd1->getNo()->getPhysicsBody()->setEnabled(true);
    xd2->getNo()->getPhysicsBody()->setEnabled(false);
    xd1->setVisible(true);
    xd2->setVisible(false);

    
    //设置弹跳
    auto tan = root_level_1->getChildByName<Sprite*>("tur0001_91");
    os = objSpring::create();
    os->setObj(tan);
    addChild(os);
    
    Layer* grlayer = Layer::create();
    auto ground = root_level_1->getChildByName<Sprite*>("img_ground_02");
    grlayer->addChild(ground);
    addChild(grlayer);
    this->scheduleUpdate();
    
    return true;
}

/** 场景进入函数
 *  @2015/12/16 09:40
 */
void Level_1::onEnter()
{
    Layer::onEnter();
//    auto collisionevent = EventListenerPhysicsContact::create();
//    collisionevent->onContactBegin = CC_CALLBACK_1(Level_1::onCollisionBegin, this);
//    collisionevent->onContactPostSolve = CC_CALLBACK_2(Level_1::onContactPostSolve, this);
//    collisionevent->onContactPreSolve = CC_CALLBACK_2(Level_1::onContactPreSolve, this);
//    collisionevent->onContactSeparate = CC_CALLBACK_1(Level_1::onContactSeparate, this);
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(collisionevent, this);
    
}


/** 场景更新函数
 *  @2015/12/16 09:40
 */
void Level_1::update(float dt)
{
}


void Level_1::onBtnClick(Ref* reft,Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AudioAssets/audio_home/gone.wav");
        auto s = dynamic_cast<Button*>(reft)->getParent()->getParent()->getName();
        if (s=="btn_010001_1")
        {
            if (!xd1->isVisible())
            {
                xd1->getNo()->getPhysicsBody()->setEnabled(true);
                xd2->getNo()->getPhysicsBody()->setEnabled(false);
                xd1->setVisible(true);
                xd2->setVisible(false);
            }
        }
        else if(s=="btn_010001_2")
        {
            //TODO  添加 刚体的 速度 力
            os->addForce();
        }
        else if(s=="btn_010001_3")
        {
            if (!xd2->isVisible())
            {
                xd1->getNo()->getPhysicsBody()->setEnabled(false);
                xd2->getNo()->getPhysicsBody()->setEnabled(true);
                xd1->setVisible(false);
                xd2->setVisible(true);
            }
        }
        log("当期的按钮名字 %s",s.c_str());
        ismove = !ismove;
    }
}

/** 碰撞开始事件
 *  @2015/12/16 11:28
 */
bool Level_1::onCollisionBegin(const cocos2d::PhysicsContact& contact)
{
    PhysicsBody* bodyA = contact.getShapeA()->getBody();
    PhysicsBody* bodyB = contact.getShapeB()->getBody();
    PhysicsBody* temp =nullptr;
    //log("A:%d B:%d",bodyA->getTag(),bodyB->getTag());
    if(bodyA->getTag() == 555555)
    {
        temp = bodyB;
        bodyB = bodyA;
        bodyA = temp;
        
    }

    if(bodyB->getTag() == 555555)
    {
        //log("A:%d",bodyA->getTag());
        //  100001     物理世界
        //  555555     主要车的
        //  300001     悬浮的物体
        //  400001     第一关的怪物
        //  600001     弹簧的物体
        
        
        if (bodyA->getTag()== 400001)
        {
            MainCar_R* car =(MainCar_R*)bodyB->getNode()->getParent()->getParent();
            //car->removeFromParent();
            car->setBodyEnable();
        }
        
        switch (bodyA->getTag()) {
            case 400001:
                log("第一关的怪物");
                bodyB->setEnabled(false);

                break;
                
            case 300001:
                log("悬浮的物体");
                break;
            
            case 600001:
                log("弹簧的物体");
                break;
                
            default:
                break;
        }
    }

    return true;
}

/** 碰撞开始事件
 *  @2015/12/16 09:40
 */
bool Level_1::onContactPreSolve(const cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve)
{
    
   // log("碰到了 弹簧 bbbbbbb");
    
    
    return false;
}

/** 碰撞中。。。
 *  @2015/12/16 09:40
 */
void Level_1::onContactPostSolve(const cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve)
{
//    // 获得碰撞的精灵
//    Node* spriteA = contact.getShapeA()->getBody()->getNode();
//    Node* spriteB = contact.getShapeB()->getBody()->getNode();
//    if (spriteA && spriteB)
//    {
//        
//    }
//    //log("碰到了 弹簧 aaaaaa");
    
}

/** 碰撞离开
 *  @2015/12/16 09:40
 */
void Level_1::onContactSeparate(const cocos2d::PhysicsContact& contact)
{
//    string phyname =  contact.getShapeA()->getBody()->getNode()->getName();
//    int phyname1 =  contact.getShapeA()->getBody()->getNode()->getTag();
//    
//    int phyname2 =  contact.getShapeA()->getBody()->getTag();
//    if (300001 ==phyname2)
//    {
//        iscarfukong = false;
//        log("退出了 炫富器 %d",phyname2);
//    }
//    else if (600001 ==phyname2)
//    {
//        os->setObjClear();
//        
//        log("退出 弹簧 %d",phyname2);
//    }
//    
}











