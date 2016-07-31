#include "gameTextLibrary.h"

//================================================================================//
//  gameBasicText                                                                 //
//================================================================================//

void gameBasicText::initText(string srcText)
{
    //These are default settings
    gameText = srcText.c_str();
    xPosition = 0;
    yPosition = 0;
    textSize = 30;
    textColor = Color::Black;
    font.loadFromFile("Fonts/Zapf.ttf");
    text.setFont(font);
    text.setString(gameText);
    text.setCharacterSize(textSize);
    text.setPosition(xPosition, yPosition);
    text.setColor(textColor);
    bounds = text.getLocalBounds();
}

void gameBasicText::setFontType(string newFont)
{
    font.loadFromFile(newFont);
    text.setFont(font);
}

void gameBasicText::setGameText(string srcText)
{
    gameText = srcText.c_str();
    text.setString(gameText);
}

void gameBasicText::setTextSize(int newSize)
{
    textSize = newSize;
    text.setCharacterSize(textSize);
}
void gameBasicText::setTextPosition(int x, int y)
{
    xPosition = x;
    yPosition = y;
    text.setPosition(xPosition, yPosition);
}

void gameBasicText::setTextColor(Color newColor)
{
    textColor = newColor;
    text.setColor(textColor);
}

void gameBasicText::showText(RenderWindow& Window)
{
    Window.draw(text);
}

//================================================================================//
//  gameClickableText                                                             //
//================================================================================//

void gameClickableText::mouseOver(RenderWindow& Window)
{
    Vector2i mousePos = Mouse::getPosition(Window);
    buffer.loadFromFile("Sounds/button-3.wav");
    if(mousePos.x > xPosition && mousePos.y > yPosition
            && mousePos.x - bounds.width < xPosition && mousePos.y - bounds.height < yPosition)
    {
        text.setStyle(Text::Bold);
        if(once)
        {
            sound.setBuffer(buffer);
            sound.play();
            once = 0;
        }
    }
    else
    {
        text.setStyle(Text::Regular);
        once = 1;
    }
}

int gameClickableText::handleClick(RenderWindow& Window)
{
    if(Mouse::isButtonPressed(Mouse::Left))
    {
        Vector2i mousePos = Mouse::getPosition(Window);
        if(mousePos.x > xPosition && mousePos.y > yPosition
            && mousePos.x - bounds.width < xPosition && mousePos.y - bounds.height < yPosition)
            return 1;
        return 0;
    }
}

//================================================================================//
//  gameToggleText                                                                //
//================================================================================//

void gameToggleText::initText(string srcText, string altText)
{
    //These are default settings
    gameText = srcText.c_str();
    altGameText = altText.c_str();
    xPosition = 0;
    yPosition = 0;
    textSize = 30;
    choice = 0;
    textColor = Color::Black;
    font.loadFromFile("Fonts/LucidaBrightRegular.ttf");
    text.setFont(font);
    text.setString(gameText);
    text.setCharacterSize(textSize);
    text.setPosition(xPosition, yPosition);
    text.setColor(textColor);
    bounds = text.getLocalBounds();
}

void gameToggleText::handleClick(RenderWindow& Window)
{
    if(Mouse::isButtonPressed(Mouse::Left))
    {
        Vector2i mousePos = Mouse::getPosition(Window);
        if(mousePos.x > xPosition && mousePos.y > yPosition
            && mousePos.x - bounds.width < xPosition && mousePos.y - bounds.height < yPosition)
        {
            if(choice == 0)
            {
                text.setString(altGameText);
                choice = 1;
            }
            else if(choice == 1)
            {
                text.setString(gameText);
                choice = 0;
            }
            bounds = text.getLocalBounds();
            sf::sleep(sf::seconds(0.1));//this line slows down the toggle display
        }
    }
}
