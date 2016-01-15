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

#include "ui/CocosGUI.h"

using namespace cocos2d;

class SpriteTweenBase : public cocos2d::Sprite
{

private:
    
    cocos2d::Sprite* _sprite;
    
    Vec2 _currentvec2;
    Vec2 _tovec2;
    
public:
    
    void initSpriteTween(cocos2d::Sprite* sprite)
    {
        this->_sprite = this;

        _currentvec2 = sprite->getPosition();
        
        this->setPosition(sprite->getPosition());
        this->setName(sprite->getName());
        
        addChild(this->_sprite);
    }
    
    /** 物体向前播放动画
     *  @2015/12/19 17:00
     */
    void PlayForwordAction(const cocos2d::Vec2& position)
    {
        _tovec2 =position;
        auto pa = MoveTo::create(0.8f,_tovec2);
        this->_sprite->runAction(pa);
    }
    
    /** 物体向后播放动画
     *  @2015/12/19 17:00
     */
    void PlayReverseAction()
    {
        auto pa = MoveTo::create(0.8f,_currentvec2);
        this->_sprite->runAction(pa);
    
    }
    
    // implement the "static create()" method manually
    CREATE_FUNC(SpriteTweenBase);

};




#endif /* SpriteTweenBase_hpp */
