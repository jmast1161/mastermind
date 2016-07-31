#include "Game.h"

void Game::Start(void)
{
    HWND hWnd = GetConsoleWindow();
    ShowWindow( hWnd, SW_HIDE );

    int pegSelect = 0;
    int playMode = 0;

    VideoMode VMode(1024, 768, 32);
    RenderWindow Window(VMode, "Mastermind");
    Window.setFramerateLimit(60);

    Texture texture;
    texture.loadFromFile("Images/grayBackground.jpg");
    Sprite background(texture);

    RectangleShape dirRect;
    dirRect.setSize(Vector2f(800, 600));
    FloatRect dirBounds = dirRect.getLocalBounds();
    dirRect.setOrigin(dirBounds.left + dirBounds.width/2.0f,
                      dirBounds.top + dirBounds.height/2.0f);
    dirRect.setFillColor(Color(220,220,220));
    dirRect.setOutlineColor(Color::Black);
    dirRect.setOutlineThickness(2.0f);
    dirRect.setPosition(1024.0f/2.0f, 768.0f/2.0f);

    gameClickableText play, quit, options, directions, scores, back, done;
    gameBasicText directionsText[10];

    play.initText("Play");
    directions.initText("Directions");
    quit.initText("Quit");
    back.initText("Back");
    done.initText("Done");
    
    directionsText[0].initText("Mastermind consists of two players, a Code Maker");
    directionsText[1].initText("and Code Breaker.  The Code Maker creates a four");
    directionsText[2].initText("color code using any combination of six colors.");
    directionsText[3].initText("The Code Breaker must try to guess the combination");
    directionsText[4].initText("within ten tries.  After each guess, the Code Maker");
    directionsText[5].initText("will give hints to the Code Breaker.  These hints");
    directionsText[6].initText("will come in the form of red and white pegs.  Red");
    directionsText[7].initText("pegs mean that the Code Breaker has a correct color");
    directionsText[8].initText("in the correct spot.  White pegs means that the Code");
    directionsText[9].initText("Breaker has a correct color in the wrong spot.");

    play.setTextPosition(20, 300);
    directions.setTextPosition(20, 350);
    quit.setTextPosition(20, 400);
    back.setTextPosition(125, 635);
    done.setTextPosition(20, 250);

    int dY = 125;
    for(int i = 0; i < 10; i++)
    {
        directionsText[i].setTextPosition(150, dY);
        dY += 50;
    }
    board gameBoard;

    codePeg codeYellowSprite;
    codeYellowSprite.init(Window);
    codeYellowSprite.setPegPosition(800, 100);
    codeYellowSprite.setPegColor(Color::Yellow);

    codePeg codeBlueSprite;
    codeBlueSprite.init(Window);
    codeBlueSprite.setPegPosition(800, 200);
    codeBlueSprite.setPegColor(Color::Blue);

    codePeg codeRedSprite;
    codeRedSprite.init(Window);
    codeRedSprite.setPegPosition(800, 300);
    codeRedSprite.setPegColor(Color::Red);

    codePeg codeGreenSprite;
    codeGreenSprite.init(Window);
    codeGreenSprite.setPegPosition(800, 400);
    codeGreenSprite.setPegColor(Color::Green);

    codePeg codeWhiteSprite;
    codeWhiteSprite.init(Window);
    codeWhiteSprite.setPegPosition(800, 500);
    codeWhiteSprite.setPegColor(Color::White);

    codePeg codePurpleSprite;
    codePurpleSprite.init(Window);
    codePurpleSprite.setPegPosition(800, 600);
    codePurpleSprite.setPegColor(Color(50, 0, 100));

    Event event;
    while(Window.isOpen())
    {
        while(Window.pollEvent(event))
            switch(event.type)
            {
                case Event::Closed:
                    Window.close();
                    break;
                defualt:
                    break;
            }

        Window.draw(background);
        gameBoard.draw(Window);

        if(!playMode)
        {
            if(!Mouse::isButtonPressed(Mouse::Left))
            {
                play.mouseOver(Window);
                directions.mouseOver(Window);
                quit.mouseOver(Window);
            }
            else
            {
                if(play.handleClick(Window))
                    playMode = 1;
                else if(directions.handleClick(Window))
                    playMode = 2;
                else if(quit.handleClick(Window))
                    Window.close();
            }
            play.showText(Window);
            directions.showText(Window);
            quit.showText(Window);
        }
        else if(playMode == 1)
        {
            if(!gameBoard.manageRow())
            {
                gameBoard.mouseOver(Window);
                gameBoard.placePeg(Window, pegSelect);

                switch(pegSelect)
                {
                    case 0:
                        if(codeRedSprite.drag(Window))
                            pegSelect = 1;
                        if(codeGreenSprite.drag(Window))
                            pegSelect = 2;
                        if(codeBlueSprite.drag(Window))
                            pegSelect = 3;
                        if(codeYellowSprite.drag(Window))
                            pegSelect = 4;
                        if(codeWhiteSprite.drag(Window))
                            pegSelect = 5;
                        if(codePurpleSprite.drag(Window))
                            pegSelect = 6;
                        break;
                    case 1:
                        if(codeRedSprite.drag(Window))
                            pegSelect = 1;
                        else
                            pegSelect = 0;
                        break;
                    case 2:
                        if(codeGreenSprite.drag(Window))
                            pegSelect = 2;
                        else
                            pegSelect = 0;
                        break;
                    case 3:
                        if(codeBlueSprite.drag(Window))
                            pegSelect = 3;
                        else
                            pegSelect = 0;
                        break;
                    case 4:
                        if(codeYellowSprite.drag(Window))
                            pegSelect = 4;
                        else
                            pegSelect = 0;
                        break;
                    case 5:
                        if(codeWhiteSprite.drag(Window))
                            pegSelect = 5;
                        else
                            pegSelect = 0;
                        break;
                    case 6:
                        if(codePurpleSprite.drag(Window))
                            pegSelect = 6;
                        else
                            pegSelect = 0;
                        break;
                }
                
                if(!Mouse::isButtonPressed(Mouse::Left))
                    done.mouseOver(Window);
                else
                    if(done.handleClick(Window))
                    {
                        gameBoard.reset();
                        playMode = 0;
                    }
                done.showText(Window);

                codeRedSprite.draw(Window);
                codeGreenSprite.draw(Window);
                codeBlueSprite.draw(Window);
                codeYellowSprite.draw(Window);
                codeWhiteSprite.draw(Window);
                codePurpleSprite.draw(Window);
            }
            else
            {
                if(!Mouse::isButtonPressed(Mouse::Left))
                    done.mouseOver(Window);
                else
                    if(done.handleClick(Window))
                    {
                        gameBoard.reset();
                        playMode = 0;
                    }
                done.showText(Window);
            }
        }
        else if(playMode == 2)
        {
            Window.draw(dirRect);
            if(!Mouse::isButtonPressed(Mouse::Left))
                back.mouseOver(Window);
            else
                if(back.handleClick(Window))
                    playMode = 0;
            for(int i = 0; i < 10; i++)
                directionsText[i].showText(Window);
            back.showText(Window);
        }
        Window.display();
    }
}
