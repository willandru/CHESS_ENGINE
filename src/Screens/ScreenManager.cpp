#include "ScreenManager.h"


#include "Screen.h"

#include "SplashScreen.h"
#include "MainMenuScreen.h"
#include "GameScreen.h"
#include "Game3DScreen.h"


#include "GameTime.h"
#include "Window.h"


#include <memory>



extern Window gWindow;




ScreenManager::ScreenManager() = default;



ScreenManager::~ScreenManager() = default;





void ScreenManager::init()
{
    current.reset();


    activeType = ScreenType::Splash;


    splashTimer = 0.0f;
}






void ScreenManager::setScreen(ScreenType type)
{

    if (current)
    {
        current->onExit();

        current.reset();
    }



    activeType = type;



    switch(type)
    {


        case ScreenType::Splash:
        {
            current = std::make_unique<SplashScreen>();

            splashTimer = 0.0f;

            break;
        }



        case ScreenType::MainMenu:
        {
            current = std::make_unique<MainMenuScreen>();

            break;
        }



        case ScreenType::Game:
        {
            current = std::make_unique<GameScreen>();

            break;
        }



        case ScreenType::Game3D:
        {
            current = std::make_unique<Game3DScreen>();

            break;
        }


    }




    if(current)
    {
        current->onEnter();
    }

}







void ScreenManager::update(GameTime& time)
{

    if(!current)
        return;



    float dt = time.getDeltaTime();




    if(activeType == ScreenType::Splash)
    {

        splashTimer += dt;



        if(splashTimer >= splashDuration)
        {

            gWindow.setFullscreen(true);



            setScreen(ScreenType::MainMenu);


            return;

        }

    }




    current->update(dt);

}







void ScreenManager::render()
{

    if(current)
    {
        current->render();
    }

}








ScreenType ScreenManager::getActiveScreen() const
{
    return activeType;
}