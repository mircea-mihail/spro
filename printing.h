#ifndef SPRO_PRINTING_H_
#define SPRO_PRINTING_H_

#include "printing.cpp"

//prints the way you're supposed to use the application
void usage();

//prints a warning to remind you to stop the timer
void printWarning();

//anime cool watamote
//prints a total number of hours, minutes and seconds in a file
void addItUp(std::string filename, int extraSeconds);

//displays the unfinished progress form -s without ending it with -e
int showCurrentProgress();

//prints the filename contents
void printTable(std::string filename);

#endif