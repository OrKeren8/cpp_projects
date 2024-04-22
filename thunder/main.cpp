#include <iostream>

#include "test.h"
#include "snakeGame.h"
#include "gameConfig.h"

using namespace std;

void testSnakeGame();

int main() 
{
    //cout << "Hello, World!" << endl;
    //cout << "testing" << endl;
    // testKbhitAndGetch();
    testSnakeGame();

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
    gotoxy(0, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 2);
    return 0;
}

void testSnakeGame()   
{
    SnakesGame theGame;

    theGame.init(5);
    theGame.run();
    theGame.freeMemory();
}