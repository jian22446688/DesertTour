
//
//  Btn_QuestionSelect.hpp
//  DesertTour
//
//  Created by Cary on 15/12/16.
//
//

#ifndef Btn_QuestionSelect_hpp
#define Btn_QuestionSelect_hpp

#include <stdio.h>
#include "MainUI.hpp"

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;




class Btn_QuestionSelect : public cocos2d::Layer
{
    
private:
    
    class MainUI* _maniui = NULL;

    class Btn_Standard* _btncontrol = NULL;
    
    IBtnControl* _ibtncontrol = NULL;
    
    cocos2d::Sprite* btnques;
    
public:
    
    //static cocos2d::Layer* createScene(Node* node,Node* setcurrenQuestionpos);
    
    virtual bool init();
    
    CREATE_FUNC(Btn_QuestionSelect);
    
    
    /** 设置物体
     *  @2015/12/22 19:35
     */
    void setObj(Node* obj);
    
    /** 触摸屏幕开始
     *  @2015/12/16 19:40
     */
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    
    /** 给问题按钮设置 需要控制的物体
     *  @2015/12/19 14:32
     */
    void AnswerFinsh(bool& isAnswercorrect);
    
    
    /** 给问题按钮设置 1,主要UI , 2控制按钮
     *  @2015/12/18 19:40
     */
    void setMainUI(MainUI* mainui ,Btn_Standard* btn_stand)
    {
        this->_maniui = mainui;
        this->_btncontrol = btn_stand;
    }
    
    /** 给问题按钮设置 1,主要UI , 2控制按钮 接口
     *  @2015/12/28 16:00
     */
    void setIBtnMainUI(MainUI* mainui ,IBtnControl* ibtn_stand)
    {
        this->_maniui = mainui;
        this->_ibtncontrol = ibtn_stand;
    }
    
    /** 给问题按钮设置主要UI
     *  @2015/12/18 19:40
     */
    MainUI* getMainUI()
    {
        return _maniui;
    }
    
    /** 给问题按钮设置 需要控制的物体
     *  @2015/12/18 19:40
     */
    void setControlObject(Btn_Standard* btn_stand)
    {
        this->_btncontrol = btn_stand;
    }

    
    /** 给问题按钮设置 需要控制的物体
     *  @2015/12/18 19:40
     */
    Btn_Standard*  getControlObject()
    {
        return _btncontrol;
    }
    
};



/***********************************标准按钮***************************************/


class Btn_Standard : public cocos2d::Layer ,public IBtnControl
{
    
public:
    
    bool _isBtnEnable = false;
    
    
public:
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Btn_Standard);
    
    
    /** 给问题按钮设置 需要控制的物体
     *  @2015/12/18 19:40
     */
    void onBtnClick(Ref* reft,Widget::TouchEventType type);
    
    
    /** 设置物体
     *  @2015/12/23 08:45
     */
    void setObj(Node* obj);
    
    /** 播放音效
     *  @2015/01/11 09:35
     */
    void PlayEffect();
    
    /** 获取当前的按钮是否可用
     *  @2015/12/19 15:30
     */
    bool getBtnEnable()
    {
        return _isBtnEnable;
    }
    
    /** 设置控制按钮是否可用
     *  @2015/12/19 15:20
     */
    void setBtnEnable(bool isbtn)
    {
        auto btn = (Button*)this->getChildByName("root_btn_standard")->getChildByName("btn_standard");
        btn->setEnabled(isbtn);
        _isBtnEnable = isbtn;
    }
    
    /** 获取按钮 需要控制的物体
     *  @2015/12/19 15:25
     */
    Button* getBtn();
    
    
    /** 问题回答
     *  @2015/12/28 15:41
     */
    virtual void AnswerPassed(bool ispass);
    
    /** 控制的按钮是否启用
     *  @2015/12/28 15:41
     */
    virtual void IsBtnEnable(bool isbtn);
};



class Btn_Ground : public cocos2d::Sprite,public IBtnControl
{
private:
    bool isbtnopen = false;

    
public:
    
    /**
     * Widget click event callback.
     */
    typedef std::function<void()> ccWidgetClickCallback;
    
    
    virtual bool init();
    
    
    CREATE_FUNC(Btn_Ground);
    
    /** 设置物体
     *  @2015/01/07 11:21
     */
    void setObj(Node* obj);
    
    /** 碰撞开始事件
     *  @2015/01/07 11:21
     */
    bool onCollisionBegin(const cocos2d::PhysicsContact& contact);
    
    
    /** 碰撞离开
     *  @2015/01/07 11:21
     */
    void onContactSeparate(const cocos2d::PhysicsContact& contact);
    
    
    /**
     * Set a callback to touch vent listener.
     *@param callback  The callback in `ccWidgetEventCallback.`
     */
    void onCallbackTest_2(const ccWidgetClickCallback& callback);
    
    
    /** 问题回答
     *  @2015/01/07 11:21
     */
    virtual void AnswerPassed(bool ispass);
    
    /** 控制的按钮是否启用
     *  @2015/01/07 11:21
     */
    virtual void IsBtnEnable(bool isbtn);
    
protected:
    
    ccWidgetClickCallback _clickEventListener;
    
};


class Btn_Ground_1 : public cocos2d::Sprite,public IBtnControl
{
private:
    bool isbtnopen = false;
    
    
public:
    
    /**
     * Widget click event callback.
     */
    typedef std::function<void()> ccWidgetClickCallback;
    
    
    virtual bool init();
    
    
    CREATE_FUNC(Btn_Ground_1);
    
    /** 设置物体
     *  @2015/01/07 11:21
     */
    void setObj(Node* obj);
    
    /** 碰撞开始事件
     *  @2015/01/07 11:21
     */
    bool onCollisionBegin(const cocos2d::PhysicsContact& contact);
    
    
    /** 碰撞离开
     *  @2015/01/07 11:21
     */
    void onContactSeparate(const cocos2d::PhysicsContact& contact);
    
    
    /**
     * Set a callback to touch vent listener.
     *@param callback  The callback in `ccWidgetEventCallback.`
     */
    void onCallbackTest_2(const ccWidgetClickCallback& callback);
    
    
    /** 问题回答
     *  @2015/01/07 11:21
     */
    virtual void AnswerPassed(bool ispass);
    
    /** 控制的按钮是否启用
     *  @2015/01/07 11:21
     */
    virtual void IsBtnEnable(bool isbtn);
    
protected:
    
    ccWidgetClickCallback _clickEventListener;
    
};




/** 自定义带问题的按钮
 *  @2015/01/012 14:35
 */
class QuestionButton : public Button ,public IBtnControl
{
    
private:
    
    Button* _button;
    
    bool _isBtnEnable = false;
public:
    
    CREATE_FUNC(QuestionButton);
    
    /** 设置物体
     *  @2015/01/012 14:10
     */
    void setObj(Button* obj)
    {
        _button = obj;
        _button->setPosition(obj->getPosition());
        _button->setScale(obj->getScaleX(), obj->getScaleY());
        _button->setContentSize(obj->getContentSize());
        _button->setEnabled(_isBtnEnable);
    }
    
    Button* getBtn()
    {
        return _button;
    }
    
    /** 问题回答
     *  @2015/01/12 14:10
     */
    virtual void AnswerPassed(bool ispass)
    {
        
    }
    
    /** 控制的按钮是否启用
     *  @2015/01/012 14:10
     */
    virtual void IsBtnEnable(bool isbtn)
    {
        _button->setEnabled(true);
    }
};

































#endif /* Btn_QuestionSelect_hpp */
