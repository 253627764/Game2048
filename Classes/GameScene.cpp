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
    
    //初始化网格中的每一块
    for(int row=0;row < GAME_ROWS;row++){
        for (int col=0; col < GAME_COLS; col++) {
            auto layerTiled = LayerColor::create(Color4B(70,70,70,255), GAME_TILED_WIDTH, GAME_TILED_HEIGHT);
            layerTiled->setPosition(Point(GAME_TILED_WIDTH*col+GAME_TILED_BOARD_WIDTH*(col+1),GAME_TILED_HEIGHT*row+GAME_TILED_BOARD_WIDTH*(row+1)));
            colorBack->addChild(layerTiled);
        }
    }
    
    //初始化数字块
    auto tiled = MovedTiled::create();
    int num = rand()%16;
    colorBack->addChild(tiled);
    tiled->moveTo(num/GAME_ROWS,num%GAME_COLS);
    
    //分数
    
    
    return true;
}