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
    int tiledMapWidth = GAME_TILED_WIDTH*GAME_COLS+GAME_TILED_BOARD_WIDTH*(GAME_COLS+1);
    int tiledMapHeight = GAME_TILED_HEIGHT*GAME_ROWS+GAME_TILED_BOARD_WIDTH*(GAME_ROWS+1);
    auto colorBack = LayerColor::create(Color4B(170,170,170,255),tiledMapWidth , tiledMapHeight);
//    colorBack->setAnchorPoint(Point(colorBack->getContentSize().width/2,colorBack->getContentSize().height/2));
    colorBack->setPosition(Point((GAME_SCREEN_WIDTH-tiledMapWidth)/2,(GAME_SCREEN_HEIGH-tiledMapHeight)/2));
    this->addChild(colorBack);
    
    //分数
    
    
    return true;
}