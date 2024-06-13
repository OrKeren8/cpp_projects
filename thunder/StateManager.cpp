#include "StateManager.h"
#include "GameSleep.h"
#include "GamePrint.h"

#include <conio.h>
#include <iostream>
#include <string>

using std::endl;
using std::to_string;
using std::exception;



StateManager::StateManager(int argc, char* argv[]): stepsIO(game.getTimeLeft(), game.getLevel()){
	setMode(argc, argv);
}

void StateManager::setMode(int argc, char* argv[]) {
	string errorMessage = "Game Mode not avaliable: ";
	switch (argc) {
	case 1:
		game.setMode(GameMode::SIMPLE, &keyboardStepsInput, nullptr);
		break;
	case 2:
		if (!strcmp(argv[1],"-load")) {
			game.setMode(GameMode::LOAD_FROM_FILE, &stepsIO, nullptr);
		}
		else if (!strcmp(argv[1],"-save")) {
			game.setMode(GameMode::SAVE_TO_FILE, &keyboardStepsInput, &stepsIO);
		}
		else {
			errorMessage.append(argv[1]);
			exceptionHandler(exception(errorMessage.c_str()));
		}
		break;
	case 3:
		if (!strcmp(argv[1], "-load") and !strcmp(argv[2], "-silent")) {
			game.setMode(GameMode::SILENT_LOAD_FROM_FILE, &stepsIO, nullptr);
			GameSleep::silentMode = GamePrint::silentMode = true;
		}
		else if (!strcmp(argv[1], "-save") and !strcmp(argv[2], "-silent")) {
			game.setMode(GameMode::SAVE_TO_FILE, &keyboardStepsInput ,&stepsIO);
		}
		else {
			errorMessage.append(argv[1]);
			errorMessage.append(" ");
			errorMessage.append(argv[2]);
			exceptionHandler(exception(errorMessage.c_str()));
		}
		break;
	default:
		exceptionHandler(exception("Game Mode not avaliable"));
	}
}


void StateManager::exceptionHandler(const exception& e) {
	toExit = true;
	clrscr();
	GamePrint::print("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*- Game Paused *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*");
	GamePrint::print("Exception: " + (string)e.what());
	GamePrint::print("Exiting game ...");
	GameSleep::longSleep();
}


void StateManager::startGame()
{
	if (!toExit) {
		if(game.getMode() != GameMode::SILENT_LOAD_FROM_FILE and game.getMode() != GameMode::LOAD_FROM_FILE)
			mainMenu();
		if (!toExit)
		{
			try {
				game.prepareToStart();
				while (game.getState()!=GameState::RESULT_DIFF and game.getState()!=GameState::WIN and game.getState()!= GameState::LOSE and !toExit) {
					game.gameLoop();
					if (game.getState() == GameState::PAUSE) {
						if (game.getMode() != GameMode::SILENT_LOAD_FROM_FILE)
							pauseMenu();
						if (!toExit)
							game.setStateToRunning();
					}
					if (game.getState() == GameState::RESULT_DIFF) {
						throw std::exception("Results unmatch");
					}
				}
			}
			catch (const exception& e) {
				exceptionHandler(e);
			}
		}
	}
}


void StateManager::mainMenu()
{
	unsigned short userChoice;
	GamePrint::print("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Thunderbirds: Escape from the Egyptian Tomb *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
	do {
		GamePrint::print("Please enter your choice");
		GamePrint::print("1: Start a new game");
		GamePrint::print("2: Set color ON/OFF (the default value is on)");
		GamePrint::print("3: load a specific map");
		GamePrint::print("8: Instructions and keys");
		GamePrint::print("9: Exit");
		cin >> userChoice;
		switch (userChoice)
		{
		case 1:
			GamePrint::print("Great, setting up the game, have fun!! :D");
			break;
		case 2:
			colorSet = !colorSet;
			colorSet ? GamePrint::print("color is now set on") : GamePrint::print("color is now set off");
			GamePrint::print("");
			break;
		case 3:
			GamePrint::print("No problem, when you will start a new game, you will choose the map :)");
			mapChoose = true;
			break;
		case 8:
			GamePrint::print("\nObjective :\nEscape the ancient Egyptian tomb by maneuvering the two trapped ships, a big ship(2x2) and a small ship(2x1), through obstacles and reaching the exit before time runs out\n");
			GamePrint::print("Controls:\nUse WASD to move the active ship");
			GamePrint::print("W - Up\nA - Left\nX - Down\nD - Right");
			GamePrint::print("Press 'B' or 'S' to switch control between the big and small ships\nPress 'ESC' to pause the game.");
			break;
		case 9:
			clrscr();
			GamePrint::print("Exiting the game, please come back when you can :D");
			GameSleep::shortSleep();
			toExit = true;
			break;
		default:
			GamePrint::print("invalid choice, please try again");
			break;
		}
	} while (userChoice != 1 && !toExit);
	GameSleep::shortSleep();
	clrscr();
}


void StateManager::pauseMenu() {

	bool illigalChoice = true;
	char userInput;

	GamePrint::print("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*- Game Paused *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*");
	GamePrint::print("Press ESC again to continue or 9 to Exit");
	while (illigalChoice) {
		while (!_kbhit())
			GameSleep::systemOprSleep();
		userInput = _getch();
		switch (userInput)
		{
		case (int)GameConfig::eKeys::ESC:
			clrscr();
			GamePrint::print("Returning to the game, get ready");
			GameSleep::shortSleep();
			clrscr();
			game.printScreen();
			illigalChoice = false;
			break;
		case (int)GameConfig::eKeys::EXIT:
			clrscr();
			game.printCredits();
			toExit = true;
			illigalChoice = false;
			break;
		}
	}
}

