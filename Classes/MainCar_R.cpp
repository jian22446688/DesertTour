//
//  MainCar_R.cpp
//  DesertTour
//
//  Created by Cary on 15/12/16.
//
//

#include "MainCar_R.hpp"
#include "MainUI.hpp"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "math.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;

// on "init" you need to initialize your instance
bool MainCar_R::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    auto maincar_r = CSLoader::createNode("LayerUI/MainCar.csb");
    maincar_r->setName("MainCar_R");
    addChild(maincar_r);
    
    //获取车的组件
    maincarbody = maincar_r->getChildByName<Sprite*>("img_maincarbody_1");
    mainwheel_d = maincar_r->getChildByName<Sprite*>("img_maincar_d_2");
    mainwheel_x = maincar_r->getChildByName<Sprite*>("img_maincar_x_3");
    
    
    
    //添加更新方法
    scheduleUpdate();
    return true;
}

/** 场景进入函数
 *  @2015/12/16 09:40
 */
void MainCar_R::onEnter()
{
    Layer::onEnter();
    
    //设置点击事件
    auto ontouchevent = EventListenerTouchOneByOne::create();
    ontouchevent->onTouchBegan = CC_CALLBACK_2(MainCar_R::onTouchBegan, this);
    ontouchevent->setSwallowTouches(true);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ontouchevent, this);
    
    
    auto collisionevent = EventListenerPhysicsContact::create();
    collisionevent->onContactBegin = CC_CALLBACK_1(MainCar_R::onCollisionBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(collisionevent, this);
    
    
    
    mainwheel_d->setPosition(Vec2(maincarbody->getPosition().x-30,maincarbody->getPosition().y-28));
    mainwheel_x->setPosition(Vec2(maincarbody->getPosition().x+33,maincarbody->getPosition().y-38));
   /////
    PhysicsBody* phy_mainbody = PhysicsBody::createBox(Size(maincarbody->getContentSize().width-10,maincarbody->getContentSize().height-16));
    phy_mainbody->setTag(PHY_TAG_MAINCAR);
    phy_mainbody->setMass(1000.0f);
    phy_mainbody->setCategoryBitmask(0x01);
    phy_mainbody->setCollisionBitmask(0x01);
    phy_mainbody->setContactTestBitmask(0x01);
    phy_mainbody->setGroup(1);
    PhysicsBody* phy_mainwheel_d = PhysicsBody::createCircle(mainwheel_d->getContentSize().width/2-1);
    phy_mainwheel_d->setMass(1000.0f);
    phy_mainwheel_d->setLinearDamping(0.9f);
    phy_mainwheel_d->setCategoryBitmask(0x88);
    phy_mainwheel_d->setCollisionBitmask(0x01);
    phy_mainwheel_d->setContactTestBitmask(0x01);
    PhysicsBody* phy_mainwheel_x = PhysicsBody::createCircle(mainwheel_x->getContentSize().width/2-1);
    phy_mainwheel_x->setMass(1000.0f);
    phy_mainwheel_x->setLinearDamping(0.9f);
    phy_mainwheel_x->setCategoryBitmask(0x88);
    phy_mainwheel_x->setCollisionBitmask(0x01);
    phy_mainwheel_x->setContactTestBitmask(0x01);
    maincarbody->setPhysicsBody(phy_mainbody);
    mainwheel_d->setPhysicsBody(phy_mainwheel_d);
    mainwheel_x->setPhysicsBody(phy_mainwheel_x);
    

    PhysicsWorld* phy_world = this->getScene()->getPhysicsWorld();
    PhysicsJointPin* phyjointpin_x = PhysicsJointPin::construct(mainwheel_x->getPhysicsBody(), maincarbody->getPhysicsBody(), Vec2(maincarbody->getPosition().x+33,maincarbody->getPosition().y-38));
    phyjointpin_x->setCollisionEnable(false);
    phyjointpin_x->setEnable(true);
    
    PhysicsJointPin* phyjointpin_d = PhysicsJointPin::construct(mainwheel_d->getPhysicsBody(), maincarbody->getPhysicsBody(), Vec2(maincarbody->getPosition().x-30,maincarbody->getPosition().y-28));
    phyjointpin_d->setCollisionEnable(false);
    phyjointpin_d->setEnable(true);
    phy_world->addJoint(phyjointpin_x);
    phy_world->addJoint(phyjointpin_d);
}

/** 场景更新函数
 *  @2015/12/16 09:40
 */
void MainCar_R::update(float dt)
{
    //限制车的 旋转角度
    if (maincarbody->getRotation()>65.0f)
        maincarbody->setRotation(65.0f);
    if (maincarbody->getRotation()<-65.0f)
        maincarbody->setRotation(-65.0f);
}

/** 触摸屏幕开始
 *  @2015/12/16 09:40
 */
bool MainCar_R::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    Point tarPoint = maincarbody->convertToNodeSpace(touch->getLocation());
    Rect tarRect = Rect(0, 0, maincarbody->getContentSize().width, maincarbody->getContentSize().height);
    if (tarRect.containsPoint(tarPoint))
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AudioAssets/audio_home/gone.wav");
        if (!iscar)
        {
            setCarSpeed(getMainUI()->getCarSpeed_D(), getMainUI()->getCarSpeed_X(), true);
            iscar = true;
        }else{
            setCarSpeed(0.0f,0.0f, false);
            iscar = false;
        }
        return true;
    }
    return false;
}



/** 碰撞开始事件
 *  @2015/12/16 11:28
 */
bool MainCar_R::onCollisionBegin(const cocos2d::PhysicsContact& contact)
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
        
        if (bodyA->getTag() == 400001)
        {
            //碰到僵死了
            MainCar_R::kiLLCar_js();
        }
        else if(bodyA->getTag() == 400008)
        {
            //碰到了炸弹了
            MainCar_R::kiLLCar_zd();
        }
        else if(bodyA->getTag() == 100001)
        {
            //游戏结束的动画
            getMainUI()->GameOverActionPlayed(true);
            bodyB->getNode()->getParent()->getParent()->removeFromParent();
        }
        else if(bodyA->getTag() == 666666)
        {
            //播放游戏通关的动画
            getMainUI()->GameVictoryActionPlayed(true);
            MainCar_R::StopCar();
        }
        else if(bodyA->getTag() == 400010 || bodyA->getTag() == 400040)
        {
            //碰到了火把
            MainCar_R::kiLLCar_zd();
        }
        else if(bodyA->getTag() == 400020)
        {
            //死亡回调函数
            if (_carkilcallk){
                _carkilcallk();
            }
            //碰到了上吊怪物
            MainCar_R::StopCar();
            bodyA->getNode()->setVisible(false);
            maincarbody->setVisible(false);
            mainwheel_x->setVisible(false);
            mainwheel_d->setVisible(false);
            auto kill = CSLoader::createNode("Node/KillAnimaion/L5_upkill.csb");
            addChild(kill);
            kill->setPosition(Vec2(739.2f,666.0f));
            auto animkill = CSLoader::createTimeline("Node/KillAnimaion/L5_upkill.csb");
            animkill->gotoFrameAndPlay(0, 30, false);
            animkill->addFrameEndCallFunc(30, "m", [=]()
                                          {
                                              //游戏结束的动画
                                              getMainUI()->GameOverActionPlayed(true);
                                          });
            
            
            kill->runAction(animkill);
        }
        else if(bodyA->getTag() == 400030)
        {
            //碰到了L5木乃伊
            MainCar_R::StopCar();
            bodyA->getNode()->setVisible(false);
            //this->setVisible(false);
            //碰到僵死了
            MainCar_R::kiLLCar_js();
        }
        else if(bodyA->getTag() == PHY_TAG_SCORPION)
        {
            MainCar_R::StopCar();
            maincarbody->setVisible(false);
            mainwheel_x->setVisible(false);
            mainwheel_d->setVisible(false);
            maincarbody->getPhysicsBody()->setEnabled(false);
            mainwheel_x->getPhysicsBody()->setEnabled(false);
            mainwheel_d->getPhysicsBody()->setEnabled(false);
            
            schedule([=](float ft)
                     {
                         //游戏结束的动画
                         getMainUI()->GameOverActionPlayed(true);
                     }, 0.5f, "k");
        }
    }
    return true;
}


/** 车暂停
 *  @2015/12/22 17:05
 */
void MainCar_R::StopCar()
{
    PhysicsWorld* phyWorld =this->getScene()->getPhysicsWorld();
    PhysicsJointMotor* phyjointmotorbig = PhysicsJointMotor::construct(mainwheel_x->getPhysicsBody(), maincarbody->getPhysicsBody(), CAR_STOP);
    phyjointmotorbig->setCollisionEnable(false);
    PhysicsJointMotor* phyjointmotorsmall = PhysicsJointMotor::construct(mainwheel_d->getPhysicsBody(), maincarbody->getPhysicsBody(), CAR_STOP);
    phyjointmotorsmall->setCollisionEnable(false);
    phyWorld->addJoint(phyjointmotorbig);
    phyWorld->addJoint(phyjointmotorsmall);
    
}


/** 车暂停
 *  @2015/12/29 08:20
 */
void MainCar_R::setCarSpeed(float sd , float sx , bool iscaropen)
{
    iscar = iscaropen;
    
    PhysicsWorld* phyWorld =this->getScene()->getPhysicsWorld();
    PhysicsJointMotor* phyjointmotorbig = PhysicsJointMotor::construct(mainwheel_x->getPhysicsBody(), maincarbody->getPhysicsBody(), sx);
    phyjointmotorbig->setCollisionEnable(false);
    PhysicsJointMotor* phyjointmotorsmall = PhysicsJointMotor::construct(mainwheel_d->getPhysicsBody(), maincarbody->getPhysicsBody(), sd);
    phyjointmotorsmall->setCollisionEnable(false);
    phyWorld->addJoint(phyjointmotorbig);
    phyWorld->addJoint(phyjointmotorsmall);
}


/** 返回车的身体
 *  @2015/12/23 17:15
 */
Node* MainCar_R::getCarBoty()
{
    return maincarbody;
}

void MainCar_R::setBodyEnable()
{
    if (maincarbody->getPhysicsBody())
        maincarbody->getPhysicsBody()->setEnabled(false);
}

/** 设置主要UI实例
 *  @2015/12/23 15:40
 */
void MainCar_R::setMainUI(MainUI* mainui)
{
    MainCar_R::mainUiCar = mainui;
}

/** 获取主要UI实例
 *  @2015/12/24 15:40
 */
MainUI* MainCar_R::getMainUI()
{
    return MainCar_R::mainUiCar;
}

/** 设置车
 *  @2015/12/25 08:30
 */
void MainCar_R::setObj(Node* object)
{
    Vec2 vec = object->getPosition();
    this->setAnchorPoint(Vec2(0, 0));
    maincarbody->setPosition(vec);
    object->setVisible(false);
    mainwheel_d->setPosition(Vec2(maincarbody->getPosition().x-30,maincarbody->getPosition().y-28));
    mainwheel_x->setPosition(Vec2(maincarbody->getPosition().x+33,maincarbody->getPosition().y-38));
}

/** 死亡动画
 *  @2015/12/25 09:25
 */
void MainCar_R::kiLLCar_js()
{
    MainCar_R::StopCar();
    maincarbody->setVisible(false);
    mainwheel_x->setVisible(false);
    mainwheel_d->setVisible(false);
    maincarbody->getPhysicsBody()->setEnabled(false);
    mainwheel_x->getPhysicsBody()->setEnabled(false);
    mainwheel_d->getPhysicsBody()->setEnabled(false);
    //游戏结束的动画
    
    Node* carkill = CSLoader::createNode("Node/KillAnimaion/L1_js.csb");
    addChild(carkill);
    carkill->setPosition(Vec2(maincarbody->getPosition().x+52.0f, maincarbody->getPosition().y+5));
    auto killanim = CSLoader::createTimeline("Node/KillAnimaion/L1_js.csb");
    killanim->gotoFrameAndPlay(0, 70, false);
    carkill->runAction(killanim);
    killanim->addFrameEndCallFunc(70, "ab", [=]()
                                  {
                                      //调用死亡界面
                                      getMainUI()->GameOverActionPlayed(true);
                                  });
}

/** 死亡动画
 *  @2015/12/29 19:25
 */
void MainCar_R::kiLLCar_zd()
{
    MainCar_R::StopCar();
    maincarbody->setVisible(false);
    mainwheel_x->setVisible(false);
    mainwheel_d->setVisible(false);
    maincarbody->getPhysicsBody()->setEnabled(false);
    mainwheel_x->getPhysicsBody()->setEnabled(false);
    mainwheel_d->getPhysicsBody()->setEnabled(false);
    //游戏结束的动画
    
    Node* carkill = CSLoader::createNode("Node/KillAnimaion/carfirekill.csb");
    addChild(carkill);
    carkill->setPosition(Vec2(maincarbody->getPosition().x, maincarbody->getPosition().y+10));
    auto killanim = CSLoader::createTimeline("Node/KillAnimaion/carfirekill.csb");
    killanim->gotoFrameAndPlay(0, 81, false);
    carkill->runAction(killanim);
    killanim->addFrameEndCallFunc(81, "aaa", [=]()
                                  {
                                      //调用死亡界面
                                      getMainUI()->GameOverActionPlayed(true);
                                      
                                  });
    
}

/** 调取游戏结束界面
 *  @2015/12/25 10:05
 */
void MainCar_R::PalyGameOver()
{
    getMainUI()->GameOverActionPlayed(true);
    this->removeFromParent();
}

/** 转向
 *  @2015/12/25 10:05
 */
void MainCar_R::CarTurn()
{
    this->setScaleX(-this->getScaleX());
}


/** 获取 右 车的位置
 *  @2015/01/05 10:15
 */
Node* MainCar_R::getCarNode()
{
    return maincarbody;
}


/** 获取 右 车的位置
 *  @2015/01/05 19:40
 */
bool MainCar_R::isCarOpen()
{
    return iscar;
}

/** 设置车死亡的回调函数
 *  @2015/01/011 10:40
 */
void MainCar_R::addCarkillcallk(const MainCar_R::carKillCallk& carcalk)
{
    this->_carkilcallk = carcalk;
}

void MainCar_R::setChange(Node* ojb)
{
    _chenge = ojb;
}


/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/



bool MainCar_L::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto maincar_l = CSLoader::createNode("LayerUI/MainCar_L.csb");
    maincar_l->setName("MainCar_L");
    addChild(maincar_l);
    
    //获取车的组件
    maincarbody = maincar_l->getChildByName<Sprite*>("img_maincarbody_1");
    mainwheel_d = maincar_l->getChildByName<Sprite*>("img_maincar_d_2");
    mainwheel_x = maincar_l->getChildByName<Sprite*>("img_maincar_x_3");
    
    
    //添加更新方法
    scheduleUpdate();
    return true;
}


/** 场景进入函数
 *  @2015/01/04 17:10
 */
void MainCar_L::onEnter()
{
    Layer::onEnter();
    
    //设置点击事件
    auto ontouchevent = EventListenerTouchOneByOne::create();
    ontouchevent->onTouchBegan = CC_CALLBACK_2(MainCar_L::onTouchBegan, this);
    ontouchevent->setSwallowTouches(true);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ontouchevent, this);
    
    
    auto collisionevent = EventListenerPhysicsContact::create();
    collisionevent->onContactBegin = CC_CALLBACK_1(MainCar_L::onCollisionBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(collisionevent, this);
    
    
    
    mainwheel_d->setPosition(Vec2(maincarbody->getPosition().x+30,maincarbody->getPosition().y-28));
    mainwheel_x->setPosition(Vec2(maincarbody->getPosition().x-32,maincarbody->getPosition().y-38));
    PhysicsBody* phy_mainbody = PhysicsBody::createBox(Size(maincarbody->getContentSize().width-8,maincarbody->getContentSize().height-16));
    phy_mainbody->setTag(PHY_TAG_MAINCAR);
    phy_mainbody->setMass(1000.0f);
    phy_mainbody->setCategoryBitmask(0x01);
    phy_mainbody->setCollisionBitmask(0x01);
    phy_mainbody->setContactTestBitmask(0x01);
    PhysicsBody* phy_mainwheel_d = PhysicsBody::createCircle(mainwheel_d->getContentSize().width/2-1);
    phy_mainwheel_d->setMass(1000.0f);
    phy_mainwheel_d->setCategoryBitmask(0x88);
    phy_mainwheel_d->setCollisionBitmask(0x01);
    phy_mainwheel_d->setContactTestBitmask(0x01);
    PhysicsBody* phy_mainwheel_x = PhysicsBody::createCircle(mainwheel_x->getContentSize().width/2-1);
    phy_mainwheel_x->setMass(1000.0f);
    phy_mainwheel_x->setCategoryBitmask(0x88);
    phy_mainwheel_x->setCollisionBitmask(0x01);
    phy_mainwheel_x->setContactTestBitmask(0x01);
    maincarbody->setPhysicsBody(phy_mainbody);
    mainwheel_d->setPhysicsBody(phy_mainwheel_d);
    mainwheel_x->setPhysicsBody(phy_mainwheel_x);
    
    //maincarbody->getPhysicsBody()->setDynamic(false);
    
    
    PhysicsWorld* phy_world = this->getScene()->getPhysicsWorld();
    PhysicsJointPin* phyjointpin_x = PhysicsJointPin::construct(mainwheel_x->getPhysicsBody(), maincarbody->getPhysicsBody(), Vec2(maincarbody->getPosition().x-32,maincarbody->getPosition().y-38));
    
    
    phyjointpin_x->setCollisionEnable(false);
    phyjointpin_x->setEnable(true);
    PhysicsJointPin* phyjointpin_d = PhysicsJointPin::construct(mainwheel_d->getPhysicsBody(), maincarbody->getPhysicsBody(), Vec2(maincarbody->getPosition().x+30,maincarbody->getPosition().y-28));
    
    phyjointpin_d->setCollisionEnable(false);
    phyjointpin_d->setEnable(true);
    phy_world->addJoint(phyjointpin_x);
    phy_world->addJoint(phyjointpin_d);
    
    
}


/** 场景更新函数
 *  @2015/01/04 17:10
 */
void MainCar_L::update(float dt)
{
    //限制车的 旋转角度
    if (maincarbody->getRotation()>65.0f)
        maincarbody->setRotation(65.0f);
    
    if (maincarbody->getRotation()<-65.0f)
        maincarbody->setRotation(-65.0f);
}


/** 触摸屏幕开始
 *  @2015/01/04 17:10
 */
bool MainCar_L::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
    Point tarPoint = maincarbody->convertToNodeSpace(touch->getLocation());
    Rect tarRect = Rect(0, 0, maincarbody->getContentSize().width, maincarbody->getContentSize().height);
    if (tarRect.containsPoint(tarPoint))
    {
        if (!iscar)
        {
            setCarSpeed(getMainUI()->getCarSpeed_D(), getMainUI()->getCarSpeed_X(), true);
            iscar = true;
        }
        else
        {
            setCarSpeed(0.0f,0.0f, false);
            iscar = false;
        }
        return false;
    }
    return false;
}

/** 碰撞开始事件
 *  @2015/01/04 17:10
 */
bool MainCar_L::onCollisionBegin(const cocos2d::PhysicsContact& contact)
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
        
        if (bodyA->getTag() == 400001)
        {
            //碰到僵死了
            MainCar_L::kiLLCar_js();
        }
        else if(bodyA->getTag() == 400008)
        {
            //碰到了炸弹了
            MainCar_L::kiLLCar_zd();
        }
        else if(bodyA->getTag() == 100001)
        {
            //游戏结束的动画
            getMainUI()->GameOverActionPlayed(true);
            bodyB->getNode()->getParent()->getParent()->removeFromParent();
        }
        else if(bodyA->getTag() == 666666)
        {
            //播放游戏通关的动画
            getMainUI()->GameVictoryActionPlayed(true);
            MainCar_L::StopCar();
        }
        else if(bodyA->getTag() == 400010 || bodyA->getTag() == 400040)
        {
            //碰到了火把
            MainCar_L::kiLLCar_zd();
        }
        else if(bodyA->getTag() == 400020)
        {
            //死亡回调函数
            if (_carkilcallk){
                _carkilcallk();
            }
            //碰到了上吊怪物
            MainCar_L::StopCar();
            bodyA->getNode()->setVisible(false);
            maincarbody->setVisible(false);
            mainwheel_x->setVisible(false);
            mainwheel_d->setVisible(false);
            auto kill = CSLoader::createNode("Node/KillAnimaion/L5_upkill.csb");
            addChild(kill);
            kill->setPosition(Vec2(739.2f,666.0f));
            auto animkill = CSLoader::createTimeline("Node/KillAnimaion/L5_upkill.csb");
            animkill->gotoFrameAndPlay(0, 30, false);
            animkill->addFrameEndCallFunc(30, "m", [=]()
                                          {
                                              //游戏结束的动画
                                              getMainUI()->GameOverActionPlayed(true);
                                          });
            
            //死亡回调函数
            if (_carkilcallk){
                _carkilcallk();
            }
            kill->runAction(animkill);
            
            
        }
        else if(bodyA->getTag() == 400030)
        {
            //碰到了L5木乃伊
            MainCar_L::StopCar();
            bodyA->getNode()->setVisible(false);
            //this->setVisible(false);
            //碰到僵死了
            MainCar_L::kiLLCar_js();
        }
    }

    return true;
}



/** 车暂停
 *  @2015/12/22 17:05
 */
void MainCar_L::StopCar()
{
    PhysicsWorld* phyWorld =this->getScene()->getPhysicsWorld();
    PhysicsJointMotor* phyjointmotorbig = PhysicsJointMotor::construct(mainwheel_x->getPhysicsBody(), maincarbody->getPhysicsBody(), CAR_STOP);
    phyjointmotorbig->setCollisionEnable(false);
    PhysicsJointMotor* phyjointmotorsmall = PhysicsJointMotor::construct(mainwheel_d->getPhysicsBody(), maincarbody->getPhysicsBody(), CAR_STOP);
    phyjointmotorsmall->setCollisionEnable(false);
    phyWorld->addJoint(phyjointmotorbig);
    phyWorld->addJoint(phyjointmotorsmall);
    
}


/** 车暂停
 *  @2015/12/29 08:20
 */
void MainCar_L::setCarSpeed(float sd , float sx , bool iscaropen)
{
    iscar = iscaropen;
    PhysicsWorld* phyWorld =this->getScene()->getPhysicsWorld();
    PhysicsJointMotor* phyjointmotorbig = PhysicsJointMotor::construct(mainwheel_x->getPhysicsBody(), maincarbody->getPhysicsBody(), sx);
    phyjointmotorbig->setCollisionEnable(false);
    PhysicsJointMotor* phyjointmotorsmall = PhysicsJointMotor::construct(mainwheel_d->getPhysicsBody(), maincarbody->getPhysicsBody(), sd);
    phyjointmotorsmall->setCollisionEnable(false);
    phyWorld->addJoint(phyjointmotorbig);
    phyWorld->addJoint(phyjointmotorsmall);
}


/** 返回车的身体
 *  @2015/12/23 17:15
 */
Node* MainCar_L::getCarBoty()
{
    return maincarbody;
}


void MainCar_L::setBodyEnable()
{
    if (maincarbody->getPhysicsBody())
        maincarbody->getPhysicsBody()->setEnabled(false);
}


/** 设置主要UI实例
 *  @2015/12/23 15:40
 */
void MainCar_L::setMainUI(MainUI* mainui)
{
    MainCar_L::mainUiCar = mainui;
}

/** 获取主要UI实例
 *  @2015/12/24 15:40
 */
MainUI* MainCar_L::getMainUI()
{
    return MainCar_L::mainUiCar;
}

/** 设置车
 *  @2015/12/25 08:30
 */
void MainCar_L::setObj(Node* object)
{
    Vec2 vec = object->getPosition();
    //this->setAnchorPoint(Vec2(0, 0));
    maincarbody->setPosition(vec);
    object->setVisible(false);
    
}

/** 死亡动画
 *  @2015/12/25 09:25
 */
void MainCar_L::kiLLCar_js()
{
    MainCar_L::StopCar();
    maincarbody->setVisible(false);
    mainwheel_x->setVisible(false);
    mainwheel_d->setVisible(false);
    maincarbody->getPhysicsBody()->setEnabled(false);
    mainwheel_x->getPhysicsBody()->setEnabled(false);
    mainwheel_d->getPhysicsBody()->setEnabled(false);
    //游戏结束的动画
    
    Node* carkill = CSLoader::createNode("Node/KillAnimaion/L1_js.csb");
    addChild(carkill);
    carkill->setPosition(Vec2(maincarbody->getPosition().x-52.0f, maincarbody->getPosition().y+5));
    auto killanim = CSLoader::createTimeline("Node/KillAnimaion/L1_js.csb");
    killanim->gotoFrameAndPlay(0, 70, false);
    carkill->runAction(killanim);
    killanim->addFrameEndCallFunc(70, "ab", [=]()
                                  {
                                      //调用死亡界面
                                      getMainUI()->GameOverActionPlayed(true);
                                  });
    carkill->setScaleX(-carkill->getScaleX());
}

/** 死亡动画
 *  @2015/12/29 19:25
 */
void MainCar_L::kiLLCar_zd()
{
    MainCar_L::StopCar();
    maincarbody->setVisible(false);
    mainwheel_x->setVisible(false);
    mainwheel_d->setVisible(false);
    
    maincarbody->getPhysicsBody()->setEnabled(false);
    mainwheel_x->getPhysicsBody()->setEnabled(false);
    mainwheel_d->getPhysicsBody()->setEnabled(false);
    //游戏结束的动画
    
    Node* carkill = CSLoader::createNode("Node/KillAnimaion/carfirekill.csb");
    addChild(carkill);
    carkill->setPosition(Vec2(maincarbody->getPosition().x, maincarbody->getPosition().y+10));
    auto killanim = CSLoader::createTimeline("Node/KillAnimaion/carfirekill.csb");
    killanim->gotoFrameAndPlay(0, 81, false);
    carkill->runAction(killanim);
    killanim->addFrameEndCallFunc(81, "aaa", [=]()
                                  {
                                      //调用死亡界面
                                      getMainUI()->GameOverActionPlayed(true);
                                      
                                  });
    
}

/** 调取游戏结束界面
 *  @2015/12/25 10:05
 */
void MainCar_L::PalyGameOver()
{
    getMainUI()->GameOverActionPlayed(true);
    this->removeFromParent();
}



/** 获取 左 车的位置
 *  @2015/01/05 10:15
 */
Node* MainCar_L::getCarNode()
{
    return maincarbody;
}

/** 获取 车是否启动
 *  @2015/01/05 19:40
 */
bool MainCar_L::isCarOpen()
{
    return iscar;
}


/** 设置车死亡的回调函数
 *  @2015/01/011 10:40
 */
void MainCar_L::addCarkillcallk(const MainCar_L::carKillCallk& carcalk)
{
    this->_carkilcallk = carcalk;
}




















