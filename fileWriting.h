#ifndef SPRO_FILEWRITING_H_
#define SPRO_FILEWRITING_H_

#include "fileWriting.cpp"

//starts the timer -> writes to an aux file the time in system time
void startTimer(std::string title);

//writes to the appropriate file the time spent studying from -s to -e
void addEntry(time_t start, time_t stop, std::string title);

//stops the timer and adds an entry, making the auxfile empty (writing 0 to it)
void stopTimer();

#endif