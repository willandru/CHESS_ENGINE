#include "GameScreen.h"
#include "ScreenManager.h"

extern ScreenManager gScreenManager;

void GameScreen::onEnter(){
    back = Button(100,100,200,50,"BACK");
    back.setOnClick([](){
        gScreenManager.setScreen(ScreenType::MainMenu);
    });
}

void GameScreen::update(float dt){
    back.update(150,120,false);
}

void GameScreen::render(){
    back.render();
}

void GameScreen::onExit(){}