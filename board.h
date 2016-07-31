#include <SFML/Graphics.hpp>
#include "gameTextLibrary.h"
#include <time.h>
using namespace std;
using namespace sf;

class board
{
    protected:
        gameBasicText mmTitle;
        RectangleShape rect;
        RectangleShape codeRect;
        int top, left;
        int i, j;
        int rowSelect, columnSelect;
        CircleShape circleArr[4][10];
        CircleShape codeArr[4];
        CircleShape keyArr[4][10];
        int pegPresent[4];
        int pegDrop, pegCount, keyIndex, winner;
        int dummy[60];
    public:
        board(void);
        void draw(RenderWindow& Window);
        int mouseOver(RenderWindow& Window);
        void placePeg(RenderWindow& Window, int pegSelect);
        int manageRow(void);
        void reset(void);
};
