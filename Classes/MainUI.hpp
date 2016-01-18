//
//  MainUI.hpp
//  DesertTour
//
//  Created by Cary on 15/12/14.
//
//

#ifndef MainUI_hpp
#define MainUI_hpp

#include <stdio.h>

/** 所有的关卡引入
 *  @2015/12/15 11:10
 */
#include "Level_1.hpp"
#include "Level_2.hpp"
#include "Level_3.hpp"
#include "Level_4.hpp"
#include "Level_5.hpp"
#include "Level_6.hpp"
#include "Level_7.hpp"
#include "Level_8.hpp"
#include "Level_9.hpp"
#include "Level_10.hpp"


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
//  400006      刚体     僵死的食物
//  400008      刚体     炸弹
//  400010      刚体     怪物碰到障碍转向
//  400010      刚体     火把
//  600010      刚体     地上的按钮
//  600020      刚体     地上的按钮_1
//  400020      刚体     上吊的怪物
//  400030      刚体     5关木乃伊
//  400040      刚体     弓箭
//  555565      刚体     车变换位置
//  400050      刚体     蝎子的刚体





/** 碰撞和触发层
 *  @2015/12/28 08:00
 */
#define PHY_TAG_WORID           100001
#define PHY_TAG_MANUI           200001
#define PHY_TAG_MAINCAR         555555
#define PHY_TAG_JS              400001
#define PHY_TAG_SPRING          600001
#define PHY_TAG_FINISHLEVEL     666666
#define PHY_TAG_KILL_FIRE       400010
#define PHY_TAG_BTNGROUND       600010
#define PHY_TAG_BARRIER         400010
#define PHY_TAG_BTNGROUND_1     600020
#define PHY_TAG_KILL_UP         400020
#define PHY_TAG_KILL_L5         400030
#define PHY_TAG_ARCHERY_L5      400040
#define PHY_TAG_CARCHANGEPOS    555565
#define PHY_TAG_SCORPION        400050

/** 车加速
 *  @2015/12/14 20:30
 */
#define CAR_STOP                0
#define CAR_SPEED_X             4.0f
#define CAR_SPEED_D             5.0f



/** 主要的 三个界面 界面
 *  @2015/12/14 20:30
 */
#define PAGE_QUESTION       "img_questionbg"
#define PAGE_GAMEWIN        "img_gamewin_bg"
#define PAGE_GAMEOVER       "img_gameover_bg"

/** UI的主要按钮
 *  @2015/12/14 20:20
 */
#define BTN_MAINUI_ADDSPEED        "btn_mainui_addspeed"
#define BTN_MAINUI_RESTART         "btn_mainui_restart"
#define BTN_MAINUI_TOLEVEL         "btn_mainui_tolevel"
#define BTN_MAINUI_CARTURN         "btn_mainui_carturn"


/** 游戏胜利按钮
 *  @2015/12/14 20:20
 */
#define BTN_GAMEWIN_NEXT            "btn_gamewin_next"
#define BTN_GAMEWIN_RESTART         "btn_gamewin_restart"
#define BTN_GAMEWIN_TOLEVEL         "btn_gamewin_tolevel"

/** 游戏失败按钮
 *  @2015/12/14 20:20
 */
#define BTN_GAMEOVER_RESTART         "btn_gameover_restart"
#define BTN_GAMEOVER_TOLEVEL         "btn_gameover_tolevel"

/** 游戏胜利显示星星
 *  @2015/12/14 20:30
 */
#define IMG_GAMEWIN_STAR_1           "img_gamewin_star_1"
#define IMG_GAMEWIN_STAR_2           "img_gamewin_star_2"
#define IMG_GAMEWIN_STAR_3           "img_gamewin_star_3"
#define IMG_GAMEWIN_STAR_4           "img_gamewin_star_4"
#define IMG_GAMEWIN_STAR_5           "img_gamewin_star_5"

/** 出问题界面的所有的组件
 *  @2015/12/14 20:30
 */
#define QUESTION_BTN_CONFIRM          "btn_question_confirm"
#define QUESTION_TEXT_QUESTION        "text_question"
#define QUESTION_CHECKBOX_ANSWER_1    "checkbox_answer_1"
#define QUESTION_CHECKBOX_ANSWER_2    "checkbox_answer_2"
#define QUESTION_CHECKBOX_ANSWER_3    "checkbox_answer_3"
#define QUESTION_CHECKBOX_ANSWER_4    "checkbox_answer_4"

/** 控制的按钮接口
 *  @2015/12/14 20:30
 */
#include "IBtnControl.hpp"

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "MainCar_R.hpp"
#include "Btn_QuestionSelect.hpp"
#include "SpriteTweenBase.hpp"
#include "TooslFunction.hpp"
#include "fire_x.hpp"
#include "guaiwu_js.hpp"
#include "other_level_1.hpp"
#include "other_level_2.hpp"
#include "objSpring.hpp"
#include "Exit.hpp"




#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;


enum CarTurnType
{
    Car_R,
    Car_L
};



class MainUI : public cocos2d::Layer
{
    
    
    
public:
    
    /** 创建单例模式 单例模式的私有变量
     *  @2015/12/14 20:03
     */
    //static MainUI* _mainui;
    
    /** 设置问题号
     *  @2015/12/15 08:28
     */
    int currentQuestionNumber = 0;
    
    /** 当前选择的答案
     *  @2015/12/15 08:28
     */
    std::string currentSelectAnswer;
    
    /** 当前关卡回答正确的数量
     *  @2015/12/15 08:28
     */
    int answerCorrect = 0;
    
    
    /** 住车是否加速
     *  @2015/12/15 08:15
     */
    bool isMainCarAddSpeed = true;
    
    
    /** 左右车
     *  @2015/12/15 08:15
     */
    bool isMainCarTrun = true;
    
    /** 问题框界面
     *  @2015/12/15 08:15
     */
    cocos2d::Sprite* QuestionPage = nullptr;
    Button* btn_question_confirm = nullptr;
    Text* text_question = nullptr;
    Text* text_answer_1 = nullptr;
    Text* text_answer_2 = nullptr;
    Text* text_answer_3 = nullptr;
    Text* text_answer_4 = nullptr;
    CheckBox* checkbox_answer_1 = nullptr;
    CheckBox* checkbox_answer_2 = nullptr;
    CheckBox* checkbox_answer_3 = nullptr;
    CheckBox* checkbox_answer_4 = nullptr;
    
    
    
    /** 游戏胜利界面
     *  @2015/12/15 08:28
     */
    cocos2d::Sprite* GameVictoryPage;
    
    cocos2d::Sprite* gamevictory_star[5];
    
    
    /** 游戏失败界面
     *  @2015/12/15 08:28
     */
    cocos2d::Sprite* GameOverPage;
    
    
    /** 当前的关卡数
     *  @2015/12/15 08:28
     */
    int currentLevel = 0;
    
    /** 问题框的初始位置
     *  @2015/12/15 18:24
     */
    cocos2d::Vec2 deVect;
    
    /** 问题框的状态
     *  @2015/12/15 18:24
     */
    bool isQuestionPlayAction = true;
    
    /** 游戏胜利的状态
     *  @2015/12/15 18:55
     */
    bool isGameVictoryPlayAction = true;
    
    /** 游戏失败的状态
     *  @2015/12/15 18:55
     */
    bool isGameOverPlayAction = true;
    
    
    /** 回调选择的问题按钮
     *  @2015/12/19 14:35
     */
    class Btn_QuestionSelect* questionselect = NULL;
    
    /** 问题是否回答正确
     *  @2015/12/19 14:38
     */
    bool isQuestionAnswerCorrect = false;
    
    
    /** 车的实力
     *  @2015/12/22 17:15
     */
    class MainCar_R* mainCar;
    
    
    /** 车的实力
     *  @2015/12/22 17:15
     */
    class MainCar_R* mainCar_r;
    
    
    /** 车的实力
     *  @2015/12/22 17:15
     */
    class MainCar_L* mainCar_l;
    
    
    /** 车的速度 小轮
     *  @2015/01/05 19:35
     */
    float carSpeed_x;
    
    /** 车的速度 大轮
     *  @2015/01/05 19:35
     */
    float carSpeed_d;
    
    
    /** 遮罩层事件
     *  @2015/12/28 13:47
     */
    EventListenerTouchOneByOne* touchmasklistener;
    
    /** 遮罩层精灵
     *  @2015/12/28 13:58
     */
    Node* masklayer;
    
    /** 限制位置
     *  @2015/01/15 14:16
     */
    Node* _nodePos;
    
    /** 限制位置
     *  @2015/01/15 14:16
     */
    Node* _movePos;
    
    /** 是否移动
     *  @2015/01/15 14:16
     */
    bool _ismove = false;
    
    
public:
    
    virtual bool init();
    
    virtual void update(float ft);
    
    CREATE_FUNC(MainUI);
    
    /** 进入场景
     *  @2015/12/14 20:03
     */
    void onEnter();
    
    /** 初始化问题
     *  @2015/12/15 11:53
     */
    void initQuestion();
    
    /** 判断回答的问题正确还是错误
     *  @2015/12/15 12:43
     */
    void isAnswerQuestion(CheckBox* check);
    
    /** 主要按钮点击事件
     *  @2015/12/15 07:55
     */
    void onBtnClick(Ref* reft,Widget::TouchEventType type);
    
    /** 主要按钮点击事件
     *  @2015/12/15 07:55
     */
    void onCheckBoxSelect(Ref* reft, CheckBox::EventType type);
    
    /** 问题交替按钮
     *  @2015/12/15 07:55
     */
    void onBtnClickSelectQuestion(Ref* reft,Widget::TouchEventType type);
    
    /** 问题回答正确的方法
     *  @2015/12/15 07:55
     */
    void QuestionPassed();
    
    /** 问题回答错误的方法
     *  @2015/12/15 07:55
     */
    void QuestionFiall();
    
    /** 调用问题动画框
     *  @2015/12/15 07:55
     */
    void QuestionActionPlayed(const bool& isquestion , Btn_QuestionSelect* selectquestion);
    
    /** 调用游戏胜利界面
     *  @2015/12/15 18:50
     */
    void GameVictoryActionPlayed(bool isgamevictory);
    
    /** 调用游戏失败界面
     *  @2015/12/15 18:50
     */
    void GameOverActionPlayed(bool isgamevoer);
    
    /** 游戏过关 胜利过关
     *  @2015/12/15 08:00
     */
    void gameVictroy(std::string levelname);
    
    /** 游戏过关 胜利过关 到下一关
     *  @2015/12/15 08:00
     */
    void gameVictroyNext(int& levelname);

    /** 游戏失败 死亡结束
     *  @2015/12/15 08:00
     */
    void gameOver();
    
    /** 问题动作播放完成
     *  @2015/12/15 20:30
     */
    void QuestionFinish();
    
    /** 游戏胜利 完成动作
     *  @2015/12/15 08:00
     */
    void GameVitoryFinish();
    
    /** 游戏失败 死亡结束 完成动作
     *  @2015/12/15 08:00
      */
    void GameOverFinish();
    
    /** 设置车的位置
     *  @2015/12/21 18:05
     */
    void setMainCar_R(Node* carpos);
    
    /** 设置车的位置
     *  @2015/12/21 18:05
     */
    void setMainCar_L(Node* carpos);
    
    /** 车暂停
     *  @2015/12/22 17:05
     */
    void StopCar();
    
    
    /** 销毁车
     *  @2015/12/22 17:15
     */
    void DeleteCar();
    
    
    /** 设置车的实例
     *  @2015/12/23 15:40
     */
    void setCar(MainCar_R* car , MainCar_L* car_l);

    /** 设置左车的实例
     *  @2015/01/05 10:20
     */
    void setCar_L(MainCar_L* car_l);

    /** 设置左车的实例
     *  @2015/01/05 10:20
     */
    void setCar_R(MainCar_R* car_r);
    
    
    /** 获取左车的实例
     *  @2015/01/05 11:00
     */
    MainCar_L* getCar_L();
    
    /** 获取左车的实例
     *  @2015/01/05 11:00
     */
    MainCar_R* getCar_R();
    
    
    /** 获取车的速度
     *  @2015/01/05 19:50
     */
    float getCarSpeed_X();
    
    /** 获取车的速度
     *  @2015/01/05 19:50
     */
    float getCarSpeed_D();
    
    /** 获取车的实例
     *  @2015/12/23 15:40
     */
    MainCar_R* getCar();
    
    /** 设置主要UI实例
     *  @2015/12/23 15:40
     */
    void setMainUI();
    
    /** 设置遮罩是否显示
     *  @2015/12/28 13:53
     */
    void setShow(bool isshow);
    
    /** 获取是否死亡
     *  @2015/01/11 13:58
     */
    bool isGameOver();
    
    /** 获取是否死亡
     *  @2015/01/15 14:28
     */
    void setMovePosition(Node* nodeA, Node* nodeB,bool ism = true);
    
};




















































#endif /* MainUI_hpp */
