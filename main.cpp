#include "graphics.h"
#include "browser.h"
#include "config.h"
#include <iostream>


/*
*    There is a low propability that the following error below will occur:
*    Exception thrown at 0x0000000000000000 in ergasia2022.exe:
*    0xC0000005: Access violation executing location
*
*    If that happens, simply rerun the exe or build again if in VS code
*/

void update(float ms)
{
    Browser* browser = reinterpret_cast<Browser*>(graphics::getUserData());
    browser->update();
    graphics::MouseState mouse;
    graphics::getMouseState(mouse);
    if (mouse.button_left_released)
    {
        graphics::playSound("assets\\door2.wav", 1.0f, false);
    }

}


void draw()
{
    Browser* browser = reinterpret_cast<Browser*>(graphics::getUserData());
    browser->draw();
}

int main()
{
    Browser mybrowser;

    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Movieflix");

    graphics::setUserData(&mybrowser);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    //graphics::setFont(std::string(ASSET_PATH) + "SF-Pro-Display-Regular.otf");
    graphics::setFont(std::string(ASSET_PATH) + "SF-Pro-Text-Light.otf");


    mybrowser.init();
    graphics::startMessageLoop();

    return 0;
}