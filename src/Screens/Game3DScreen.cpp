#include "Game3DScreen.h"


void Game3DScreen::onEnter()
{
    renderer3D.initialize(
        "Shaders/basic_3d.vert",
        "Shaders/basic_3d.frag"
    );
}


void Game3DScreen::update(float dt)
{

}


void Game3DScreen::render()
{
    renderer3D.render(game);
}


void Game3DScreen::onExit()
{

}