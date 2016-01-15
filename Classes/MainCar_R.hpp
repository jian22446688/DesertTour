//
//  MainCar_R.hpp
//  DesertTour
//
//  Created by Cary on 15/12/16.
//
//

#ifndef MainCar_R_hpp
#define MainCar_R_hpp

#include <stdio.h>


#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;






class MainCar_R : public cocos2d::Layer
{
private:
    
    
    
    Node* levelscene;
    
    /** 主要车身
     *  @2015/12/16 09:48
     */
    cocos2d::Sprite* maincarbody;
    
    /** 车的大轮子
     *  @2015/12/16 09:48
     */
    cocos2d::Sprite* mainwheel_d;
    
    /** 车的小轮子
     *  @2015/12/16 09:48
     */
    cocos2d::Sprite* mainwheel_x;
    
    
    /** 车的速度方向
     *  @2015/12/16 09:48
     */
    bool iscar = false;

    /** 主要UI
     *  @2015/12/16 09:48
     */
     class MainUI* mainUiCar;
    
    /** 车变换的位置
     *  @2015/01/14 14:28
     */
    Node* _chenge;
    
    
public:
    typedef std::function<void()> carKillCallk;
    
    carKillCallk _carkilcallk;
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    
    CREATE_FUNC(MainCar_R);
    
    /** 场景进入函数
     *  @2015/12/16 09:40
     */
    virtual void onEnter();
    
    /** 场景更新函数
     *  @2015/12/16 09:40
     */
    virtual void update(float dt);
    
    /** 触摸屏幕开始
     *  @2015/12/16 09:40
     */
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    
    /** 碰撞开始事件
     *  @2015/12/16 11:28
     */
    bool onCollisionBegin(const cocos2d::PhysicsContact& contact);
    
    
    
    /** 车暂停
     *  @2015/12/22 17:05
     */
    void StopCar();
    
    /** 车加速度方法
     *  @2015/12/29 08:20
     */
    void setCarSpeed(float sd , float sx , bool iscaropen);
    
    /** 返回车的身体
     *  @2015/12/23 17:15
     */
    Node* getCarBoty();
    
    
    void setBodyEnable();
    
    
    /** 设置主要UI实例
     *  @2015/12/23 15:40
     */
    void setMainUI(MainUI* mainui);
    
    
    /** 获取主要UI实例
     *  @2015/12/24 15:40
     */
    MainUI* getMainUI();
    
    
    
    /** 设置车
     *  @2015/12/25 08:30
     */
    void setObj(Node* object);
    
    
    /** 死亡动画
     *  @2015/12/29 09:25
     */
    void kiLLCar_js();
    
    /** 炸弹死亡动画
     *  @2015/12/29 19:25
     */
    void kiLLCar_zd();
    
    
    /** 调取游戏结束界面
     *  @2015/12/25 10:05
     */
    void PalyGameOver();
    
    
    /** 转向
     *  @2015/12/25 10:05
     */
    void CarTurn();
    
    
    /** 获取 右 车的位置
     *  @2015/01/05 10:15
     */
    Node* getCarNode();

    
    /** 获取 获取 车是否开动
     *  @2015/01/05 19:40
     */
    bool isCarOpen();
    
    /** 设置车死亡的回调函数
     *  @2015/01/011 10:40
     */
    void addCarkillcallk(const carKillCallk& carcalk);
    
    /** 车变换的位置
     *  @2015/01/14 14:22
     */
    void setChange(Node* ojb);
    
    
};


/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/



class MainCar_L : public cocos2d::Layer
{
private:
    
    Node* levelscene;
    
    /** 主要车身
     *  @2015/01/04 19:15
     */
    cocos2d::Sprite* maincarbody;
    
    /** 车的大轮子
     *  @2015/01/04 19:15
     */
    cocos2d::Sprite* mainwheel_d;
    
    /** 车的小轮子
     *  @2015/01/04 19:15
     */
    cocos2d::Sprite* mainwheel_x;
    
    
    /** 车的速度方向
     *  @2015/01/04 19:15
     */
    bool iscar = false;
    
    /** 主要UI
     *  @2015/01/04 19:15
     */
    class MainUI* mainUiCar;
    
    
public:
    
    typedef std::function<void()> carKillCallk;
    
    carKillCallk _carkilcallk;
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    
    CREATE_FUNC(MainCar_L);
    
    /** 场景进入函数
     *  @2015/01/04 17:10
     */
    virtual void onEnter();
    
    /** 场景更新函数
     *  @2015/01/04 17:10
     */
    virtual void update(float dt);
    
    /** 触摸屏幕开始
     *  @2015/01/04 17:10
     */
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    
    /** 碰撞开始事件
     *  @2015/01/04 17:10
     */
    virtual bool onCollisionBegin(const cocos2d::PhysicsContact& contact);
    
    
    
    /** 车暂停
     *  @2015/01/04 17:10
     */
    void StopCar();
    
    /** 车加速度方法
     *  @2015/01/04 17:10
     */
    void setCarSpeed(float sd , float sx , bool iscaropen);
    
    /** 返回车的身体
     *  @2015/01/04 17:10
     */
    Node* getCarBoty();
    
    
    void setBodyEnable();
    
    
    /** 设置主要UI实例
     *  @2015/01/04 17:10
     */
    void setMainUI(MainUI* mainui);
    
    
    /** 获取主要UI实例
     *  @2015/01/04 17:10
     */
    MainUI* getMainUI();
    
    
    
    /** 设置车
     *  @2015/01/04 17:10
     */
    void setObj(Node* object);
    
    
    /** 死亡动画
     *  @2015/01/04 17:10
     */
    void kiLLCar_js();
    
    /** 炸弹死亡动画
     *  @2015/01/04 17:10
     */
    void kiLLCar_zd();
    
    
    /** 调取游戏结束界面
     *  @2015/01/04 17:10
     */
    void PalyGameOver();
    
    
    /** 获取 左 车的位置
     *  @2015/01/05 10:15
     */
    Node* getCarNode();
    
    
    /** 获取 车是否开动
     *  @2015/01/05 19:40
     */
    bool isCarOpen();
    
    
    /** 设置车死亡的回调函数
     *  @2015/01/011 10:40
     */
    void addCarkillcallk(const carKillCallk& carcalk);
};







































#endif /* MainCar_R_hpp */
