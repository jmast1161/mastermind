#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
using namespace sf;
using namespace std;

#ifndef GAMETEXTLIBRARY_H_
#define GAMETEXTLIBRARY_H_

class gameBasicText
{
    protected:
        Font font;
        Text text;
        FloatRect bounds;
        string gameText;
        int xPosition;
        int yPosition;
        int textSize;
        Color textColor;
    public:
        void initText(string srcText);
        void setFontType(string newFont);
        void setGameText(string srcText);
        void setTextSize(int newSize);
        void setTextPosition(int x, int y);
        void setTextColor(Color newColor);
        void showText(RenderWindow& Window);
};

class gameClickableText: public gameBasicText
{
    protected:
        SoundBuffer buffer;
        Sound sound;
        int once;
    public:
        void mouseOver(RenderWindow& Window);
        int handleClick(RenderWindow& Window);
};

class gameToggleText: public gameClickableText
{
    protected:
        string altGameText;
        int choice;
    public:
        void initText(string srcText, string altText);
        void handleClick(RenderWindow& Window);
};

#endif
