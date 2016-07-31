#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class codePeg
{
    protected:
        FloatRect bounds;
        CircleShape circle;
        int xPos, yPos, xDiff, yDiff, once;
        int xBase, yBase;
        int pressed;
        Vector2i mousePos;
        Vector2f circlePos;
    public:
        void init(RenderWindow& Window);
        void draw(RenderWindow& Window);
        int drag(RenderWindow& Window);
        void setPegPosition(int x, int y);
        void setPegColor(Color pegColor);
        int mouseOver(RenderWindow& Window);
};
