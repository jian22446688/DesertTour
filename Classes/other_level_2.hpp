//
//  other_level_2.hpp
//  DesertTour
//
//  Created by Cary on 15/12/25.
//
//

#ifndef other_level_2_hpp
#define other_level_2_hpp

#include <stdio.h>

#include "IBtnControl.hpp"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "Archery.hpp"

#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;


class other_level_2 : public cocos2d::Layer
{
public:

    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(other_level_2);
    
};




class Bombed : public cocos2d::Sprite ,public IBtnControl
{
    public:
    
    cocos2d::Sprite* bire = NULL;
    
    //刚体桥
    cocos2d::Sprite* phybire = NULL;
    
    cocos2d::Node* brie = NULL;
    
public:
    
    
    static Bombed* createSprite(Sprite* target);

    
    CREATE_FUNC(Bombed);
    
    virtual bool init();
   
    void setObj(Node* tagete);

    
    /** 问题回答
     *  @2015/12/29 14:21
     */
    virtual void AnswerPassed(bool ispass);
    
    /** 控制的按钮是否启用
     *  @2015/12/29 14:21
     */
    virtual void IsBtnEnable(bool isbtn);
    
    
    /** 碰撞开始事件
     *  @2015/12/29 17:10
     */
    bool onCollisionBegin(const cocos2d::PhysicsContact& contact);
  
    /** 爆炸
     *  @2015/12/29 17:10
     */
    void startBomb();
    
    /** 爆炸物体
     *  @2015/01/04 10:50
     */
    void setBomb(Sprite* obj);
    
    /** 爆炸桥物体
     *  @2015/01/04 11:00
     */
    void setBombbri(Sprite* obj);
    
};


class Brigde :public cocos2d::Sprite ,public IBomb
{
    
public:
    
    
    virtual bool init();
    
    CREATE_FUNC(Brigde);
    
    /** 问题回答
     *  @2015/01/04 09:15
     */
    virtual void PlayBomb();
    
    void setObj(Sprite* tagete);
    
};



class Monster : public cocos2d::Sprite,public IBtnControl
{
    

    
public:
    /** 问题回答
     *  @2015/01/07 10:15
     */
    typedef std::function<void()> frameEvent_1;
    typedef std::function<void()> frameEvent_2;
    typedef std::function<void()> frameEvent_3;
    typedef std::function<void()> frameEvent_4;
    
    
    virtual bool init();
    
    CREATE_FUNC(Monster);
    
    /** 设置物体
     *  @2015/01/04 09:15
     */
    void setObj(Node* tagete);
    
    /** 动画帧事件
     *  @2015/01/04 09:15
     */
    void addFrame_1(frameEvent_1& fram1);
    void addFrame_2(frameEvent_2& fram2);
    void addFrame_3(frameEvent_3& fram3);
    void addFrame_4(frameEvent_4& fram4);
    /** 问题回答
     *  @2015/01/04 09:15
     */
    virtual void AnswerPassed(bool ispass);
    
    /** 控制的按钮是否启用
     *  @2015/01/04 09:15
     */
    virtual void IsBtnEnable(bool isbtn);
    
    
protected:
    
    
    frameEvent_1 _frameEvent_1;
    frameEvent_2 _frameEvent_2;
    frameEvent_3 _frameEvent_3;
    frameEvent_4 _frameEvent_4;
    
};



class Scorpion_gw : public cocos2d::Sprite, public IBtnControl
{
    enum ScorpionType{
        Walk,
        Attack,
        Sleep,
    };
    
private:
    
    bool isMove = false;
    float movespeed = 0;
    ActionTimeline* guaiwu;
    cocos2d::Vec2 moveA;
    cocos2d::Vec2 moveB;
    bool iskeyr = false;
    bool iskeyl = true;
    Node* animNode;
    
    ScorpionType _scorpiontype = Walk;
    
public:
    
    
    
    virtual bool init();
    
    virtual void update(float ft);
    
    CREATE_FUNC(Scorpion_gw);
    
    void setObj(Node* obj);
    
    /** 设置移动范围
     *  @2015/01/15 11:20
     */
    void setMovePosition(Node* objeA,Node* objeB,float movespeed);
    
    /** 更换状态
     *  @2015/01/15 09:40
     */
    void ChangeStatus(ScorpionType type);
    
    /** 问题回答
     *  @2015/01/15 09:40
     */
    virtual void AnswerPassed(bool ispass);
    
    /** 控制的按钮是否启用
     *  @2015/01/15 09:40
     */
    virtual void IsBtnEnable(bool isbtn);
    
    /** 碰撞开始事件
     *  @2015/01/15 09:40
     */
    bool onCollisionBegin(const cocos2d::PhysicsContact& contact);
};



class L9_Lifting : public cocos2d::Sprite ,public IBtnControl
{

private:
    
    bool _isopen = false;
    
public:

    virtual bool init(){
        if (!Sprite::init()) {
            return false;
        }
        this->setTexture("DesertUI/Level/level_9/l9_gound_3.png");
        PhysicsBody* phys_1 = PhysicsBody::createBox(Size(this->getContentSize().width,this->getContentSize().height/15));
        phys_1->setPositionOffset(Vec2(0.0f, -this->getContentSize().height/2+20-1));
        phys_1->setDynamic(false);
        this->setPhysicsBody(phys_1);
        return true;
    }
    
    void setObj(Sprite* obj){
        this->setPosition(obj->getPosition());
        obj->setVisible(false);
    }
    
    CREATE_FUNC(L9_Lifting);
    
    bool IsEn(){
        return _isopen;
    }
    
    /** 问题回答
     *  @2015/12/28 15:41
     */
    virtual void AnswerPassed(bool ispass){
    
    }
    
    /** 控制的按钮是否启用
     *  @2015/12/28 15:41
     */
    virtual void IsBtnEnable(bool isbtn){
        _isopen = true;
    }
    
    
};


class Guard_gu : public cocos2d::Sprite
{
    enum ScorpionType{
        Walk,
        Attack,
        Sleep,
    };
private:
    
    bool isMove = false;
    float movespeed = 0;
    ActionTimeline* guaiwu;
    cocos2d::Vec2 moveA;
    cocos2d::Vec2 moveB;
    bool iskeyr = false;
    bool iskeyl = true;
    Node* animNode;
    
public:
    
    virtual bool init();
    
    CREATE_FUNC(Guard_gu);
    
    
    virtual void update(float ft);
    
    void setObj(Node* obj);
    
    /** 设置移动范围
     *  @2015/01/20 09:15
     */
    void setMovePosition(Node* objeA,Node* objeB,float movespeed);
    
    /** 碰撞开始事件
     *  @2015/01/20 09:50
     */
    bool onCollisionBegin(const cocos2d::PhysicsContact& contact);
    
    /** 更换状态
     *  @2015/01/15 09:40
     */
    void ChangeStatus(ScorpionType type);
};





class Boos_gu : public cocos2d::Sprite
{
    enum ScorpionType{
        Walk,
        Wait,
        Attack,
        Kill,
        Hurt,
        Sleep,
    };
private:
    bool isMove = false;
    float movespeed = 0;
    ActionTimeline* guaiwu;
    cocos2d::Vec2 moveA;
    cocos2d::Vec2 moveB;
    bool iskeyr = false;
    bool iskeyl = true;
    Node* animNode;
    
    float _initHp;
    
    float _hp = 100000.0f;
    
    Text* _stext;
    LoadingBar* _loadingShow;
    
    ScorpionType scotype;
    
public:
    virtual bool init();
    
    CREATE_FUNC(Boos_gu);
    
    virtual void update(float ft);
    
    void setObj(Node* obj);
    
    /** 设置移动范围
     *  @2015/01/21 09:15
     */
    void setMovePosition(Node* objeA,Node* objeB,float movespeed);
    
    /** 碰撞开始事件
     *  @2015/01/21 09:10
     */
    bool onCollisionBegin(const cocos2d::PhysicsContact& contact);
    
    /** 更换状态
     *  @2015/01/21 09:45
     */
    void ChangeStatus(ScorpionType type);
    
    
    /** 怪物的血
     *  @2015/01/21 09:45
     */
    void setHp(float hp){
        this->_hp = hp;
    }
    float getHp(){
        return this->_hp;
    }
    
    /** 显示血文字
     *  @2015/01/21 09:45
     */
    void ShowText(int str);
    
    /** 显示血文字
     *  @2015/01/21 09:45
     */
    void ShowLoading(float str);
};




































#endif /* other_level_2_hpp */
