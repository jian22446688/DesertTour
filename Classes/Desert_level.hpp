//
//  Desert_home.hpp
//  DesertTour
//
//  Created by Cary on 15/12/12.
//
//

#ifndef Desert_level_hpp
#define Desert_level_hpp

#include <stdio.h>


#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;


class Desert_level : public cocos2d::Layer
{

private:
    
    TextAtlas* text_showstar;
    
private:
    //设置星星显示的数量
    void ShowStar(int starquantity);
    
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Desert_level);
    
    void onEnter();
    
    void onBtnClickLevel(Ref* reft,Widget::TouchEventType type);
    void onBtnClickBack(Ref* reft,Widget::TouchEventType type);
};



class LevelSystem
{
public:
    
    /** 关卡的进入按钮
     *  @2015/12/14 13:40
     */
    
    /** 关卡的进入按钮
     *  @2015/12/14 13:40
     */
    Button* btnLevel;
    
    /** 当前的关卡
     *  @2015/12/14 13:40
     */
    int currentLevel;
    
    
    /** 当前的关卡行星数量
     *  @2015/12/14 13:40
     */
    int currentLevelStarNumber = 0;
    
    
    /** 当前的关卡是否开启
     *  @2015/12/14 13:40
     */
    bool isCurrentLevel = false;
    
    /** 当前的关卡星星数组
     *  @2015/12/14 13:40
     */
    cocos2d::Sprite* star[5];
    
    /** 初始化卡关的各种状态
     *  @2015/12/14 13:40
     */
    void initLevel();
    
    /** 设置显示的星星数量
     *  @2015/12/14 13:40
     */
    void ShowStar();
    
    
};
































#endif /* Desert_home_hpp */
