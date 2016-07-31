#include "board.h"
board::board(void)
{
    rect.setSize(Vector2f(400, 600));
    FloatRect boardRect = rect.getLocalBounds();

    left = 1024.0f/2.0f - boardRect.width/2.0f;
    top = 768.0f/2.0f - boardRect.height/2.0f;

    rect.setOrigin(boardRect.left + boardRect.width/2.0f,
                        boardRect.top + boardRect.height/2.0f);
    rect.setFillColor(Color(210,105,30));
    rect.setOutlineColor(Color::Black);
    rect.setOutlineThickness(2.0f);
    rect.setPosition(Vector2f(1024.0f/2.0f, 768.0f/2.0f));

    codeRect.setSize(Vector2f(300, 50));
    FloatRect cRect = codeRect.getLocalBounds();
    codeRect.setOrigin(cRect.left + cRect.width/2.0f, 0);
    codeRect.setFillColor(Color(0,190,255));
    codeRect.setOutlineColor(Color::Black);
    codeRect.setOutlineThickness(2.0f);
    codeRect.setPosition(1024.0f/2.0f, 100.0f);

    mmTitle.initText("Mastermind");
    mmTitle.setTextColor(Color(175,238,238));
    mmTitle.setTextPosition(428, 105);

    srand(time(NULL));

    reset();
}

void board::reset(void)
{
    rowSelect = 9;
    columnSelect = -1;
    pegDrop = 0;
    pegCount = 0;
    keyIndex = 0;
    winner = 0;
    int cX, cY;
    cY = top + 90;
    cX = left + 25;
    for(j = 0; j < 10; j++)
    {   
        for(i = 0; i < 4; i++)
        {
            circleArr[i][j].setRadius(20);
            circleArr[i][j].setPointCount(30);
            circleArr[i][j].setFillColor(Color::Black);
            circleArr[i][j].setOutlineColor(Color::Black);
            circleArr[i][j].setOutlineThickness(2.0f);
            circleArr[i][j].setPosition(cX, cY);
            cX += 35 + 2*circleArr[i][j].getRadius();
        }
        cX = left + 25;
        cY += 50;
    }

    int kX, kY;
    kY = top + 15;
    kX = left + 60;
    for(i = 0; i < 4; i++)
    {
        codeArr[i].setRadius(20);
        codeArr[i].setPointCount(30);
        switch(rand() % 6)
            {
                case 0:
                    codeArr[i].setFillColor(Color::Red);
                    break;
                case 1:
                    codeArr[i].setFillColor(Color::Green);
                    break;
                case 2:
                    codeArr[i].setFillColor(Color::Blue);
                    break;
                case 3:
                    codeArr[i].setFillColor(Color::Yellow);
                    break;
                case 4:
                    codeArr[i].setFillColor(Color::White);
                    break;
                case 5:
                    codeArr[i].setFillColor(Color(50, 0, 100));
                    break;
            }
        codeArr[i].setOutlineColor(Color::Black);
        codeArr[i].setOutlineThickness(2.0f);
        codeArr[i].setPosition(kX, kY);
        kX += 35 + 2*codeArr[i].getRadius();
    }
    
    kY = top + 95;
    kX = left + 335;
    for(j = 0; j < 10; j++)
    {
        for(i = 0; i < 4; i++)
        {
            keyArr[i][j].setRadius(6);
            keyArr[i][j].setPointCount(30);
            keyArr[i][j].setFillColor(Color::Black);
            keyArr[i][j].setOutlineColor(Color::Black);
            keyArr[i][j].setOutlineThickness(0.5f);

            if(i == 0)
                keyArr[i][j].setPosition(kX, kY);
            else if(i == 1)
                keyArr[i][j].setPosition(kX + 20, kY);
            else if(i == 2)
                keyArr[i][j].setPosition(kX, kY + 20);
            else if(i == 3)
                keyArr[i][j].setPosition(kX + 20, kY + 20);
        }
        kY += 50 + 2*keyArr[i][j].getRadius();
    }
    for(i = 0; i < 4; i++)
        pegPresent[i] = 0;
}

void board::draw(RenderWindow& Window)
{
    Window.draw(rect);
    for(j = 0; j < 10; j++)
    {   
        for(i = 0; i < 4; i++)
        {
            Window.draw(circleArr[i][j]);
            Window.draw(keyArr[i][j]);
        }
    }
    if(winner || rowSelect < 0)
        for(i = 0; i < 4; i++)
            Window.draw(codeArr[i]);
    else
    {
        Window.draw(codeRect);
        mmTitle.showText(Window);
    }
}

int board::mouseOver(RenderWindow& Window)
{
    FloatRect pegBounds;
    Vector2f pegPosition;
    Vector2i mousePos;
    mousePos = Mouse::getPosition(Window);
    for(i = 0; i < 4; i++)
    {
        pegBounds = circleArr[i][rowSelect].getLocalBounds();
        pegPosition = circleArr[i][rowSelect].getPosition();
        if(mousePos.x > pegPosition.x && mousePos.y > pegPosition.y
            && mousePos.x - pegBounds.width < pegPosition.x && mousePos.y - pegBounds.height < pegPosition.y)
        {
            if(!pegPresent[i])
                circleArr[i][rowSelect].setFillColor(Color(137,137,137));
            else
                circleArr[i][rowSelect].setOutlineThickness(4.0f);
            if(!pegDrop)
                return i;
            else
                pegDrop = 0;
        }
        else
        {
            if(!pegPresent[i])
                circleArr[i][rowSelect].setFillColor(Color::Black);
            else
                circleArr[i][rowSelect].setOutlineThickness(2.0f);
        }
    }
    return -1;
}

void board::placePeg(RenderWindow& Window, int pegSelect)
{
    int pegPosition = mouseOver(Window);
    if(pegPosition >= 0 && pegSelect)
    {
        pegDrop = 1;
    }
    if(!Mouse::isButtonPressed(Mouse::Left) && pegDrop && pegPosition >= 0)
    {
        switch(pegSelect)
        {
            case 1:
                circleArr[pegPosition][rowSelect].setFillColor(Color::Red);
                break;
            case 2:
                circleArr[pegPosition][rowSelect].setFillColor(Color::Green);
                break;
            case 3:
                circleArr[pegPosition][rowSelect].setFillColor(Color::Blue);
                break;
            case 4:
                circleArr[pegPosition][rowSelect].setFillColor(Color::Yellow);
                break;
            case 5:
                circleArr[pegPosition][rowSelect].setFillColor(Color::White);
                break;
            case 6:
                circleArr[pegPosition][rowSelect].setFillColor(Color(50, 0, 100));
                break;
        }
        if(!pegPresent[pegPosition])
            pegCount++;
        pegPresent[pegPosition] = 1;
        pegDrop = 0;
    }
}

int board::manageRow(void)
{
    int checkCodePeg[4];
    int checkKeyPeg[4];

    if(pegCount == 4)
    {
        for(i = 0; i < 4; i++)
        {
            checkCodePeg[i] = 0;
            checkKeyPeg[i] = 0;
        }
        for(i = 0; i < 4; i++)
        {
            if(circleArr[i][rowSelect].getFillColor() == codeArr[i].getFillColor())
            {
                keyArr[keyIndex][rowSelect].setFillColor(Color::Red);
                checkKeyPeg[i] = 1;
                checkCodePeg[i] = 1;
                keyIndex++;
            }
        }

        for(i = 0; i < 4; i++)
        {
            for(j = 0; j < 4; j++)
                if(!checkCodePeg[i] && !checkKeyPeg[j])
                    if(circleArr[i][rowSelect].getFillColor() == codeArr[j].getFillColor())
                    {
                        keyArr[keyIndex][rowSelect].setFillColor(Color::White);
                        keyIndex++;
                        checkCodePeg[i] = 1;
                        checkKeyPeg[j] = 1;
                    }
            pegPresent[i] = 0;
        }
        if(keyArr[0][rowSelect].getFillColor() == Color::Red &&
           keyArr[1][rowSelect].getFillColor() == Color::Red &&
           keyArr[2][rowSelect].getFillColor() == Color::Red &&
           keyArr[3][rowSelect].getFillColor() == Color::Red)
            winner = 1;
        keyIndex = 0;
        pegCount = 0;
        rowSelect--;
        if(rowSelect < 0 && !winner)
            return 1;
    }
    return winner;

}
