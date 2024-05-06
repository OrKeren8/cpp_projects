#pragma once

#include "point.h"
#include "ship.h"
#include "block.h"
#include "gameConfig.h"
#include "time.h"
#include "health.h"
#include "utils.h"

#include <iostream>
#include <cstring>
#include <vector>


class Board {
	constexpr static size_t WIDTH = 80;
	constexpr static size_t HEIGHT = 25;
	size_t num_blocks = 0;
	// the original board that will be copied to the actual board
	char original_board[HEIGHT][WIDTH + 1] = {
		//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
			"W T                                                       WWWW            W    W", // 1
			"W                                                         WBBW           WSW   W", // 2
			"W L                                                       WBBW           WSW   W", // 3
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 4
			"W         @@                                                                   W", // 5
			"W         ##                                                                   W", // 6
			"W         ##                                                                   W", // 7
			"W                                                                              W", // 8
			"W                                                                              W", // 9
			"W                              11                                              W", // 10
			"W          22222               1111                 333                        W", // 11
			"W                                                   333                        W", // 12
			"W                                                 WWWWWWWWWWWW                 W", // 13
			"W                                                                              W", // 14
			"W                                                 W         WWWW               W", // 15
			"W                                             WWWWW            W               W", // 16
			"W                                              00              W               W", // 17
			"W                                       W      00            X W               W", // 18
			"W                                       WWWWWWWWWWWWWWWWWWWWWWWW               W", // 19
			"W                                                                              W", // 20
			"W                                       5                                      W", // 21
			"             44                        55                                       ", // 22
			"                                                                                ", // 23
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"  // 24
	};
	Time time;
	Health health;
	Point life_pos;
	Point exit_pos;	
	Ship ships[GameConfig::NUM_SHIPS];
	Block blocks[GameConfig::MAX_NUM_BLOCKS];
	bool colorSet = false;

public:
	char board[HEIGHT][WIDTH + 1];  // the actual board that will be modified
	
	void init(bool colorSet);
	void printScreen();
	void updateGamePieces();
	bool checkMove(LocationInfo& objectLoction);
	Ship* getShips() {return ships;}
	Block* getBlocks() { return blocks; }
	Time& getTime() { return time; }
	Health& getHealth() { return health; }
	void addObstacle(vector <Block*>& obs, char currSymbol, Coord coord);
	void shipFinishLine(char shipID);

};