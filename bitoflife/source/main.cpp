#include "MicroBit.h"


class GameOfLife 
{
public:
    void seed(MicroBit *uBit)
    {
        for(int x=1; x<ROWS; x++) {
            for(int y=1; y<COLUMNS; y++) {
                this->buffer0[x][y] = uBit->random(2);
            }
        }
        this->gen0 = &(this->buffer0);
        this->gen1 = &(this->buffer1);
    }

    void nextgen()
    {
        for(int x=1; x<ROWS; x++) {
            for(int y=1; y<COLUMNS; y++) {
                // Note: (*gen0)[x][y] <=> (*(this->gen0))[x][y]
                int count = (*gen0)[x-1][y-1] + (*gen0)[x-1][y] + (*gen0)[x-1][y+1] +
                            (*gen0)[x][y-1]                     + (*gen0)[x][y+1]   +
                            (*gen0)[x+1][y-1] + (*gen0)[x+1][y] + (*gen0)[x+1][y+1] ;
                if (count < 2 || count > 3) { (*(this->gen1))[x][y] = 0; }                      // Die
                if (count == 2)             { (*(this->gen1))[x][y] = (*(this->gen0))[x][y]; }  // Stay the same
                if (count == 3)             { (*(this->gen1))[x][y] = 1; }                      // Alive
            }
        }
        this->tmp  = this->gen0;
        this->gen0 = this->gen1;
        this->gen1 = this->tmp;
    }

    void display(MicroBit *uBit)
    {
        for(int x=1; x<ROWS; x++) {
            for(int y=1; y<COLUMNS; y++) {
                this->screen.setPixelValue(x, y, (*gen0)[x][y]);
            }
        }
        uBit->display.print(this->screen);
    }

private:
    static const int ROWS    = 5;
    static const int COLUMNS = 5;

    MicroBitImage screen = MicroBitImage(ROWS, COLUMNS);

    int buffer0[ROWS+2][COLUMNS+2];
    int buffer1[ROWS+2][COLUMNS+2];

    int (*gen0)[ROWS+2][COLUMNS+2];
    int (*gen1)[ROWS+2][COLUMNS+2];
    int (*tmp)[ROWS+2][COLUMNS+2];
};


MicroBit    uBit;
GameOfLife  game;

void onButtonA(MicroBitEvent e)
{
    game.seed(&uBit);
    game.display(&uBit);
}

void onButtonB(MicroBitEvent e)
{
    game.nextgen();
    game.display(&uBit);
}

int main()
{
    uBit.init();

    uBit.seedRandom();

    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonA);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonB);

    release_fiber();
}