//
//  Level_5.cpp
//  DesertTour
//
//  Created by Cary on 15/12/26.
//
//

#include "Level_5.hpp"


#include "MainUI.hpp"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;



Scene* Level_5::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->setName("level_5");
    
    /** 吧物理世界设置成式调模式
     *  @2015/12/16 11:15
     */
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    scene->getPhysicsWorld()->setGravity(Vec2(0 , -800.0f));
    auto layer = Level_5::create();
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Level_5::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ){
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visiblePoint = Director::getInstance()->getVisibleOrigin();
    auto root_level_5 = CSLoader::createNode("Scene/LevelScene/Level_5.csb");
    root_level_5->setTag(100001);
    this->addChild(root_level_5);
    //设置物理 空心世界
    PhysicsBody* psworld =PhysicsBody::createEdgeBox(Size(visibleSize.width,visibleSize.height*1.2),PHYSICSBODY_MATERIAL_DEFAULT,2);
    psworld->setCategoryBitmask(0x01);
    psworld->setCollisionBitmask(0x01);
    psworld->setContactTestBitmask(0x01);
    root_level_5->setPhysicsBody(psworld);
    //火把
    Node* hb1 = root_level_5->getChildByName<Node*>("FileNode_1");
    //火把
    Node* hb2 = root_level_5->getChildByName<Node*>("FileNode_1_0");
    fire_x* fhb1 = fire_x::create();
    fhb1->setObject(hb1);
    addChild(fhb1);
    fire_x* fhb2 = fire_x::create();
    fhb2->setObject(hb2);
    addChild(fhb2);
    //完成退出
    Sprite* exitl5 = root_level_5->getChildByName<Sprite*>("img_next_27");
    //主要车
    Sprite* carl5 = root_level_5->getChildByName<Sprite*>("img_maincarbody_1");
    //按钮一
    Sprite* btnl5_1 = root_level_5->getChildByName<Sprite*>("btn_010001_50");
    //按钮二
    anim_l5_2 = root_level_5->getChildByName<Node*>("FileNode_2_kill");
    //按钮三
    Sprite* btnl5_3 = root_level_5->getChildByName<Sprite*>("btn_010001_50_0");
    //问题1
    Sprite* questionl4_1 = root_level_5->getChildByName<Sprite*>("anim_question0001_51_0");
    //问题2
    Sprite* questionl4_2 = root_level_5->getChildByName<Sprite*>("anim_question0001_51");
    //问题3
    Sprite* questionl4_3 = root_level_5->getChildByName<Sprite*>("anim_question0001_25");
    //怪物a
    Sprite* monsterl5_0 = root_level_5->getChildByName<Sprite*>("monster_18");
    //怪物
    Sprite* monsterl5_1 = root_level_5->getChildByName<Sprite*>("anim_guaiwu_1");
    //按钮二
    Sprite* monsterl5_2 = root_level_5->getChildByName<Sprite*>("btn_010001_22_0");
    //按钮二
    Sprite* monsterl5_3 = root_level_5->getChildByName<Sprite*>("btn_010001_22_0_0");
    //地面按钮
    Sprite* btngroundl5_2 = root_level_5->getChildByName<Sprite*>("btn_dicar0001_9");
    //地面右上
    Sprite* groundl5_1 = root_level_5->getChildByName<Sprite*>("td4_47_2");
    //地面下
    Sprite* groundl5_2 = root_level_5->getChildByName<Sprite*>("d1_3");
    //地面左上
    Sprite* groundl5_5 = root_level_5->getChildByName<Sprite*>("td4_47_1");
    //地面右上
    Sprite* groundl5_6 = root_level_5->getChildByName<Sprite*>("td4_47_3");
    //弹簧
    Sprite* sprs = root_level_5->getChildByName<Sprite*>("tur0001_47");
    //怪物门
    Sprite* gate = root_level_5->getChildByName<Sprite*>("d3_5");
    //yidong
    Sprite* move_17 = root_level_5->getChildByName<Sprite*>("move_17");
    //电网
    ParticleSystemQuad* particle_1 = root_level_5->getChildByName<ParticleSystemQuad*>("Particle_1");
    particle_1->setContentSize(Size(26.0f,200.0f));
    ToolsFunction::setPhyDynamicSpriteBox(move_17);
    ToolsFunction::setPhyDynamicSpriteBox(groundl5_1);
    ToolsFunction::setPhyDynamicSpriteBox(groundl5_2);
    ToolsFunction::setPhyDynamicSpriteBox(groundl5_5);
    ToolsFunction::setPhyDynamicSpriteBox(groundl5_6);
    
    //设置刚体
    PhysicsBody* psworld2 =PhysicsBody::createBox(Size(particle_1->getContentSize().width,particle_1->getContentSize().height));
    psworld2->setPositionOffset(Vec2(-13.0f, -110.0f));
    //火的碰撞掩码
    psworld2->setTag(PHY_TAG_KILL_FIRE);
    //设置触发 掩码
    psworld2->setContactTestBitmask(0x01);
    psworld2->setCollisionBitmask(0x02);
    psworld2->setDynamic(false);
    particle_1->setPhysicsBody(psworld2);
    
    //添加地面按钮
    Btn_Ground_1* btngr = Btn_Ground_1::create();
    btngr->setObj(btngroundl5_2);
    addChild(btngr);
    
    //创建主要UI界面
    mainui = MainUI::create();
    auto maincar_r = MainCar_R::create();
    mainui->setCar_R(maincar_r);
    maincar_r->setMainUI(mainui);
    maincar_r->setObj(carl5);
    addChild(maincar_r,10);
    addChild(mainui,3000);
    //退出
    Exit* eit = Exit::create();
    eit->setObj(exitl5);
    addChild(eit);
    
    Btn_QuestionSelect* qbs2 = Btn_QuestionSelect::create();
    qbs2->setObj(questionl4_1);
    qbs2->setIBtnMainUI(mainui, btngr);
    addChild(qbs2,30);
    //弹簧按按钮
    Btn_Standard* bs2 = Btn_Standard::create();
    bs2->setObj(btnl5_1);
    addChild(bs2,30);
    Btn_QuestionSelect* qbs3 = Btn_QuestionSelect::create();
    qbs3->setObj(questionl4_2);
    qbs3->setIBtnMainUI(mainui, bs2);
    addChild(qbs3,30);
    //怪物，门
    Btn_Standard* bs3 = Btn_Standard::create();
    bs3->setObj(btnl5_3);
    addChild(bs3,30);
    Btn_QuestionSelect* qbs4 = Btn_QuestionSelect::create();
    qbs4->setObj(questionl4_3);
    qbs4->setIBtnMainUI(mainui, bs3);
    addChild(qbs4,30);
    
    Layer* dlyer = Layer::create();
    dlyer->addChild(groundl5_5);
    addChild(dlyer);
    //怪物移动
    guaiwu_js* gu = guaiwu_js::create();
    gu->setGuanwu(monsterl5_1);
    gu->setMovePosition(monsterl5_2, monsterl5_3, 20.0f);
    addChild(gu);
    PhysicsBody* gua = PhysicsBody::createBox(monsterl5_0->getContentSize());
    gua->setTag(400030);
    gua->setRotationEnable(false);
    gua->setCategoryBitmask(0x01);
    gua->setCollisionBitmask(0x02);
    gua->setContactTestBitmask(0x01);
    gua->setDynamic(true);
    monsterl5_0->setPhysicsBody(gua);
    //添加力度
    bs2->getBtn()->addTouchEventListener([=](Ref* reft, Widget::TouchEventType type)
                                         {
                                             if (type==Widget::TouchEventType::ENDED) {
                                                 //bs2->PlayEffect();
                                                 //spr->addForce(Vec2(1000.0f, 1500.0f));
                                                 if (ismove) {
                                                     auto moveto = MoveTo::create(0.8f, Vec2(384.2f, move_17->getPosition().y));
                                                     move_17->runAction(moveto);
                                                     ismove = false;
                                                 }else{
                                                     auto moveto = MoveTo::create(0.8f, Vec2(159.2f, move_17->getPosition().y));
                                                     move_17->runAction(moveto);
                                                     ismove = true;
                                                 }
                                             }
                                         });
    //关门
    bs3->getBtn()->addTouchEventListener([=](Ref* reft, Widget::TouchEventType type)
                                         {
                                             if (type==Widget::TouchEventType::ENDED) {
                                                 bs2->PlayEffect();
                                                 auto scal = ScaleTo::create(1.0f, -1, 1);
                                                 gate->runAction(scal);
                                                 gua->setEnabled(false);
                                             }
                                         });
    //地面按钮
    btngr->onCallbackTest_2([=]()
                            {
                                if (particle_1) {
                                    particle_1->setVisible(false);
                                    particle_1->getPhysicsBody()->setEnabled(false);
                                }
                            });
    
    
    //怪物动画刚体
    Sprite* sprsphys = root_level_5->getChildByName<Sprite*>("btn_010001_22_1");
    sprsphys->setVisible(false);
    PhysicsBody* guaup = PhysicsBody::createBox(Size(sprsphys->getContentSize().width*1.5f,sprsphys->getContentSize().height));
    guaup->setTag(PHY_TAG_KILL_UP);
    guaup->setRotationEnable(false);
    guaup->setCategoryBitmask(0x01);
    guaup->setCollisionBitmask(0x02);
    guaup->setContactTestBitmask(0x01);
    guaup->setDynamic(true);
    sprsphys->setPhysicsBody(guaup);
    
    //播放怪物动画
    anim = CSLoader::createTimeline("Node/level_animation/l5_updown.csb");
    anim->gotoFrameAndPlay(0, 320, true);
    root_level_5->runAction(anim);
    //怪物下来
    anim->addFrameEndCallFunc(29, "a", [=]()
                              {
                                  guaup->setEnabled(true);
                              });
    //怪物下来
    anim->addFrameEndCallFunc(30, "b", [=]()
                              {
                                 guaup->setEnabled(true);
                              });
    //怪物下来
    anim->addFrameEndCallFunc(74, "c", [=]()
                              {
                                  guaup->setEnabled(false);
                              });
    //怪物下来
    anim->addFrameEndCallFunc(75, "d", [=]()
                              {
                                  guaup->setEnabled(false);
                              });
    scheduleUpdate();
    return true;
}

/** 场景更新函数
 *  @2015/01/11 11:30
 */
void Level_5::update(float dt)
{
    if (iskill)
    {
        if (mainui)
        {
            if (!mainui->isGameOver()) {
                anim_l5_2->setVisible(false);
                anim->gotoFrameAndPause(0);
                iskill = false;
            }
        }
    }
}

















