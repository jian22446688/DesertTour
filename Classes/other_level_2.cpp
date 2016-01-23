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
        phybire->getPhysicsBody()->setEnabled(false);
        //phybire->removeFromParent();
    }
    auto node = CSLoader::createTimeline("Node/animation/bomb.csb");
    node->gotoFrameAndPlay(0, 46, false);
    this->runAction(node);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AudioAssets/audio_level/l2_bome.mp3");
    
    node->addFrameEndCallFunc(46, "a", [=]()
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


/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/*******************************************************************/

bool Scorpion_gw::init()
{
    if (!Sprite::init()) {
        return false;
    }
    animNode = CSLoader::createNode("Node/level_animation/l7_gw.csb");
    addChild(animNode);
    guaiwu = CSLoader::createTimeline("Node/level_animation/l7_gw.csb");
    ChangeStatus(ScorpionType::Walk);
    this->setContentSize(Size(60, 40));
    PhysicsBody* phybody = PhysicsBody::createBox(this->getContentSize());
    phybody->setPositionOffset(Vec2(-40, -130));
    phybody->setTag(PHY_TAG_SCORPION);
    phybody->setMass(3000);
    phybody->setRotationEnable(false);
    phybody->setCategoryBitmask(0x01);
    phybody->setCollisionBitmask(0x02);
    phybody->setContactTestBitmask(0x01);
    phybody->setDynamic(true);
    this->setPhysicsBody(phybody);
    auto colsiionEvent = EventListenerPhysicsContact::create();
    colsiionEvent->onContactBegin = CC_CALLBACK_1(Scorpion_gw::onCollisionBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(colsiionEvent, this);
    scheduleUpdate();
    return true;
}

void Scorpion_gw::update(float ft)
{
    if (isMove){
        if (iskeyl) {
            if (this->getPositionX() > moveA.x){
                this->setPositionX((this->getPositionX()-ft*Scorpion_gw::movespeed));
            }else{
                iskeyl = false;
                iskeyr = true;
                this->setScaleX(-this->getScaleX());
                this->getPhysicsBody()->setPositionOffset(Vec2(80, -130));
            }
        }
        if (iskeyr){
            if (this->getPositionX() <moveB.x){
                this->setPositionX((this->getPositionX()+ft*Scorpion_gw::movespeed));
            }else{
                iskeyl = true;
                iskeyr = false;
                this->setScaleX(-this->getScaleX());
                this->getPhysicsBody()->setPositionOffset(Vec2(-50, -130));
            }
        }
    }
}

void Scorpion_gw::setObj(Node* obj)
{
    this->setPosition(Vec2(obj->getPosition().x, obj->getPosition().y+105.0f));
    obj->setVisible(false);
}

void Scorpion_gw::setMovePosition(Node* objeA,Node* objeB ,float movespeed)
{
    isMove = true;
    this->movespeed = movespeed;
    moveA =objeA->getPosition();
    moveB =objeB->getPosition();
    objeA->setVisible(false);
    objeB->setVisible(false);
}

/** 更换状态
 *  @2015/01/15 09:40
 */
void Scorpion_gw::ChangeStatus(ScorpionType type)
{
    if (type == ScorpionType::Walk){
        guaiwu->gotoFrameAndPlay(0, 25, true);
        animNode->runAction(guaiwu);
        isMove = true;
    }else if (type == ScorpionType::Attack){
        guaiwu->gotoFrameAndPlay(35, 65, false);
        animNode->runAction(guaiwu);
        isMove = false;
    }else if (type == ScorpionType::Sleep){
        guaiwu->gotoFrameAndPlay(70, 150, true);
        animNode->runAction(guaiwu);
        isMove = false;
    }
}

/** 问题回答
 *  @2015/01/15 09:40
 */
void Scorpion_gw::AnswerPassed(bool ispass)
{
    
}

/** 控制的按钮是否启用
 *  @2015/01/15 09:40
 */
void Scorpion_gw::IsBtnEnable(bool isbtn)
{
    this->getPhysicsBody()->setEnabled(false);
    ChangeStatus(ScorpionType::Sleep);
}

/** 碰撞开始事件
 *  @2015/01/15 09:40
 */
bool Scorpion_gw::onCollisionBegin(const cocos2d::PhysicsContact& contact)
{
    PhysicsBody* bodyA = contact.getShapeA()->getBody();
    PhysicsBody* bodyB = contact.getShapeB()->getBody();
    PhysicsBody* bodythis = this->getPhysicsBody();
    if (bodythis == bodyA || bodythis == bodyB)
    {
        if (bodyA->getTag() == PHY_TAG_MAINCAR || bodyB->getTag() == PHY_TAG_MAINCAR) {
            ChangeStatus(ScorpionType::Attack);
            log("Attack");
        }else if (bodyA->getTag() == PHY_TAG_ARCHERY_L5){
            
        }
    }
    return true;
}

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/*******************************************************************/





bool Guard_gu::init()
{
    if (!Sprite::init()) {
        return false;
    }
    animNode = CSLoader::createNode("Node/level_animation/l9_guard.csb");
    addChild(animNode);
    guaiwu = CSLoader::createTimeline("Node/level_animation/l9_guard.csb");
    ChangeStatus(ScorpionType::Walk);
    this->setContentSize(Size(100.0f, 80.0f));
    PhysicsBody* phybody = PhysicsBody::createBox(this->getContentSize());
    phybody->setPositionOffset(Vec2(-50.0f, -40.0f));
    phybody->setTag(PHY_TAG_GUARD);
    phybody->setMass(3000);
    phybody->setRotationEnable(false);
    phybody->setCategoryBitmask(0x01);
    phybody->setCollisionBitmask(0x02);
    phybody->setContactTestBitmask(0x01);
    phybody->setDynamic(true);
    phybody->setGravityEnable(false);
    this->setPhysicsBody(phybody);
    auto colsiionEvent = EventListenerPhysicsContact::create();
    colsiionEvent->onContactBegin = CC_CALLBACK_1(Guard_gu::onCollisionBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(colsiionEvent, this);
    scheduleUpdate();
    return true;
}

void Guard_gu::update(float ft)
{
    if (isMove){
        if (iskeyl) {
            if (this->getPositionX() > moveA.x){
                this->setPositionX((this->getPositionX()-ft*Guard_gu::movespeed));
            }else{
                iskeyl = false;
                iskeyr = true;
                this->setScaleX(-this->getScaleX());
                this->getPhysicsBody()->setPositionOffset(Vec2(50.0f, -40.0f));
            }
        }
        if (iskeyr){
            if (this->getPositionX() <moveB.x){
                this->setPositionX((this->getPositionX()+ft*Guard_gu::movespeed));
            }else{
                iskeyl = true;
                iskeyr = false;
                this->setScaleX(-this->getScaleX());
                this->getPhysicsBody()->setPositionOffset(Vec2(-50.0f, -40.0f));
            }
        }
    }
}

void Guard_gu::setObj(Node* obj)
{
    this->setPosition(Vec2(obj->getPosition().x, obj->getPosition().y));
    obj->setVisible(false);
}

void Guard_gu::setMovePosition(Node* objeA,Node* objeB ,float movespeed)
{
    isMove = true;
    this->movespeed = movespeed;
    moveA =objeA->getPosition();
    moveB =objeB->getPosition();
    objeA->setVisible(false);
    objeB->setVisible(false);
}

/** 更换状态
 *  @2015/01/15 09:40
 */
void Guard_gu::ChangeStatus(ScorpionType type)
{
    if (type == ScorpionType::Walk){
        guaiwu->play("walk", true);
        animNode->runAction(guaiwu);
        isMove = true;
    }else if (type == ScorpionType::Attack){
        guaiwu->play("attack", false);
        animNode->runAction(guaiwu);
        isMove = false;
    }else if (type == ScorpionType::Sleep){
        guaiwu->gotoFrameAndPlay(70, 150, true);
        animNode->runAction(guaiwu);
        isMove = false;
    }
}

/** 碰撞开始事件
 *  @2015/01/15 09:40
 */
bool Guard_gu::onCollisionBegin(const cocos2d::PhysicsContact& contact)
{
    PhysicsBody* bodyA = contact.getShapeA()->getBody();
    PhysicsBody* bodyB = contact.getShapeB()->getBody();
    PhysicsBody* bodythis = this->getPhysicsBody();
    if (bodythis == bodyA || bodythis == bodyB)
    {
        if (bodyA->getTag() == PHY_TAG_MAINCAR || bodyB->getTag() == PHY_TAG_MAINCAR) {
            ChangeStatus(ScorpionType::Attack);
            
            if (bodyA->getTag() == PHY_TAG_MAINCAR) {
                guaiwu->addFrameEndCallFunc(65, "a", [=]()
                                            {
                                                bodyA->setVelocity(Vec2(-5000.0f, 1000.0f));
                                            });
            }
            if (bodyB->getTag() == PHY_TAG_MAINCAR) {
                guaiwu->addFrameEndCallFunc(65, "a", [=]()
                                            {
                                                bodyB->setVelocity(Vec2(-5000.0f, 1000.0f));
                                            });
            }
            
            log("Attack");
        }
    }
    return true;
}




/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/*******************************************************************/





bool Boos_gu::init()
{
    if (!Sprite::init()) {
        return false;
    }
    animNode = CSLoader::createNode("Node/KillAnimaion/l10_boos.csb");
    addChild(animNode);
    //guaiwu = CSLoader::createTimeline("Node/KillAnimaion/l10_boos.csb");
    //设置初始Hp
    this->_initHp = getHp();
    this->setContentSize(Size(200.0f, 120.0f));
    _loadingShow = LoadingBar::create("DesertUI/home/loadingbar.png");
    _loadingShow->setContentSize(Size(100.0f,20.0f));
    _loadingShow->setPosition(Vec2(0, this->getContentSize().height / 2 + 40));
    _loadingShow->setDirection(cocos2d::ui::LoadingBar::Direction::LEFT);
    _loadingShow->setPercent(100);
    addChild(_loadingShow,80);
    _stext = Text::create();
    _stext->setFontSize(13.0f);
    _stext->setPosition(Vec2(0, this->getContentSize().height / 2 + 36));
    _stext->setColor(Color3B(255, 255, 255));
    _stext->setString("100000");
    addChild(_stext,81);
    ChangeStatus(ScorpionType::Walk);
    PhysicsBody* phybody = PhysicsBody::createBox(this->getContentSize());
    phybody->setPositionOffset(Vec2(-100.0f, -60.0f));
    phybody->setTag(PHY_TAG_GUARD);
    phybody->setMass(3000);
    phybody->setRotationEnable(false);
    phybody->setCategoryBitmask(0x01);
    phybody->setCollisionBitmask(0x02);
    phybody->setContactTestBitmask(0x01);
    phybody->setDynamic(true);
    phybody->setGravityEnable(false);
    this->setPhysicsBody(phybody);
    auto colsiionEvent = EventListenerPhysicsContact::create();
    colsiionEvent->onContactBegin = CC_CALLBACK_1(Boos_gu::onCollisionBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(colsiionEvent, this);
    scheduleUpdate();
    
    return true;
}

void Boos_gu::update(float ft)
{
    if (isMove){
        if (iskeyl) {
            if (this->getPositionX() > moveA.x){
                this->setPositionX((this->getPositionX()-ft*Boos_gu::movespeed));
            }else{
                iskeyl = false;
                iskeyr = true;
                this->setScaleX(-this->getScaleX());
                this->getPhysicsBody()->setPositionOffset(Vec2(100.0f, -60.0f));
                _stext->setScaleX(this->getScaleX());
                _loadingShow->setScaleX(this->getScaleX());
            }
        }
        if (iskeyr){
            if (this->getPositionX() <moveB.x){
                this->setPositionX((this->getPositionX()+ft*Boos_gu::movespeed));
            }else{
                iskeyl = true;
                iskeyr = false;
                this->setScaleX(-this->getScaleX());
                this->getPhysicsBody()->setPositionOffset(Vec2(-100.0f, -60.0f));
                _stext->setScaleX(this->getScaleX());
                _loadingShow->setScaleX(this->getScaleX());
            }
        }
    }
    
    //等待执行；
    schedule([=](float ft)
             {
                 if (scotype != ScorpionType::Wait) {
                     //ChangeStatus(ScorpionType::Wait);
                 }
                 
                 schedule([=](float ft)
                          {
                              //ChangeStatus(ScorpionType::Walk);
                          }, 3.0f, "a");
                 //log("我执行了一次、、、、、、、、、、");
             }, 6.0f, "a");
}

void Boos_gu::setObj(Node* obj)
{
    this->setPosition(Vec2(obj->getPosition().x, obj->getPosition().y));
    obj->setVisible(false);
}

void Boos_gu::setMovePosition(Node* objeA,Node* objeB ,float movespeed)
{
    isMove = true;
    this->movespeed = movespeed;
    moveA =objeA->getPosition();
    moveB =objeB->getPosition();
    objeA->setVisible(false);
    objeB->setVisible(false);
}

/** 更换状态
 *  @2015/01/15 09:40
 */
void Boos_gu::ChangeStatus(ScorpionType type)
{
    scotype = type;
    animNode->stopAllActions();
    auto guaiwu = CSLoader::createTimeline("Node/KillAnimaion/l10_boos.csb");
    if (type == ScorpionType::Walk){
        guaiwu->gotoFrameAndPlay(160, 195, true);
        //guaiwu->play("walk", true);
        animNode->runAction(guaiwu);
        isMove = true;
    }else if (type == ScorpionType::Wait){
        guaiwu->gotoFrameAndPlay(0, 35, true);
        //guaiwu->play("wait", true);
        animNode->runAction(guaiwu);
        isMove = false;
    }else if (type == ScorpionType::Attack){
        guaiwu->gotoFrameAndPlay(40, 91, false);
        //guaiwu->play("attack", false);
        animNode->runAction(guaiwu);
        isMove = false;
    }else if (type == ScorpionType::Hurt){
        guaiwu->gotoFrameAndPlay(100, 115, false);
        //guaiwu->play("hurt", false);
        animNode->runAction(guaiwu);
        guaiwu->addFrameEndCallFunc(115, "a", [=](){ ChangeStatus(ScorpionType::Walk);   });
        isMove = false;
    }else if (type == ScorpionType::Kill){
        guaiwu->gotoFrameAndPlay(120, 155, false);
        //guaiwu->play("kill", false);
        animNode->runAction(guaiwu);
        isMove = false;
    }
}

/** 碰撞开始事件
 *  @2015/01/15 09:40
 */
bool Boos_gu::onCollisionBegin(const cocos2d::PhysicsContact& contact)
{
    PhysicsBody* bodyA = contact.getShapeA()->getBody();
    PhysicsBody* bodyB = contact.getShapeB()->getBody();
    PhysicsBody* bodythis = this->getPhysicsBody();
    if (bodythis == bodyA || bodythis == bodyB)
    {
        if (bodyA->getTag() == PHY_TAG_ARCHERY_L5 || bodyB->getTag() == PHY_TAG_ARCHERY_L5) {
            ChangeStatus(ScorpionType::Hurt);
            if (getHp() > 0) {
                Bullet* bu =  (Bullet*)bodyA->getNode();
                setHp(getHp() - bu->getAttack());
                ShowText(bu->getAttack());
                float chp = getHp() / this->_initHp * 100.0f;
                ShowLoading(chp);
                if (getHp() <= 0) {
                    _stext->setVisible(false);
                    _loadingShow->setVisible(false);
                    ChangeStatus(ScorpionType::Kill);
                    log("死亡了。。。。。。。。。。");
                }
            }
        }
        if (bodyA->getTag() == PHY_TAG_MAINCAR || bodyB->getTag() == PHY_TAG_MAINCAR) {
            ChangeStatus(ScorpionType::Attack);
        }
    }
    return true;
}

/** 显示血文字
 *  @2015/01/21 09:45
 */
void Boos_gu::ShowText(int str)
{
    char _s[20];
    sprintf(_s, "%d",str);
    auto  _showtext = Text::create();
    _showtext->setContentSize(Size(100.0f,60.0f));
    _showtext->setFontSize(22.0f);
    _showtext->setColor(Color3B(255, 255, 255));
    _showtext->setPosition(Vec2(0, this->getContentSize().height / 2 + 30));
    _showtext->setOpacity(255);
    _showtext->setString(_s);
    this->addChild(_showtext,100);
    auto fade = FadeTo::create(0.8f, 0);
    auto moto = MoveTo::create(0.8f, Vec2(0, this->getContentSize().height / 2 + 110));
    auto spawn = Spawn::create(fade,moto, NULL);
    auto clack = CallFunc::create([=]()
                                  {
                                      _showtext->removeFromParent();
                                  });
    auto sequen = Sequence::create(spawn,clack, NULL);
    _showtext->runAction(sequen);
    
    if (this->getScaleX() == -1) {
        _showtext->setScaleX(this->getScaleX());
    }
}

/** 显示血条
 *  @2015/01/21 09:45
 */
void Boos_gu::ShowLoading(float str)
{
    char _s[20];
    sprintf(_s, "%d",(int)getHp());
    _stext->setString(_s);
    _loadingShow->setPercent(str);
}


























