//
//  SplashScene.cpp
//  Game2048
//
//  Created by luowei on 14-7-8.
//
//

#include "SplashScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;


bool Splash::init(){
    if(!Layer::init()){
        return false;
    }
    //显示游戏名称
    auto labelGame=Label::createWithBMFont("futura-48.fnt","2048");
    labelGame->setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGH/2));
    labelGame->setScale(0.5);
    this->addChild(labelGame);
    
    //显示制作单位
    auto labelGameVec=Label::createWithBMFont("futura-48.fnt","luowei 2014.6.28");
    labelGameVec->setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGH/4));
    labelGame->setScale(2);
    this->addChild(labelGameVec);
    
    //计划任务3秒钟后，自动跳到游戏场景
    this->scheduleOnce(schedule_selector(Splash::jumpToGame), 3);
                                                                                                                                                        
    return true;
}

void Splash::jumpToGame(float t){
    //音效的加载
    SimpleAudioEngine::getInstance()->preloadEffect("move1.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("moveClear.wav");
    
    auto scene = Game::createScene();
    //场景切换
    Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5, scene));
    
}

Scene * Splash::createScene(){
    auto scene = Scene::create();
    auto layer = Splash::create();
    scene->addChild(layer);
    return scene;
}