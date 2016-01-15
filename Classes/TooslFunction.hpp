//
//  TooslFunction.hpp
//  DesertTour
//
//  Created by Cary on 15/12/14.
//
//

#ifndef TooslFunction_hpp
#define TooslFunction_hpp

#include <stdio.h>

#include "cocos2d.h"
#include "MainUI.hpp"


class ToolsFunction:public cocos2d::Layer
{
private:
    
    //  碰撞掩码     类型      说明
    //------------------------------------------
    //  100001      刚体     物理世界
    //  555555      刚体     主要车的
    //  300001      刚体     悬浮的物体
    //  400001      刚体     第一关的怪物
    //  600001      刚体     弹簧的物体
    //  666666      刚体     通过卡关的
    //  300002      刚体     碰到悬浮物体设置标签
    //  200001      物体     主要UI界面的标签
    
    
    
    
public:
    
    /** 设置开启卡关限制
     *  @2015/12/14 16:35
     */
    const static int AsbL2 = 1;
    const static int AsbL3 = 3;
    const static int AsbL4 = 5;
    const static int AsbL5 = 7;
    const static int AsbL6 = 9;
    const static int AsbL7 = 11;
    const static int AsbL8 = 13;
    const static int AsbL9 = 15;
    const static int AsbL10 = 18;
    
    
    /** 设置精灵成刚体
     *  @2015/12/18 19:05
     */
    static void setPhySpriteBox(cocos2d::Sprite* spritephy);
    
    
    /** 设置静态 可碰撞 精灵成刚体
     *  @2015/12/21 09:15
     */
    static void setPhyDynamicSpriteBox(cocos2d::Sprite* spritephy);
    
    /** 设置静态 和车 触发事件的 精灵成刚体
     *  @2015/12/21 09:15
     */
    static void setPhyContactSpriteBox(cocos2d::Sprite* spritephy);
    
    
    /** 设置静态 障碍 触发事件的 精灵成刚体
     *  @2015/12/21 09:15
     */
    static void setPhyContactBarrBox(cocos2d::Sprite* spritephy);
    
    /** 设置静态 和车 碰撞事件的 精灵成刚体
     *  @2015/12/21 09:15
     */
    static void setPhyCollisionSpriteBox(cocos2d::Sprite* spritephy);
    
    /** 设置保存关卡的星星数量
     *  @2015/12/18 19:05
     */
    //static void setPhySpriteBox(cocos2d::Sprite* spritephy);
    
    /** 设置保存关卡的星星数量
     *  @2015/12/14 16:35
     */
    static void setSaveStar(std::string keynma,int starNumber);
    
    /** 设置卡关是否开启的状态
     *  @2015/12/14 16:35
     */
    static void setSavebool(std::string boolname,bool islevel);
    
    /** 获取卡关开关状态
     *  @2015/12/14 16:35
     */
    static bool getLevelStatus(std::string levelname);
    
    /** 获取卡关的星星数量
     *  @2015/12/14 16:35
     */
    static int getLevelStarCount(std::string levelname);
    
    /** 统计所有的星星数量
     *  @2015/12/14 16:35
     */
    static int CountStarNumber();
    
    /** 向前播放 Tween 动作
     *  @2015/12/21 09:55
     */
    static void TweenForword(cocos2d::Node* tweenobject, const cocos2d::Vec2 tweenpos);
    
    /** 向后播放twwen 动作
     *  @2015/12/21 09:55
     */
    static void TweenReverse(cocos2d::Node* tweenobject, const cocos2d::Vec2 tweenpos);
    
    
    /** 进入关卡 根据数字加载关卡
     *  @2015/12/28 17:16
     */
    static void LoadLevel(std::string  levelnumber);
    
    
    
    
    
    
    
    
    
};



















#endif /* TooslFunction_hpp */
