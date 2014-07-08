//
//  GameScene.cpp
//  Game2048
//
//  Created by luowei on 14-7-8.
//
//

#include "GameScene.h"

Scene * Game::createScene(){
    auto scene = Scene::create();
    auto layer = Game::create();
    scene->addChild(layer);
    return scene;
}

bool Game::init(){
    if(!Layer::init()){
        return false;
    }
    
    //初始化游戏标题
    auto labelGame=Label::createWithBMFont("futura-48.fnt","2048");
    labelGame->setScale(2);
    labelGame->setPosition(Point(labelGame->getContentSize().width,GAME_SCREEN_HEIGH-labelGame->getContentSize().height));
    this->addChild(labelGame);
    
    //初始化游戏网格
    
    
    //分数
    
    
    return true;
}