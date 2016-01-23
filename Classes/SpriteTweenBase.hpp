//
//  SpriteTweenBase.hpp
//  DesertTour
//
//  Created by Cary on 15/12/19.
//
//

#ifndef SpriteTweenBase_hpp
#define SpriteTweenBase_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "IBtnControl.hpp"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class SpriteTweenBase : public cocos2d::Sprite , public IBtnControl
{

private:
    
    cocos2d::Sprite* _sprite;
    float angle;
    
    float _attack = 33.0f;
    
    ParticleSystemQuad* partic;
    
public:
    
    virtual bool init();
    
    virtual void update(float ft);
    
    
    /** 问题回答
     *  @2015/12/28 15:41
     */
    virtual void AnswerPassed(bool ispass);
    
    /** 控制的按钮是否启用
     *  @2015/12/28 15:41
     */
    virtual void IsBtnEnable(bool isbtn);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SpriteTweenBase);
};




#endif /* SpriteTweenBase_hpp */
