//
//  MoveTiled.cpp
//  Game2048
//
//  Created by luowei on 14-7-9.
//
//

#include "MovedTiled.h"

void MovedTiled::showAt(int r,int c){
    moveTo(r, c);
    //动画
    auto bk = this->getChildByTag(110);
    bk->runAction(Sequence::create(ScaleTo::create(0.2, 0.8),ScaleTo::create(0.2, 1.2),ScaleTo::create(0.2, 1), NULL));
    
}

//将这个块移动到某行某列
void MovedTiled::moveTo(int r,int c){
    this->m_row = r;
    this->m_col = c;
    this->setPosition(Point(c*GAME_TILED_WIDTH+c+GAME_TILED_BOARD_WIDTH*(c+1),r*GAME_TILED_HEIGHT+GAME_TILED_BOARD_WIDTH*(r+1)));
    
}

//翻倍
void MovedTiled::doubleNumber(){
    this->m_number = this->m_number*2;
    auto bk = this->getChildByTag(110);
    Label * label = (Label*)bk->getChildByTag(10);
    label->setString(StringUtils::format("%d",m_number));
    //动画效果
    bk->runAction(Sequence::create(ScaleTo::create(0.2, 0.8),ScaleTo::create(0.2, 1.2),ScaleTo::create(0.2, 1), NULL));
    
    switch (this->m_number) {
        case 2:
            bk->setColor(Color3B(230,220,210));
            
        case 4:
            bk->setColor(Color3B(230,210,190));
            break;
        case 8:
            bk->setColor(Color3B(230,150,100));
            label->setColor(Color3B(255,255,255));
            break;
        case 16:
            bk->setColor(Color3B(230,120,80));
            label->setColor(Color3B(255,255,255));
            break;
        case 32:
            bk->setColor(Color3B(230,100,90));
            label->setColor(Color3B(255,255,255));
            break;
        case 64:
            bk->setColor(Color3B(230,70,60));
            label->setColor(Color3B(255,255,255));
            break;
        case 128:
            bk->setColor(Color3B(230,190,60));
            label->setColor(Color3B(255,255,255));
            break;
        case 256:
            bk->setColor(Color3B(230,190,60));
            label->setColor(Color3B(255,255,255));
            break;
        case 512:
            bk->setColor(Color3B(230,190,60));
            label->setColor(Color3B(255,255,255));
            break;
        case 1024:
        case 2048:
            label->setScale(0.5);
            bk->setColor(Color3B(210,180,30));
            label->setColor(Color3B(255,255,255));
    }
    
}

bool MovedTiled::init(){
    if(!Node::init()){
        return false;
    }
    
    //背景层
    auto bk = LayerColor::create(Color4B(200,200,200,255),GAME_TILED_WIDTH,GAME_TILED_HEIGHT);
    bk->setTag(110);
    this->addChild(bk);
    
    //数字层
    int n = rand()%10;
    this->m_number=n>0?2:4;
    
    
    
//    auto label = Label::create();
//    label->setString(StringUtils::format("%d",this->m_number));
//    label->setScale(4);
    
    switch (this->m_number) {
        case 2:
            bk->setColor(Color3B(230,220,210));
            
        case 4:
            bk->setColor(Color3B(230,210,190));
            break;
    }
    
    auto label = Label::createWithSystemFont(StringUtils::format("%d",this->m_number), "宋体", 60);
    label->setPosition(Point(GAME_TILED_WIDTH/2,GAME_TILED_HEIGHT/2));
    label->setColor(Color3B::BLACK);
    label->setTag(10);
    bk->addChild(label);
    
    return true;
}