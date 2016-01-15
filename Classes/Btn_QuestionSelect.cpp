//
//  Btn_QuestionSelect.cpp
//  DesertTour
//
//  Created by Cary on 15/12/16.
//
//

#include "Btn_QuestionSelect.hpp"

#include "MainUI.hpp"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;

bool Btn_QuestionSelect::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //加载问题按钮
    auto btn_question = CSLoader::createNode("LayerUI/btn_UI_question.csb");
    this->addChild(btn_question);
    
    //播放问题按钮动画
    auto btn_questionanim = CSLoader::createTimeline("Node/uianimtion/questionselect.csb");
    btn_questionanim->gotoFrameAndPlay(0, 80, true);
    btn_question->runAction(btn_questionanim);
    
    //设置问题按钮位置
    auto ques = btn_question->getChildByName<Node*>("anim_question");
    
    btnques = ques->getChildByName<Sprite*>("anim_question0001_1");
    
    //屏幕添加点击事件
    auto ontouchevent = EventListenerTouchOneByOne::create();
    ontouchevent->onTouchBegan = CC_CALLBACK_2(Btn_QuestionSelect::onTouchBegan,this);
    ontouchevent->setSwallowTouches(true);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ontouchevent, btnques);
    
    return true;
}


/** 设置物体
 *  @2015/12/22 19:35
 */
void Btn_QuestionSelect::setObj(Node* obj)
{
    this->setPosition(obj->getPosition());
    this->setScaleX(obj->getScaleX());
    this->setScaleY(obj->getScaleY());
    this->setRotation(obj->getRotation());
    obj->setVisible(false);
}


/** 触摸屏幕开始
 *  @2015/12/16 19:40
 */
bool Btn_QuestionSelect::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    //获取当前的触摸点的精灵
    //将本地坐标系转化为精灵坐标系(以精灵的左下角作为坐标原点)
    Point locaNode = btnques->convertToNodeSpace(touch->getLocation());
    //获取精灵的尺寸大小
    Size s = btnques->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    if (rect.containsPoint(locaNode))
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AudioAssets/audio_home/gone.wav");
        Btn_QuestionSelect::getMainUI()->QuestionActionPlayed(true,this);
        
        log("点击到了问题按钮 正在出问题请稍后...... %s",this->getName().c_str());
        return true;
    }
    return false;
}


/** 给问题按钮设置 需要控制的物体
 *  @2015/12/19 14:32
 */
void Btn_QuestionSelect::AnswerFinsh(bool& isAnswercorrect)
{
    
    if (isAnswercorrect)
    {
        //TODO 问题回答正确
        
        
    } else {
        
        //TODO 问题回答错误
    }
    
    //调用接口的方法解锁控制的按钮
    
    _ibtncontrol->IsBtnEnable(true);
    _ibtncontrol->AnswerPassed(isAnswercorrect);
    
    this->removeFromParent();
}





/*****************************************标准按钮*************************************************/


// on "init" you need to initialize your instance
bool Btn_Standard::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto btn_standard = CSLoader::createNode("LayerUI/btn_standard.csb");
    btn_standard->setName("root_btn_standard");
    this->addChild(btn_standard);
    Button* btn_stan = btn_standard->getChildByName<Button*>("btn_standard");
    
    btn_stan->addTouchEventListener(CC_CALLBACK_2(Btn_Standard::onBtnClick, this));
    
    btn_stan->setEnabled(getBtnEnable());
    
    
    return true;
}

/** 设置物体
 *  @2015/12/23 08:45
 */
void Btn_Standard::setObj(Node* obj)
{
    //设置Anchor点
    this->setName(obj->getName());
    this->setPosition(obj->getPosition());
    this->setScaleX(obj->getScaleX());
    this->setScaleY(obj->getScaleY());
    this->setRotation(obj->getRotation());
    obj->setVisible(false);
}


/** 播放音效
 *  @2015/01/11 09:35
 */
void Btn_Standard::PlayEffect()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AudioAssets/audio_home/gone.wav");
}

void Btn_Standard::onBtnClick(Ref* reft,Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AudioAssets/audio_home/gone.wav");
    }
}


/** 获取按钮 需要控制的物体
 *  @2015/12/19 15:25
 */
Button* Btn_Standard::getBtn()
{
    return (Button*)this->getChildByName("root_btn_standard")->getChildByName("btn_standard");
}


/** 问题回答
 *  @2015/12/28 15:41
 */
void Btn_Standard::AnswerPassed(bool ispass)
{
    if (ispass)
    {
        
    }
    else
    {
        
    }
    
}

/** 控制的按钮是否启用
 *  @2015/12/28 15:41
 */
void Btn_Standard::IsBtnEnable(bool isbtn)
{
    if (isbtn)
    {
        
    }
    else
    {
        
    }
    
    setBtnEnable(true);
    
}


/*****************************************标准按钮*************************************************/


/*****************************************地面按钮*************************************************/


bool Btn_Ground::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    this->setTexture("DesertUI/Level/level_2/btn_dicar0001.png");
    PhysicsBody* phyboy = PhysicsBody::createBox(Size(this->getContentSize().width-20,this->getContentSize().height+30));
    phyboy->setTag(PHY_TAG_BTNGROUND);
    phyboy->setCategoryBitmask(0x01);
    phyboy->setCollisionBitmask(0x02);
    phyboy->setContactTestBitmask(0x01);
    phyboy->setDynamic(false);
    this->setPhysicsBody(phyboy);
    auto collisionEvent = EventListenerPhysicsContact::create();
    collisionEvent->onContactBegin = CC_CALLBACK_1(Btn_Ground::onCollisionBegin, this);
    collisionEvent->onContactSeparate = CC_CALLBACK_1(Btn_Ground::onContactSeparate,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(collisionEvent, this);
    return true;
}

/** 设置物体
 *  @2015/01/07 11:21
 */
void Btn_Ground::setObj(Node* obj)
{
    //设置Anchor点
    this->setName(obj->getName());
    this->setAnchorPoint(cocos2d::Vec2(0,0));
    this->setPosition(obj->getPosition());
    this->setScaleX(obj->getScaleX());
    this->setScaleY(obj->getScaleY());
    this->setRotation(obj->getRotation());
    this->setPositionZ(obj->getPositionZ());
    obj->setVisible(false);
}

/** 碰撞开始事件
 *  @2015/01/07 11:21
 */
bool Btn_Ground::onCollisionBegin(const cocos2d::PhysicsContact& contact)
{
    PhysicsBody* bodyA = contact.getShapeA()->getBody();
    PhysicsBody* bodyB = contact.getShapeB()->getBody();
    PhysicsBody* body = this->getPhysicsBody();
    if(body == bodyA || body == bodyB)
    {
        this->setTexture("DesertUI/Level/level_2/btn_dicar0002.png");
        if (_clickEventListener){
            _clickEventListener();
        }
        
    }
    return true;
}

/** 碰撞离开
 *  @2015/01/07 11:21
 */
void Btn_Ground::onContactSeparate(const cocos2d::PhysicsContact& contact)
{
    PhysicsBody* bodyA = contact.getShapeA()->getBody();
    PhysicsBody* bodyB = contact.getShapeB()->getBody();
    PhysicsBody* body = this->getPhysicsBody();
    if(body == bodyA || body == bodyB)
    {
        this->setTexture("DesertUI/Level/level_2/btn_dicar0001.png");
    }
}


/**
 * Set a callback to touch vent listener.
 *@param callback  The callback in `ccWidgetEventCallback.`
 */
void Btn_Ground::onCallbackTest_2(const ccWidgetClickCallback& callback)
{
    this->_clickEventListener = callback;

}


/** 问题回答
 *  @2015/01/07 11:21
 */
void Btn_Ground::AnswerPassed(bool ispass)
{
    
    
}

/** 控制的按钮是否启用
 *  @2015/01/07 11:21
 */
void Btn_Ground::IsBtnEnable(bool isbtn)
{
    isbtnopen =true;
    
}

/*****************************************地面按钮*************************************************/



/*****************************************地面按钮*************************************************/


bool Btn_Ground_1::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    this->setTexture("DesertUI/Level/level_2/btn_dicar0001.png");
    PhysicsBody* phyboy = PhysicsBody::createBox(Size(this->getContentSize().width-20,this->getContentSize().height+30));
    phyboy->setTag(PHY_TAG_BTNGROUND_1);
    phyboy->setCategoryBitmask(0x01);
    phyboy->setCollisionBitmask(0x02);
    phyboy->setContactTestBitmask(0x01);
    phyboy->setDynamic(false);
    this->setPhysicsBody(phyboy);
    auto collisionEvent = EventListenerPhysicsContact::create();
    collisionEvent->onContactBegin = CC_CALLBACK_1(Btn_Ground_1::onCollisionBegin, this);
    collisionEvent->onContactSeparate = CC_CALLBACK_1(Btn_Ground_1::onContactSeparate,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(collisionEvent, this);
    return true;
}

/** 设置物体
 *  @2015/01/07 11:21
 */
void Btn_Ground_1::setObj(Node* obj)
{
    //设置Anchor点
    this->setName(obj->getName());
    this->setAnchorPoint(cocos2d::Vec2(0,0));
    this->setPosition(obj->getPosition());
    this->setScaleX(obj->getScaleX());
    this->setScaleY(obj->getScaleY());
    this->setRotation(obj->getRotation());
    this->setPositionZ(obj->getPositionZ());
    obj->setVisible(false);
}

/** 碰撞开始事件
 *  @2015/01/07 11:21
 */
bool Btn_Ground_1::onCollisionBegin(const cocos2d::PhysicsContact& contact)
{
    PhysicsBody* bodyA = contact.getShapeA()->getBody();
    PhysicsBody* bodyB = contact.getShapeB()->getBody();
    PhysicsBody* body = this->getPhysicsBody();
    if(body == bodyA || body == bodyB)
    {
        this->setTexture("DesertUI/Level/level_2/btn_dicar0002.png");
        if (_clickEventListener){
            _clickEventListener();
        }
    }
    return true;
}

/** 碰撞离开
 *  @2015/01/07 11:21
 */
void Btn_Ground_1::onContactSeparate(const cocos2d::PhysicsContact& contact)
{
    PhysicsBody* bodyA = contact.getShapeA()->getBody();
    PhysicsBody* bodyB = contact.getShapeB()->getBody();
    PhysicsBody* body = this->getPhysicsBody();
    if(body == bodyA || body == bodyB)
    {
        this->setTexture("DesertUI/Level/level_2/btn_dicar0002.png");
    }
}


/**
 * Set a callback to touch vent listener.
 *@param callback  The callback in `ccWidgetEventCallback.`
 */
void Btn_Ground_1::onCallbackTest_2(const ccWidgetClickCallback& callback)
{
    this->_clickEventListener = callback;
    
}


/** 问题回答
 *  @2015/01/07 11:21
 */
void Btn_Ground_1::AnswerPassed(bool ispass)
{
    
    
}

/** 控制的按钮是否启用
 *  @2015/01/07 11:21
 */
void Btn_Ground_1::IsBtnEnable(bool isbtn)
{
    isbtnopen =true;
    
}

/*****************************************地面按钮*************************************************/


































