#pragma once
#include "UserInput.h"
#include "smartReadFile.h"
#include <fstream>



struct levelState : public gameState {
	int timeStamp;
	int level;

	levelState() : gameState(), timeStamp(0), level(0) {};
	levelState(int timeStamp, int level) : gameState(), timeStamp(timeStamp), level(level) {};
};

class FileActionInput : public UserInput
{	
	smartReadFile fileMap;
	
	//void loadFile() const;
	//void closeFile();

public:
	virtual char getAction(gameState* state) const override {
		levelState* ls = dynamic_cast<levelState*>(state);//move to the constructor
		return '1';
 	}
	//~FileActionInput();
};

