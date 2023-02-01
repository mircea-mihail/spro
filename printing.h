#ifndef SPRO_PRINTING_H_
#define SPRO_PRINTING_H_

#include "printing.cpp"

//prints the way you're supposed to use the application
void usage();

//prints a warning to remind you to stop the timer
void printWarning();

//anime cool watamote
//prints a total number of hours, minutes and seconds in a file
time_t addItUp(std::string filename, time_t extraSeconds);

//displays the unfinished progress form -s without ending it with -e
time_t showCurrentProgress();

//prints the filename contents
time_t printTable(std::string filename);

//does the actual printing of the file from printtable without printing 0h (clutters the info)
void dealWith0h(char c, char &tabNl, int &twoSpaces, bool &hflag);

//prints the dates and the overall total progress from the past week
void lastWeek();

#endif