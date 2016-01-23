//
//  MainUI.cpp
//  DesertTour
//
//  Created by Cary on 15/12/14.
//
//

#include "MainUI.hpp"
#include "MacroAssets.hpp"
#include "TooslFunction.hpp"
#include "Desert_level.hpp"
#include "MainCar_R.hpp"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;

bool MainUI::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    auto mainui = CSLoader::createNode("LayerUI/MainUI.csb");
    addChild(mainui);
    MainUI::QuestionPage = mainui->getChildByName<Sprite*>(PAGE_QUESTION);
    MainUI::GameVictoryPage = mainui->getChildByName<Sprite*>(PAGE_GAMEWIN);
    MainUI::GameOverPage = mainui->getChildByName<Sprite*>(PAGE_GAMEOVER);
    MainUI::QuestionPage->setLocalZOrder(500001);
    MainUI::GameVictoryPage->setLocalZOrder(500003);
    MainUI::GameOverPage->setLocalZOrder(500003);
    
    Button* btn_mainui_tolevel = mainui->getChildByName<Button*>(BTN_MAINUI_TOLEVEL);
    Button* btn_mainui_restart = mainui->getChildByName<Button*>(BTN_MAINUI_RESTART);
    Button* btn_mainui_addsped = mainui->getChildByName<Button*>(BTN_MAINUI_ADDSPEED);
    Button* btn_mainui_carturn = mainui->getChildByName<Button*>(BTN_MAINUI_CARTURN);
    btn_mainui_tolevel->addTouchEventListener(CC_CALLBACK_2(MainUI::onBtnClick, this));
    btn_mainui_restart->addTouchEventListener(CC_CALLBACK_2(MainUI::onBtnClick, this));
    btn_mainui_addsped->addTouchEventListener(CC_CALLBACK_2(MainUI::onBtnClick, this));
    btn_mainui_carturn->addTouchEventListener(CC_CALLBACK_2(MainUI::onBtnClick, this));
    btn_mainui_tolevel->setLocalZOrder(10);
    btn_mainui_restart->setLocalZOrder(10);
    btn_mainui_addsped->setLocalZOrder(10);
    btn_mainui_carturn->setLocalZOrder(10);
    MainUI::text_question = MainUI::QuestionPage->getChildByName<Text*>(QUESTION_TEXT_QUESTION);
    MainUI::text_answer_1 = MainUI::QuestionPage->getChildByName<CheckBox*>(QUESTION_CHECKBOX_ANSWER_1)->getChildByName<Text*>("text_answer");
    MainUI::text_answer_2 = MainUI::QuestionPage->getChildByName<CheckBox*>(QUESTION_CHECKBOX_ANSWER_2)->getChildByName<Text*>("text_answer");
    MainUI::text_answer_3 = MainUI::QuestionPage->getChildByName<CheckBox*>(QUESTION_CHECKBOX_ANSWER_3)->getChildByName<Text*>("text_answer");
    MainUI::text_answer_4 = MainUI::QuestionPage->getChildByName<CheckBox*>(QUESTION_CHECKBOX_ANSWER_4)->getChildByName<Text*>("text_answer");
    MainUI::checkbox_answer_1 = (CheckBox*)MainUI::text_answer_1->getParent();
    MainUI::checkbox_answer_2 = (CheckBox*)MainUI::text_answer_2->getParent();
    MainUI::checkbox_answer_3 = (CheckBox*)MainUI::text_answer_3->getParent();
    MainUI::checkbox_answer_4 = (CheckBox*)MainUI::text_answer_4->getParent();
    MainUI::checkbox_answer_1->addEventListener(CC_CALLBACK_2(MainUI::onCheckBoxSelect, this));
    MainUI::checkbox_answer_2->addEventListener(CC_CALLBACK_2(MainUI::onCheckBoxSelect, this));
    MainUI::checkbox_answer_3->addEventListener(CC_CALLBACK_2(MainUI::onCheckBoxSelect, this));
    MainUI::checkbox_answer_4->addEventListener(CC_CALLBACK_2(MainUI::onCheckBoxSelect, this));
    MainUI::btn_question_confirm = MainUI::QuestionPage->getChildByName<Button*>(QUESTION_BTN_CONFIRM);
    MainUI::btn_question_confirm->addTouchEventListener(CC_CALLBACK_2(MainUI::onBtnClickSelectQuestion, this));
    MainUI::gamevictory_star[0] = MainUI::GameVictoryPage->getChildByName<Sprite*>(IMG_GAMEWIN_STAR_1);
    MainUI::gamevictory_star[1] = MainUI::GameVictoryPage->getChildByName<Sprite*>(IMG_GAMEWIN_STAR_2);
    MainUI::gamevictory_star[2] = MainUI::GameVictoryPage->getChildByName<Sprite*>(IMG_GAMEWIN_STAR_3);
    MainUI::gamevictory_star[3] = MainUI::GameVictoryPage->getChildByName<Sprite*>(IMG_GAMEWIN_STAR_4);
    MainUI::gamevictory_star[4] = MainUI::GameVictoryPage->getChildByName<Sprite*>(IMG_GAMEWIN_STAR_5);
    Button* btn_gamevictory_tolevel = MainUI::GameVictoryPage->getChildByName<Button*>(BTN_GAMEWIN_TOLEVEL);
    Button* btn_gamevictory_restart = MainUI::GameVictoryPage->getChildByName<Button*>(BTN_GAMEWIN_RESTART);
    Button* btn_gamevictory_next= MainUI::GameVictoryPage->getChildByName<Button*>(BTN_GAMEWIN_NEXT);
    btn_gamevictory_tolevel->addTouchEventListener(CC_CALLBACK_2(MainUI::onBtnClick, this));
    btn_gamevictory_restart->addTouchEventListener(CC_CALLBACK_2(MainUI::onBtnClick, this));
    btn_gamevictory_next->addTouchEventListener(CC_CALLBACK_2(MainUI::onBtnClick, this));
    Button* btn_gameover_tolevel = MainUI::GameOverPage->getChildByName<Button*>(BTN_GAMEOVER_TOLEVEL);
    Button* btn_gameover_restart = MainUI::GameOverPage->getChildByName<Button*>(BTN_GAMEOVER_RESTART);
    btn_gameover_tolevel->addTouchEventListener(CC_CALLBACK_2(MainUI::onBtnClick, this));
    btn_gameover_restart->addTouchEventListener(CC_CALLBACK_2(MainUI::onBtnClick, this));
    //获取遮罩
    masklayer = mainui->getChildByName<Node*>("FileNode_1");
    masklayer->setLocalZOrder(10);
    masklayer->setVisible(false);
    touchmasklistener = EventListenerTouchOneByOne::create();
    touchmasklistener->onTouchBegan = CC_CALLBACK_2(MainUI::onTouchBegan, this);
    touchmasklistener->onTouchMoved = CC_CALLBACK_2(MainUI::onTouchMoved, this);
    touchmasklistener->onTouchEnded = CC_CALLBACK_2(MainUI::onTouchEnded, this);
    touchmasklistener->setSwallowTouches(false);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchmasklistener, masklayer);
    
    if (MainUI::isMainCarTrun)
    {
        //初始化车的速度
        carSpeed_x = -CAR_SPEED_X;
        carSpeed_d = -CAR_SPEED_D;
    }else{
        carSpeed_x = CAR_SPEED_X;
        carSpeed_d = CAR_SPEED_D;
    }
    scheduleUpdate();
    return true;
}

void MainUI::onEnter()
{
    Layer::onEnter();
    //设置当前的关卡
    MainUI::currentLevel = 0;
    //设置按钮为不可用
    MainUI::btn_question_confirm->setEnabled(false);
    Size visibleSize =  Director::getInstance()->getVisibleSize();
    float y = MainUI::QuestionPage->getContentSize().height + visibleSize.height;
    float x = visibleSize.width/2;
    MainUI::deVect =Vec2(x, y);
    //设置问题框的位置
    MainUI::QuestionPage->setVisible(true);
    MainUI::QuestionPage->setPosition(Vec2(x, 840));
    
    //游戏胜利的界面
    for (int i =0; i<5; i++) {
        MainUI::gamevictory_star[i]->setVisible(false);
    }
    MainUI::GameVictoryPage->setScale(0, 0);
    MainUI::GameVictoryPage->setVisible(true);
    //游戏失败的界面
    MainUI::GameOverPage->setScale(0, 0);
    MainUI::GameOverPage->setVisible(true);
    MainUI::setShow(false);
}


void MainUI::update(float ft)
{
    if (_ismove) {
        if (getCar_R()->getCarNode()->getPosition().x >= _nodePos->getPosition().x) {
            getCar_R()->setObj(_movePos);
            _ismove = false;
        }
    }
}


template <class T>
int getArrayLen(T& array)
{//使用模板定义一 个函数getArrayLen,该函数将返回数组array的长度
    return (sizeof(array) / sizeof(array[0]));
}
/** 初始化问题
 *  @2015/12/15 11:53
 */
void MainUI::initQuestion()
{
    MainUI::checkbox_answer_1->setEnabled(true);
    MainUI::checkbox_answer_2->setEnabled(true);
    MainUI::checkbox_answer_3->setEnabled(true);
    MainUI::checkbox_answer_4->setEnabled(true);
    MainUI::checkbox_answer_1->setSelected(false);
    MainUI::checkbox_answer_2->setSelected(false);
    MainUI::checkbox_answer_3->setSelected(false);
    MainUI::checkbox_answer_4->setSelected(false);
    
    MainUI::checkbox_answer_1->loadTextures("Default/CheckBox_Normal.png", "Default/CheckBox_Press.png", "Default/CheckBox_Press.png", "Default/CheckBox_Disable.png", "Default/CheckBox_Press.png");
    MainUI::checkbox_answer_2->loadTextures("Default/CheckBox_Normal.png", "Default/CheckBox_Press.png", "Default/CheckBox_Press.png", "Default/CheckBox_Disable.png", "Default/CheckBox_Press.png");
    MainUI::checkbox_answer_3->loadTextures("Default/CheckBox_Normal.png", "Default/CheckBox_Press.png", "Default/CheckBox_Press.png", "Default/CheckBox_Disable.png", "Default/CheckBox_Press.png");
    MainUI::checkbox_answer_4->loadTextures("Default/CheckBox_Normal.png", "Default/CheckBox_Press.png", "Default/CheckBox_Press.png", "Default/CheckBox_Disable.png", "Default/CheckBox_Press.png");
    MainUI::btn_question_confirm->setEnabled(false);
    //设置选择的问题问题空
    MainUI::currentSelectAnswer = "";
    //获取随机数
    MainUI::currentQuestionNumber = random(0, getArrayLen(QuestionAnswer)-1);
    MainUI::text_question->setString(QuestionAnswer[MainUI::currentQuestionNumber][0]);
    MainUI::text_answer_1->setString(QuestionAnswer[MainUI::currentQuestionNumber][2]);
    MainUI::text_answer_2->setString(QuestionAnswer[MainUI::currentQuestionNumber][3]);
    MainUI::text_answer_3->setString(QuestionAnswer[MainUI::currentQuestionNumber][4]);
    MainUI::text_answer_4->setString(QuestionAnswer[MainUI::currentQuestionNumber][5]);
}

void MainUI::onBtnClick(cocos2d::Ref *reft, Widget::TouchEventType type)
{
    if (type ==Widget::TouchEventType::ENDED)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AudioAssets/audio_home/gone.wav");
        auto btn_name = dynamic_cast<Button*>(reft);
        if (btn_name->getName()==BTN_MAINUI_TOLEVEL
            || btn_name->getName()==BTN_GAMEOVER_TOLEVEL
            || btn_name->getName()==BTN_GAMEWIN_TOLEVEL)
        {
            auto scenelevel = Desert_level::createScene();
            Director::getInstance()->replaceScene(scenelevel);
        }
        else if (btn_name->getName()==BTN_MAINUI_RESTART
                 || btn_name->getName()==BTN_GAMEOVER_RESTART
                 || btn_name->getName()==BTN_GAMEWIN_RESTART)
        {
            //TODO 游戏重新开始
            string scene = Director::getInstance()->getRunningScene()->getName();
            ToolsFunction::LoadLevel(scene);
        }
        else if (btn_name->getName()==BTN_GAMEWIN_NEXT)
        {
            MainUI::gameVictroyNext(MainUI::currentLevel);
        }
        else if (btn_name->getName()==BTN_MAINUI_CARTURN)
        {
            if (this->getScene()->getName() == "level_7"
                || this->getScene()->getName() == "level_8"
                || this->getScene()->getName() == "level_10") {
                MessageBox("当前不能变换车哦", "提示");
            }else{
                if (MainUI::isMainCarTrun)
                {
                    //转换车的走向
                    carSpeed_x = -carSpeed_x;
                    carSpeed_d = -carSpeed_d;
                    auto car_l = MainCar_L::create();
                    car_l->setMainUI(this);
                    car_l->setObj(getCar_R()->getCarNode());
                    setCar_L(car_l);
                    this->getParent()->addChild(car_l);
                    if (getCar_R()->isCarOpen()) {
                        
                        car_l->setCarSpeed(carSpeed_d, carSpeed_x, true);
                    }else{
                        car_l->setCarSpeed(CAR_STOP,CAR_STOP, false);
                    }
                    //销毁当前的车
                    getCar_R()->removeFromParent();
                    //更换按钮的图片
                    btn_name->loadTextureNormal("DesertUI/MainUI/btn_rota0001.png");
                }else{
                    //转换车的走向
                    carSpeed_x = -carSpeed_x;
                    carSpeed_d = -carSpeed_d;
                    //确定
                    auto car_r = MainCar_R::create();
                    car_r->setMainUI(this);
                    car_r->setObj(getCar_L()->getCarNode());
                    setCar_R(car_r);
                    this->getParent()->addChild(car_r);
                    if (getCar_L()->isCarOpen()) {
                        car_r->setCarSpeed(carSpeed_d, carSpeed_x,true);
                    }else{
                        car_r->setCarSpeed(CAR_STOP,CAR_STOP,false);
                    }
                    //销毁当前的车
                    getCar_L()->removeFromParent();
                    //更换按钮的图片
                    btn_name->loadTextureNormal("DesertUI/MainUI/btn_rota0002.png");
                }
            }
        }
        else if (btn_name->getName()==BTN_MAINUI_ADDSPEED)
        {
            //TODO  车加速按钮
            if (!MainUI::isMainCarAddSpeed)
            {
                MainUI::isMainCarAddSpeed = true;
                carSpeed_x = carSpeed_x / 2.5;
                carSpeed_d = carSpeed_d / 2.5;
                //更换车的速度
                if (MainUI::isMainCarTrun)
                {
                    if (getCar_R()->isCarOpen())
                        getCar_R()->setCarSpeed(carSpeed_d, carSpeed_x, true);
                }else {
                    if (getCar_L()->isCarOpen())
                        getCar_L()->setCarSpeed(carSpeed_d, carSpeed_x, true);
                }
                btn_name->loadTextureNormal("DesertUI/MainUI/btn_mainui_addspeed0001.png");
            }
            else
            {
                MainUI::isMainCarAddSpeed = false;
                carSpeed_x = carSpeed_x * 2;
                carSpeed_d = carSpeed_d * 2;
                //更换车的速度
                if (MainUI::isMainCarTrun)
                {
                    if (getCar_R()->isCarOpen())
                        getCar_R()->setCarSpeed(carSpeed_d, carSpeed_x, true);
                }else {
                    if (getCar_L()->isCarOpen())
                        getCar_L()->setCarSpeed(carSpeed_d, carSpeed_x, true);
                }
                btn_name->loadTextureNormal("DesertUI/MainUI/btn_mainui_addspeed0003.png");
            }
        }
    }
}


/** 主要按钮点击事件
 *  @2015/12/15 07:55
 */
void MainUI::onCheckBoxSelect(Ref* reft, CheckBox::EventType type)
{
    if (type==CheckBox::EventType::SELECTED)
    {
        auto checkbox = dynamic_cast<CheckBox*>(reft);
        if (checkbox->getName()==QUESTION_CHECKBOX_ANSWER_1)
        {
            MainUI::currentSelectAnswer = MainUI::text_answer_1->getString();
            MainUI::isAnswerQuestion(checkbox);
        }else if (checkbox->getName()==QUESTION_CHECKBOX_ANSWER_2){
            MainUI::currentSelectAnswer = MainUI::text_answer_2->getString();
            MainUI::isAnswerQuestion(checkbox);
        }else if (checkbox->getName()==QUESTION_CHECKBOX_ANSWER_3){
            MainUI::currentSelectAnswer = MainUI::text_answer_3->getString();
            MainUI::isAnswerQuestion(checkbox);
        }else if (checkbox->getName()==QUESTION_CHECKBOX_ANSWER_4){
            MainUI::currentSelectAnswer = MainUI::text_answer_4->getString();
            MainUI::isAnswerQuestion(checkbox);
        }
        MainUI::checkbox_answer_1->setEnabled(false);
        MainUI::checkbox_answer_2->setEnabled(false);
        MainUI::checkbox_answer_3->setEnabled(false);
        MainUI::checkbox_answer_4->setEnabled(false);
        MainUI::btn_question_confirm->setEnabled(true);
    }
}


/** 判断回答的问题正确还是错误
 *  @2015/12/15 12:43
 */
void MainUI::isAnswerQuestion(CheckBox* check)
{
    //当前题号的正确答案；
    std::string currentAnser = QuestionAnswer[MainUI::currentQuestionNumber][1];
    if (MainUI::currentSelectAnswer==currentAnser) {
        check->loadTextureBackGroundSelected("DesertUI/MainUI/img_pas.png");
        check->loadTextureFrontCrossDisabled("DesertUI/MainUI/img_pas.png");
        //回答正确
        isQuestionAnswerCorrect = true;
        MainUI::QuestionPassed();
    }else{
        check->loadTextureBackGroundSelected("DesertUI/MainUI/img_fil.png");
        check->loadTextureFrontCrossDisabled("DesertUI/MainUI/img_fil.png");
        //回答错误
        isQuestionAnswerCorrect = false;
        MainUI::QuestionFiall();
    }
}

/** 问题交替按钮
 *  @2015/12/15 07:55
 */
void MainUI::onBtnClickSelectQuestion(Ref* reft,Widget::TouchEventType type)
{
    if (type==Widget::TouchEventType::ENDED)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AudioAssets/audio_home/gone.wav");
        
        //调用实例的控制按钮
        if (questionselect !=NULL)
        {
            questionselect->AnswerFinsh(isQuestionAnswerCorrect);
        }
        MainUI::QuestionActionPlayed(false,questionselect);
        MainUI::btn_question_confirm->setEnabled(false);
    }
}

/** 问题回答正确的方法
 *  @2015/12/15 07:55
 */
void MainUI::QuestionPassed()
{
    if (MainUI::answerCorrect <= 5) {
        MainUI::answerCorrect++;
    }
}

/** 问题回答错误的方法
 *  @2015/12/15 07:55
 */
void MainUI::QuestionFiall()
{
    
}



/** 调用问题动画框
 *  @2015/12/15 07:55
 */
void MainUI::QuestionActionPlayed(const bool& isquestion,  Btn_QuestionSelect* selectquestion)
{
    if (isquestion)
    {
        if (MainUI::isQuestionPlayAction)
        {
            //初始化没一次的问题
            MainUI::initQuestion();
            auto moto = MoveTo::create(0.5f, Vec2(510,300));
            auto motoin = EaseBackIn::create(moto);
            //auto motoin = EaseExponentialIn::create(moto);
            MainUI::QuestionPage->runAction(motoin);
            questionselect = selectquestion;
            
            //调用的遮罩层
            MainUI::setShow(true);
            masklayer->setLocalZOrder(QuestionPage->getLocalZOrder()-1);
            MainUI::isQuestionPlayAction =false;
        }
    }
    else
    {
        if (!MainUI::isQuestionPlayAction)
        {
            auto moto = MoveTo::create(0.5f,Vec2(510,840));
            auto motoout = EaseBackInOut::create(moto);
            //auto motoin = EaseExponentialOut::create(moto);
            MainUI::QuestionPage->runAction(motoout);
            questionselect = NULL;
            
            //调用的遮罩层
            MainUI::setShow(false);
            
            MainUI::isQuestionPlayAction =true;
        }
    }
}

/** 调用游戏胜利界面
 *  @2015/12/15 18:50
 */
void MainUI::GameVictoryActionPlayed(bool isgamevictory)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AudioAssets/audio_home/audio_gamewin.mp3");
    MainUI::gameVictroy(this->getScene()->getName());
    
    if (MainUI::answerCorrect ==1){
        MainUI::gamevictory_star[0]->setVisible(true);
        
    }
    else if(MainUI::answerCorrect ==2) {
        MainUI::gamevictory_star[0]->setVisible(true);
        MainUI::gamevictory_star[1]->setVisible(true);
        
    }
    else if(MainUI::answerCorrect ==3) {
        MainUI::gamevictory_star[0]->setVisible(true);
        MainUI::gamevictory_star[1]->setVisible(true);
        MainUI::gamevictory_star[2]->setVisible(true);
        
    }
    else if(MainUI::answerCorrect ==4) {
        MainUI::gamevictory_star[0]->setVisible(true);
        MainUI::gamevictory_star[1]->setVisible(true);
        MainUI::gamevictory_star[2]->setVisible(true);
        MainUI::gamevictory_star[3]->setVisible(true);
    }
    else if(MainUI::answerCorrect ==5) {
        MainUI::gamevictory_star[0]->setVisible(true);
        MainUI::gamevictory_star[1]->setVisible(true);
        MainUI::gamevictory_star[2]->setVisible(true);
        MainUI::gamevictory_star[3]->setVisible(true);
        MainUI::gamevictory_star[4]->setVisible(true);
    }
    if (isgamevictory)
    {
        if (MainUI::isGameVictoryPlayAction)
        {
            auto scale = ScaleTo::create(0.8f, 1.0f, 1.0f);
            auto scalein = EaseExponentialIn::create(scale);
            auto rota = RotateBy::create(0.8f, 720);
            MainUI::GameVictoryPage->runAction(Spawn::create(scalein,rota, NULL));
            
            auto delay = DelayTime::create(0.8f);
            auto afinsh = CallFunc::create(CC_CALLBACK_0(MainUI::GameVitoryFinish, this));
            MainUI::GameVictoryPage->runAction(Sequence::create(delay,afinsh, NULL));
            
            //调用的遮罩层
            masklayer->setLocalZOrder(GameVictoryPage->getLocalZOrder()-1);
            MainUI::setShow(true);
            
            MainUI::isGameVictoryPlayAction = false;
        }
    }
    else
    {
        if (!MainUI::isGameVictoryPlayAction)
        {
            auto scale = ScaleTo::create(0.8f, 0.0f, 0.0f);
            auto scalein = EaseExponentialOut::create(scale);
            auto rota = RotateBy::create(0.8f, -720);
            MainUI::GameVictoryPage->runAction(Spawn::create(scalein,rota, NULL));
            
            MainUI::isGameVictoryPlayAction = true;
        }
    }
}


/** 调用游戏失败界面
 *  @2015/12/15 18:50
 */
void MainUI::GameOverActionPlayed(bool isgamevoer)
{
    if (isgamevoer)
    {
        if (MainUI::isGameOverPlayAction)
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AudioAssets/audio_home/audio_gameover.mp3");
            auto scale = ScaleTo::create(0.8f, 1.0f, 1.0f);
            auto scalein = EaseExponentialIn::create(scale);
            auto rota = RotateBy::create(0.8f, 720);
            
            auto delay = DelayTime::create(0.8f);
            auto afinsh = CallFunc::create(CC_CALLBACK_0(MainUI::GameOverFinish, this));
            MainUI::GameOverPage->runAction(Sequence::create(delay,afinsh, NULL));
            MainUI::GameOverPage->runAction(Spawn::create(scalein,rota,NULL));
            
            //调用的遮罩层
            MainUI::setShow(true);
            masklayer->setLocalZOrder(GameOverPage->getLocalZOrder()-1);
            MainUI::isGameOverPlayAction = false;
        }
    }
    else
    {
        if (!MainUI::isGameOverPlayAction)
        {
            auto scale = ScaleTo::create(0.8f, 0.0f, 0.0f);
            auto scalein = EaseExponentialOut::create(scale);
            auto rota = RotateBy::create(0.8f, -720);
            MainUI::GameOverPage->runAction(Spawn::create(scalein,rota, NULL));
            
            MainUI::isGameOverPlayAction = true;
        }
    }
}


/** 游戏过关 胜利过关
 *  @2015/12/15 08:00
 */
void MainUI::gameVictroy(std::string levelname)
{
    std::string aa = levelname;
    int l = std::atoi(aa.substr(6,aa.length()-6).c_str());
    MainUI::currentLevel = l+1;
    if (!(l==10))
    {
        char c[10];
        sprintf(c,"level_%d", l+1);
        ToolsFunction::setSavebool(c, true);
    }
    ToolsFunction::setSaveStar(aa, MainUI::answerCorrect);
}

/** 问题动作播放完成
 *  @2015/12/15 20:30
 */
void MainUI::QuestionFinish()
{
    
}

/** 游戏胜利 完成动作
 *  @2015/12/15 08:00
 */
void MainUI::GameVitoryFinish()
{
    log("游戏成功 动作完成》》》》》》》》》》》》》》》》》》》》》》》》");
}

/** 游戏失败 死亡结束 完成动作
 *  @2015/12/15 08:00
 */
void MainUI::GameOverFinish()
{
    log("游戏失败 动作完成》》》》》》》》》》》》》》》》》》》》》》》》");
}



/** 游戏过关 胜利过关 到下一关
 *  @2015/12/15 08:00
 */
void MainUI::gameVictroyNext(int& levelname)
{
    int starcount = ToolsFunction::CountStarNumber();
    auto director = Director::getInstance();
    if (levelname==2){
        if (starcount >=ToolsFunction::AsbL2) {
            auto scene = Level_2::createScene();
            director->replaceScene(scene);
        }else{
            auto scenelevel = Desert_level::createScene();
            director->replaceScene(scenelevel);
        }
    }else if (levelname==3){
        if (starcount >=ToolsFunction::AsbL3) {
            auto scene = Level_3::createScene();
            director->replaceScene(scene);
        }else{
            auto scenelevel = Desert_level::createScene();
            director->replaceScene(scenelevel);
        }
    }else if (levelname==4){
        if (starcount >=ToolsFunction::AsbL4) {
            auto scene = Level_4::createScene();
            director->replaceScene(scene);
        }else{
            auto scenelevel = Desert_level::createScene();
            director->replaceScene(scenelevel);
        }
    }else if (levelname==5){
        if (starcount >=ToolsFunction::AsbL5) {
            auto scene = Level_5::createScene();
            director->replaceScene(scene);
        }else{
            auto scenelevel = Desert_level::createScene();
            director->replaceScene(scenelevel);
        }
    }else if (levelname==6){
        if (starcount >=ToolsFunction::AsbL6) {
            auto scene = Level_6::createScene();
            director->replaceScene(scene);
        }else{
            auto scenelevel = Desert_level::createScene();
            director->replaceScene(scenelevel);
        }
    }else if (levelname==7){
        if (starcount >=ToolsFunction::AsbL7) {
            auto scene = Level_7::createScene();
            director->replaceScene(scene);
        }else{
            auto scenelevel = Desert_level::createScene();
            director->replaceScene(scenelevel);
        }
    }else if (levelname==8){
        if (starcount >=ToolsFunction::AsbL8) {
            auto scene = Level_8::createScene();
            director->replaceScene(scene);
        }else{
            auto scenelevel = Desert_level::createScene();
            director->replaceScene(scenelevel);
        }
    }else if (levelname==9){
        if (starcount >=ToolsFunction::AsbL9) {
            auto scene = Level_9::createScene();
            director->replaceScene(scene);
        }else{
            auto scenelevel = Desert_level::createScene();
            director->replaceScene(scenelevel);
        }
    }else if (levelname==10){
        if (starcount >=ToolsFunction::AsbL10) {
            auto scene = Level_10::createScene();
            director->replaceScene(scene);
        }else{
            auto scenelevel = Desert_level::createScene();
            director->replaceScene(scenelevel);
        }
    }else if (levelname==11){
        auto scenelevel = Desert_level::createScene();
        director->replaceScene(scenelevel);
    }
}

/** 游戏失败 死亡结束
 *  @2015/12/15 08:00
 */
void MainUI::gameOver()
{
    
}


/** 设置车的位置
 *  @2015/12/21 18:05
 */
void MainUI::setMainCar_R(Node* carpos)
{
    Vec2 vec = carpos->getPosition();
    //添加出的实力
    mainCar = MainCar_R::create();
    mainCar->setAnchorPoint(Vec2(0, 0));
    Vector<Node*> anode = mainCar->getChildren();
    auto carbody = anode.at(0)->getChildByName<Node*>("img_maincarbody_1");
    carbody->setPosition(vec);
    this->addChild(mainCar);
    carpos->setVisible(false);
}

/** 设置车的位置
 *  @2015/12/21 18:05
 */
void MainUI::setMainCar_L(Node* carpos)
{
    Vec2 vec = carpos->getPosition();
    
    //添加出的实力
    mainCar = MainCar_R::create();
    Vector<Node*> anode = mainCar->getChildren();
    auto carbody = anode.at(0)->getChildByName<Node*>("img_maincarbody_1");
    carbody->setPosition(vec);
    this->addChild(mainCar);
    mainCar->setMainUI(this);
    carpos->setVisible(false);
}


/** 车暂停
 *  @2015/12/22 17:05
 */
void MainUI::StopCar()
{
    auto mcar = mainCar;
    mcar->StopCar();
}


/** 销毁车
 *  @2015/12/22 17:15
 */
void MainUI::DeleteCar()
{
    mainCar->removeFromParent();
}

/** 获取车的实例
 *  @2015/12/23 15:40
 */
void MainUI::setCar(MainCar_R* car_r , MainCar_L* car_l)
{
    mainCar =car_r;
    mainCar_l =car_l;
}


/** 设置左车的实例
 *  @2015/01/05 10:20
 */
void MainUI::setCar_L(MainCar_L* car_l)
{
    MainUI::isMainCarTrun = false;
    mainCar_l = car_l;
}

/** 设置左车的实例
 *  @2015/01/05 10:20
 */
void MainUI::setCar_R(MainCar_R* car_r)
{
    MainUI::isMainCarTrun = true;
    mainCar_r = car_r;
}


/** 获取左车的实例
 *  @2015/01/05 11:00
 */
MainCar_L* MainUI::getCar_L()
{
    return mainCar_l ;
}

/** 获取左车的实例
 *  @2015/01/05 11:00
 */
MainCar_R* MainUI::getCar_R()
{
    return  mainCar_r;
}


/** 获取车的实例
 *  @2015/12/23 15:40
 */
MainCar_R* MainUI::getCar()
{
    return  mainCar;
}

/** 获取车的速度
 *  @2015/01/05 19:50
 */
float MainUI::getCarSpeed_X()
{
    return carSpeed_x;
}

/** 获取车的速度
 *  @2015/01/05 19:50
 */
float MainUI::getCarSpeed_D()
{
    return carSpeed_d;
}

/** 设置遮罩是否显示
 *  @2015/12/28 13:53
 */
void MainUI::setShow(bool isshow)
{
    if (isshow)
    {
        masklayer->setVisible(true);
        touchmasklistener->setSwallowTouches(true);
    }else{
        masklayer->setVisible(false);
        touchmasklistener->setSwallowTouches(false);
    }
}

/** 获取是否死亡
 *  @2015/01/11 13:58
 */
bool MainUI::isGameOver()
{
    return MainUI::isGameOverPlayAction;
}

/** 获取是否死亡
 *  @2015/01/15 14:28
 */
void MainUI::setMovePosition(Node* nodeA, Node* nodeB,bool ism)
{
    _nodePos = nodeA;
    _movePos = nodeB;
    _ismove = ism;
}

/***************************************遮罩层**************************************/












