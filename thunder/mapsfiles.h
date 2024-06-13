#pragma once
#include <string>
#include "gameConfig.h"
#include <filesystem>
#include <vector>
#include <algorithm>
#include "smartReadFile.h"
using std::string;
using std::vector;

class Mapsfiles
{
	char legend[3][GameConfig::GAME_WIDTH + 1] = {
		"W T                                                       WWWW            W    W",
		"W                                                         WBBW           WSW   W",
		"W L                                                       WBBW           WSW   W"
	};
	vector<string> filesNames;
	size_t fileIndex = 0;
	string filesPath = "mapFiles";
	string currfileName;
	string fileSuffix = ".screen.txt";
	bool fileStatus = false;
	bool mapsLoaded = false;
	bool currlevelLoaded = false;
	smartReadFile fileMap;
	void checkFileStatus();
	void copyHeaderToMap(char map[][GameConfig::GAME_WIDTH + 1],size_t& line,size_t& col);
	bool checkMapAndUpdate(char map[][GameConfig::GAME_WIDTH + 1]);
	void GetUserFileChoice();
	
	
public:
	void loadMapLevels(size_t& levels);
	Mapsfiles& operator=(const Mapsfiles& other);
	bool getMap(char map[][GameConfig::GAME_WIDTH + 1],bool userChoice);
	bool getMapsLoadedstatus() const { return mapsLoaded; }
	bool getCurrLevelLoadedStatus() const { return currlevelLoaded; }
	void loadNextMap();

	
};

