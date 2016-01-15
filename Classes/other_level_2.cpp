//
//  other_level_2.cpp
//  DesertTour
//
//  Created by Cary on 15/12/25.
//
//

#include "other_level_2.hpp"


#include "MainUI.hpp"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;


// on "init" you need to initialize your instance
bool other_level_2::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    return true;
}

/*************************************************************************/

Bombed* Bombed::createSprite(Sprite* target)
{
    Bombed* bom = new Bombed();
    bom->setPosition(target->getPosition());
    //设置Anchor点
    bom->setAnchorPoint(target->getAnchorPoint());
    bom->setPosition(target->getPosition());
    bom->setScaleX(target->getScaleX());
    bom->setScaleY(target->getScaleY());
    bom->setRotation(target->getRotation());
    target->setVisible(false);
    
    if (bom !=nullptr)
    {
        bom->autorelease();
        return bom;
    }
    CC_SAFE_DELETE(bom);
    return nullptr;
}


bool Bombed::init()
{
    if (!Sprite::init()) {
        return false;
    }
    //预加载爆炸音效
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("AudioAssets/audio_level/l2_bome.mp3");
    auto node = CSLoader::createNode("Node/animation/bomb.csb");
    addChild(node);
    
//    brie = CSLoader::createNode("Node/level_animation/l2_gound.csb");
//    brie->setPosition(Vec2(123,-198));
//    addChild(brie);
//    brie->setVisible(false);
    
    Texture2D* tu = node->getChildByName<Sprite*>("sax0001_15")->getTexture();
    this->setTexture(tu);
    this->setVisible(false);
    
    auto collisionlistener = EventListenerPhysicsContact::create();
    collisionlistener->onContactBegin = CC_CALLBACK_1(Bombed::onCollisionBegin,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(collisionlistener, this);
    
    return true;
}

void Bombed::setObj(Node* obje)
{
    //设置Anchor点
    this->setAnchorPoint(cocos2d::Vec2(0,0));
    this->setPosition(obje->getPosition());
    this->setScaleX(obje->getScaleX());
    this->setScaleY(obje->getScaleY());
    this->setRotation(obje->getRotation());
    obje->setVisible(false);
}


/** 爆炸物体
 *  @2015/01/04 10:50
 */
void Bombed::setBomb(Sprite* obj)
{
    bire = obj;
}

/** 爆炸桥物体
 *  @2015/01/04 11:00
 */
void Bombed::setBombbri(Sprite* obj)
{
    phybire = obj;
}


/** 问题回答
 *  @2015/12/29 14:21
 */
void Bombed::AnswerPassed(bool ispass)
{
    
    
}

/** 控制的按钮是否启用
 *  @2015/12/29 14:21
 */
void Bombed::IsBtnEnable(bool isbtn)
{
    PhysicsBody* phys = PhysicsBody::createBox(Size(80,40));
    phys->setPositionOffset(Vec2(10, -60));
    phys->setTag(400008);
    
    //设置触发 掩码
    phys->setContactTestBitmask(0x01);
    phys->setCollisionBitmask(0x02);
    phys->setDynamic(false);
    this->setPhysicsBody(phys);
    
    //设置当前的物体不可见
    this->setVisible(true);
    
}




/** 碰撞开始事件
 *  @2015/12/29 17:10
 */
bool Bombed::onCollisionBegin(const cocos2d::PhysicsContact& contact)
{
    
    PhysicsBody* bodyA = contact.getShapeA()->getBody();
    PhysicsBody* bodyB = contact.getShapeB()->getBody();
    PhysicsBody* temp =nullptr;
    if(bodyA->getTag() == 400008)
    {
        temp = bodyB;
        bodyB = bodyA;
        bodyA = temp;
    }
    
    if(bodyB->getTag() == 400008)
    {
        startBomb();
    }
    return false;
}

/** 爆炸
 *  @2015/12/29 17:10
 */
void Bombed::startBomb()
{
    if (brie !=NULL) {
        brie->removeFromParent();
    }
    if (phybire !=NULL) {
        phybire->setVisible(false);
        phybire->removeFromParent();
    }
    auto node = CSLoader::createTimeline("Node/animation/bomb.csb");
    node->gotoFrameAndPlay(0, 46, false);
    this->runAction(node);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AudioAssets/audio_level/l2_bome.mp3");
    
    node->addFrameEndCallFunc(45, "a", [=]()
                              {
                                  this->removeFromParent();
                              });
    
    //auto brieanim = CSLoader::createTimeline("Node/level_animation/l2_gound.csb");
    ///brieanim->gotoFrameAndPlay(0, 43, false);
    //this->runAction(brieanim);
    
}



/*************************************************************************/


bool Brigde::init()
{
    if (!Sprite::init())
    {
        return false;
    }
   return true;
}

void Brigde::setObj(Sprite* obje)
{
    //设置贴图
    //this->setTexture(obje->getTexture());
    //设置Anchor点
    //this->setAnchorPoint(cocos2d::Vec2(0,0));
    this->setPosition(obje->getPosition());
    this->setScaleX(obje->getScaleX());
    this->setScaleY(obje->getScaleY());
    this->setRotation(obje->getRotation());
    obje->setVisible(false);
}

/** 问题回答
 *  @2015/01/04 09:15
 */
void Brigde::PlayBomb()
{
    
    
    
}

/*************************************************************************/

bool Monster::init()
{
    if (!Sprite::init()){
        return false;
    }
    return true;
}

/** 问题回答
 *  @2015/01/04 09:15
 */
void Monster::setObj(Node* obje)
{
    //设置Anchor点
    this->setAnchorPoint(cocos2d::Vec2(0,0));
    this->setPosition(obje->getPosition());
    this->setScaleX(obje->getScaleX());
    this->setScaleY(obje->getScaleY());
    this->setRotation(obje->getRotation());
    obje->setVisible(false);
}


/** 动画帧事件
 *  @2015/01/04 09:15
 */
void Monster::addFrame_1(frameEvent_1& fram1){
    this->_frameEvent_1 = fram1;
}
void Monster::addFrame_2(frameEvent_2& fram2){
    this->_frameEvent_2 = fram2;
}
void Monster::addFrame_3(frameEvent_3& fram3){
    this->_frameEvent_3 = fram3;
}
void Monster::addFrame_4(frameEvent_4& fram4){
    this->_frameEvent_4 = fram4;
}

/** 问题回答
 *  @2015/12/28 15:41
 */
void Monster::AnswerPassed(bool ispass)
{
    
}

/** 控制的按钮是否启用
 *  @2015/12/28 15:41
 */
void Monster::IsBtnEnable(bool isbtn)
{
    
}





















































