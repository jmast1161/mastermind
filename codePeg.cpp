#include "codePeg.h"

int codePeg::drag(RenderWindow& Window)
{
    mousePos = Mouse::getPosition(Window);
    circlePos = circle.getPosition();

    if(Mouse::isButtonPressed(Mouse::Left))
    {
        if(pressed || mouseOver(Window))
        {
            if(once)
            {
                xDiff = mousePos.x - circlePos.x;
                yDiff = mousePos.y - circlePos.y;
                once = 0;
                pressed = 1;
            }
            xPos = mousePos.x - xDiff;
            yPos = mousePos.y - yDiff;
            circle.setPosition(xPos, yPos);
        }
    }
    else
    {
        mouseOver(Window);
        once = 1;
        xPos = xBase;
        yPos = yBase;
        xDiff = 0;
        yDiff = 0;
        circle.setPosition(xBase, yBase);
        pressed = 0;
    }
    return pressed;
}

int codePeg::mouseOver(RenderWindow& Window)
{
    mousePos = Mouse::getPosition(Window);
    if(mousePos.x > xPos && mousePos.y > yPos
        && mousePos.x - bounds.width < xPos && mousePos.y - bounds.height < yPos)
    {
        circle.setOutlineThickness(4.0f);
        return 1;
    }
    else
    {
        circle.setOutlineThickness(2.0f);
        return 0;
    }
}

void codePeg::init(RenderWindow& Window)
{
    xPos = 0;
    yPos = 0;
    xBase = 0;
    yBase = 0;
    once = 1;
    xDiff = 0;
    yDiff = 0;
    circle.setRadius(20);
    circle.setPointCount(30);
    circle.setFillColor(Color::Black);
    circle.setOutlineColor(Color::Black);
    circle.setOutlineThickness(2.0f);
    circle.setPosition(xPos, yPos);
    bounds = circle.getLocalBounds();
}

void codePeg::setPegPosition(int x, int y)
{
    xPos = x;
    yPos = y;
    xBase = x;
    yBase = y;
    circle.setPosition(xPos, yPos);
}

void codePeg::setPegColor(Color pegColor)
{
    circle.setFillColor(pegColor);
}

void codePeg::draw(RenderWindow& Window)
{
    Window.draw(circle);
}
