#ifndef SPRO_GENERALUTILITY_H_
#define SPRO_GENERALUTILITY_H_

#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

#include <unistd.h>
#include <pwd.h>

extern const std::string HOME_PATH;
extern const std::string SPRO_PATH;

//system time is in seconds so this function makes the seconds and minutes less than 60
void normalizeTheTime(time_t &hours, time_t &minutes, time_t &seconds);

//returns the number of rows of a given filename
int numberOfRows(std::string filename);

//returns true if a file with the name filename exists
bool existsFile(std::string fileName);

//returns the hour and minute in this format 16:41
std::string getHourAndMinute(time_t time);

//generates the according filename to the time given to the function
std::string generateFilename(time_t start);

//checks if a file with the date we seek exists, and if it does it returns a string 
std::string getExistingFilename(time_t day);

//returns true if auxfile contains a 0
bool zeroAuxFile();

#endif