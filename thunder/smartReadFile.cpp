#include "smartReadFile.h"
#include "StateManager.h"
#include <string>


void smartReadFile::close() 
{
	if (file.is_open()) 
	{
		file.close();
	}
}

void smartReadFile::open(const std::string& fileName)
{
	std::string errorMassage = fileName;
	try {
		if (file.is_open()) 
		{
			errorMassage += " is open, shouldnt open opened file";
			throw std::exception(errorMassage.c_str());
		}
		file.open(fileName, std::ios::in);
		if (!file.is_open()) 
		{
			errorMassage += " cannot be opened, check the file please";
			throw std::exception(errorMassage.c_str());
		}
		else if (file.bad())
		{
			errorMassage += " is corrupted or damaged, check the file please";
			throw std::exception(errorMassage.c_str());
		}
	}
	catch (const exception& e) {
		StateManager::exceptionHandler(e);
	}
}

void smartReadFile::open(const char* fileName)
{
	open((std::string)(fileName));
}