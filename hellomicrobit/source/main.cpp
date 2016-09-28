#include "MicroBit.h"

MicroBit uBit;

int main()
{
    uBit.init();

    uBit.display.scrollAsync("Hello micro:bit :)");

    release_fiber();
}