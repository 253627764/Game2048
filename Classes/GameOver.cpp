//
//  GameOver.cpp
//  Game2048
//
//  Created by luowei on 14-7-13.
//
//

#include "GameOver.h"
#include "gamedefine.h"
#include "GameScene.h"


bool GameOver::init(){
    if(!Layer::init()){
        return false;
    }
    
    //初始化游戏标题
    auto labelGameOver=Label::createWithBMFont("futura-48.fnt","Game Over!");
    labelGameOver->setScale(2);
    labelGameOver->setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGH/2));
    this->addChild(labelGameOver);
    
    //重新开始游戏
    auto restartGame=Label::createWithBMFont("futura-48.fnt","Restart Game");
    auto restartGameItem = MenuItemLabel::create(restartGame,CC_CALLBACK_1(GameOver::menuCallBack,this));
    restartGameItem->setPosition(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGH/4);
    
    auto menu = Menu::create(restartGameItem,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    return true;
}

void GameOver::menuCallBack(Ref* pObject){
    auto scene = Game::createScene();
    Director::getInstance()->replaceScene(TransitionFadeDown::create(0.5,scene));
}

Scene* GameOver::createScene(){
    auto scene = Scene::create();
    auto layer = GameOver::create();
    scene->addChild(layer);
    return scene;
}
