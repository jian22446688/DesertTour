//
//  Level_2.cpp
//  DesertTour
//
//  Created by Cary on 15/12/15.
//
//

#include "Level_2.hpp"
#include "MainUI.hpp"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "other_level_2.hpp"
#include "HelloWorldScene.h"




USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;



Scene* Level_2::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->setName("level_2");
    
    /** 吧物理世界设置成式调模式
     *  @2015/12/16 11:15
     */
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    scene->getPhysicsWorld()->setGravity(Vec2(0 , -800.0f));
    
    // 'layer' is an autorelease object
    auto layer = Level_2::create();
      // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Level_2::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visiblePoint = Director::getInstance()->getVisibleOrigin();
    
    auto root_level_2 = CSLoader::createNode("Scene/LevelScene/Level_2.csb");
    root_level_2->setTag(100001);
    this->addChild(root_level_2);
    
    
    //设置物理 空心世界
    PhysicsBody* psworld =PhysicsBody::createEdgeBox(visibleSize*1.5,PHYSICSBODY_MATERIAL_DEFAULT,2);
    psworld->setCategoryBitmask(0x01);
    psworld->setCollisionBitmask(0x01);
    psworld->setContactTestBitmask(0x01);
    root_level_2->setPhysicsBody(psworld);
    
    
    //素材火把添加；
    auto hb1 = root_level_2->getChildByName<Sprite*>("FileNode_1_0");
    auto hb2 = root_level_2->getChildByName<Sprite*>("FileNode_1");
    
    //添加一个火把
    auto ohb1 = fire_x::create();
    ohb1->setObject(hb1);
    root_level_2->addChild(ohb1);
    //添加二个火把
    auto ohb2 = fire_x::create();
    ohb2->setObject(hb2);
    root_level_2->addChild(ohb2);
    
    //设置 物理世界里面的 静态 刚体
    Sprite* phys1 = root_level_2->getChildByName<Sprite*>("img_ground_04");
    Sprite* phys2 = root_level_2->getChildByName<Sprite*>("img_ground_05_25");
    Sprite* phys3 = root_level_2->getChildByName<Sprite*>("img_ground_06");
    ToolsFunction::setPhyDynamicSpriteBox(phys1);
    ToolsFunction::setPhyDynamicSpriteBox(phys2);
    ToolsFunction::setPhyDynamicSpriteBox(phys3);

    //设置多边形的 物理刚体
    Sprite* phys4 = root_level_2->getChildByName<Sprite*>("img_ground_03");
    //四个二维数组点 组成多边形
    Vec2 pa[4] = {
        Vec2(-phys4->getContentSize().width/2,-phys4->getContentSize().height/2),
        Vec2(-phys4->getContentSize().width/2,phys4->getContentSize().height/2-2),
        Vec2(-phys4->getContentSize().width/3+150 ,phys4->getContentSize().height/2-2),
        Vec2(phys4->getContentSize().width/2,-phys4->getContentSize().height/2)};
    auto aa = PhysicsBody::createPolygon(pa, 4);
    aa->setDynamic(false);
    aa->setLinearDamping(5000.0f);
    phys4->setPhysicsBody(aa);
    
    
    //退出的
    Sprite* ni1 = root_level_2->getChildByName<Sprite*>("img_next_27");
    auto nexit = Exit::create();
    nexit->setObj(ni1);
    addChild(nexit);

    //火的精灵
    Sprite* fire1 = root_level_2->getChildByName<Node*>("FileNode_6")->getChildByName<Sprite*>("anim_huo0001_1");
    //设置刚体
    PhysicsBody* psworld2 =PhysicsBody::createBox(Size(fire1->getContentSize().width-40,fire1->getContentSize().height-20));
    //火的碰撞掩码
    psworld2->setTag(PHY_TAG_KILL_FIRE);
    //设置触发 掩码
    psworld2->setContactTestBitmask(0x01);
    psworld2->setCollisionBitmask(0x02);
    psworld2->setDynamic(false);
    fire1->setPhysicsBody(psworld2);
    //帧动画 不能使用精灵运行帧动画
    auto fireh1 = CSLoader::createTimeline("Node/animation/L2_fire.csb");
    fireh1->gotoFrameAndPlay(0, 33, true);
    root_level_2->runAction(fireh1);

    
    //获取车的位置
    Sprite* mycar = root_level_2->getChildByName<Sprite*>("img_maincarbody_9");
    //创建主要UI界面
    mainui = MainUI::create();
    auto maincar = MainCar_R::create();
    mainui->setCar_R(maincar);
    maincar->setMainUI(mainui);
    maincar->setObj(mycar);
    addChild(maincar);
    addChild(mainui,3000);
    
    //添加第一个怪物
    //FileNode_5
    
    Node* jsa1 = root_level_2->getChildByName<Node*>("FileNode_5");
    
    Sprite* psa1 = root_level_2->getChildByName<Sprite*>("btn_010001_59_0_0");
    Sprite* psa2 = root_level_2->getChildByName<Sprite*>("btn_010001_59_0_0_0");
    Sprite* psa3 = root_level_2->getChildByName<Sprite*>("btn_010001_59_2");
    
    psa3->setVisible(false);
    
    //第一个怪物
    guaiwu_js* gw = guaiwu_js::create();
    gw->setGuanwu(jsa1);
    gw->setMovePosition(psa2, psa1, 18.0f);
    addChild(gw);
    
    
    
    //获取肉的精灵
    Sprite* rm = root_level_2->getChildByName<Sprite*>("s22_43");
    Sprite* r = root_level_2->getChildByName<Sprite*>("s23_50");
    r->setVisible(false);
    //设置肉的碰撞刚体
    PhysicsBody* phyr = PhysicsBody::createBox(Size(r->getContentSize().width/3,r->getContentSize().height-3));
    phyr->setEnabled(false);
    //设置触发 掩码
    phyr->setContactTestBitmask(0x01);
    phyr->setCollisionBitmask(0x02);
    phyr->setTag(400006);
    
    phyr->setRotationEnable(true);
    r->setPhysicsBody(phyr);
    
    //phyr->setCategoryBitmask(0x01);
    
    
    //火的按钮
    Sprite* h1 = root_level_2->getChildByName<Sprite*>("btn_010001_59_1");
    //实物的按钮
    Sprite* h2 = root_level_2->getChildByName<Sprite*>("btn_010001_59");
    //火的 问题 按钮
    Sprite* qh1 = root_level_2->getChildByName<Sprite*>("anim_question0001_60_0");
    //实物 问题 的按钮
    Sprite* qh2 = root_level_2->getChildByName<Sprite*>("anim_question0001_60");
    
    //按钮1
    Btn_Standard* hba1 =Btn_Standard::create();
    hba1->setObj(h1);
    addChild(hba1);
    hba1->getBtn()->addTouchEventListener([=](Ref* reft,Widget::TouchEventType type)
                                          {
                                              if (type ==Widget::TouchEventType::ENDED)
                                              {
                                                  hba1->PlayEffect();
                                                  //控制火的按钮
                                                  fireh1->gotoFrameAndPause(36);
                                                  fire1->getPhysicsBody()->setEnabled(false);
                                              }
                                          });
    
    //按钮2
    Btn_Standard* hba2 =Btn_Standard::create();
    hba2->setObj(h2);
    addChild(hba2);
    hba2->getBtn()->addTouchEventListener([=](Ref* reft,Widget::TouchEventType type)
                                          {
                                              if (type ==Widget::TouchEventType::ENDED)
                                              {
                                                  hba1->PlayEffect();
                                                //控制肉的按钮
                                                  //gw->setEat();
                                                  hba2->getBtn()->setEnabled(false);
                                                  rm->setVisible(false);
                                                  r->setVisible(true);
                                                  r->getPhysicsBody()->setEnabled(true);
                                                  gw->Reverse(r);
                                                  //更换怪物的移动位置
                                                  gw->setMovePosition(psa3, psa1, 68.0f);
                                              }
                                          });
    
    
    //第一个 按钮的 问题
    Btn_QuestionSelect* qhba1 = Btn_QuestionSelect::create();
    qhba1->setObj(qh1);
    qhba1->setIBtnMainUI(mainui, hba1);
    addChild(qhba1);
    
    //第二个 按钮的 问题
    Btn_QuestionSelect* qhba2 = Btn_QuestionSelect::create();
    qhba2->setObj(qh2);
    qhba2->setIBtnMainUI(mainui, hba2);
    addChild(qhba2);
    
    
    //添加地雷
    Node* nh2 = root_level_2->getChildByName<Node*>("FileNode_8");
    
    Bombed* bm = Bombed::create();
    bm->setObj(nh2);
    bm->setBombbri(phys3);
    addChild(bm);
    Sprite* qbh2 = root_level_2->getChildByName<Sprite*>("anim_question0001_61");
    //第二个 按钮的 问题
    Btn_QuestionSelect* qhbba2 = Btn_QuestionSelect::create();
    qhbba2->setObj(qbh2);
    qhbba2->setIBtnMainUI(mainui, bm);
    addChild(qhbba2);
    

    return true;
}

















































