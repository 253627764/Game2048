//
//  MoveTiled.cpp
//  Game2048
//
//  Created by luowei on 14-7-9.
//
//

#include "MovedTiled.h"

void MovedTiled::showAt(int r,int c){
    
}

//将这个块移动到某行某列
void MovedTiled::moveTo(int r,int c){
    this->m_row = r;
    this->m_col = c;
    this->setPosition(Point(c*GAME_TILED_WIDTH+c+GAME_TILED_BOARD_WIDTH*(c+1),r*GAME_TILED_HEIGHT+GAME_TILED_BOARD_WIDTH*(r+1)));
    
}

bool MovedTiled::init(){
    if(!Node::init()){
        return false;
    }
    
    //背景层
    auto bk = LayerColor::create(Color4B(200,200,200,255),GAME_TILED_WIDTH,GAME_TILED_HEIGHT);
    this->addChild(bk);
    
    //数字层
    int n = rand()%10;
    this->m_number=n>0?2:4;
    
    
    
//    auto label = Label::create();
//    label->setString(StringUtils::format("%d",this->m_number));
//    label->setScale(4);
    auto label = Label::createWithSystemFont(StringUtils::format("%d",this->m_number), "宋体", 60);
    label->setPosition(Point(GAME_TILED_WIDTH/2,GAME_TILED_HEIGHT/2));
    label->setColor(Color3B::BLACK);
    bk->addChild(label);
    
    return true;
}