#pragma once


struct gameState {
	virtual ~gameState() = default;
};

class UserInput//fix name maybe stepInput
{
	/**
	* Acstract Base class for the key inputs for the game
	*/

public:
	virtual char getAction(gameState *state) const = 0;
	virtual ~UserInput() = default;
};