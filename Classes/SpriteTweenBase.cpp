//
//  SpriteTweenBase.cpp
//  DesertTour
//
//  Created by Cary on 15/12/19.
//
//

#include "SpriteTweenBase.hpp"
#include "Archery.hpp"

bool SpriteTweenBase::init()
{
    if (!Sprite::init()) {
        return false;
    }
    this->setTexture("DesertUI/Level/level_9/bomb.png");
    this->setScale(0.68f);
    
    auto ontouchEvent = EventListenerTouchOneByOne::create();
    ontouchEvent->setSwallowTouches(true);
    //触摸开始
    ontouchEvent->onTouchBegan = [=](Touch* touch, Event* event)
    {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
        if (target->getBoundingBox().containsPoint(pos)) {
            return true;
        }
        return false;
    };
    //触摸移动
    ontouchEvent->onTouchMoved = [=](Touch* touch, Event* event)
    {
        //获取角度
        float x = this->getPosition().x - touch->getLocation().x;
        float y = this->getPosition().y - touch->getLocation().y;
        angle =  atan2(x, y) * 180 / 3.1415926535898;
        angle = angle < 1 ? angle + 180 : angle - 180.0f;
        this->setRotation(angle + 180.0f);
    };
    //触摸结束
    ontouchEvent->onTouchEnded = [=](Touch* touch, Event* event)
    {
        float angleX = 2800 * cos(((angle - 90) * -1) * M_PI / 180);
        float angleY = 2800 * sin(((angle - 90) * -1) * M_PI / 180);
        
        auto  partic = ParticleSystemQuad::create("Effect/bomoeff.plist");
        //partic->postStep();
        partic->setPosition(Vec2(69.62f, 6.94f));
        partic->setRotation(180.0f);
        this->addChild(partic);
        Bullet* b = Bullet::create();
        //随机数
        int remod = random(1, 100);
        if(remod > 80){
            b->setAttack(this->_attack * 8);
        }else{
            b->setAttack(this->_attack);
        }
        b->setPosition(this->getPosition());
        this->getParent()->addChild(b,1);
        b->getPhysicsBody()->setVelocity(Vec2(angleX,angleY));
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ontouchEvent, this);
    return true;
}

void SpriteTweenBase::update(float ft)
{
    
}

/** 问题回答
 *  @2015/12/28 15:41
 */
void SpriteTweenBase::AnswerPassed(bool ispass)
{

}

/** 控制的按钮是否启用
 *  @2015/12/28 15:41
 */
void SpriteTweenBase::IsBtnEnable(bool isbtn)
{
    this->_attack = this->_attack * 2.0f;
}





