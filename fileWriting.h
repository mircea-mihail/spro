#ifndef SPRO_FILEWRITING_H_
#define SPRO_FILEWRITING_H_

#include <fstream>
#include <iostream>
#include <chrono>

#include "printing.h"

//starts the timer -> writes to an aux file the time in system time
void startTimer(std::string title);

//writes to the appropriate file the time spent studying from -s to -e
void addEntry(time_t start, time_t stop, std::string title);

//stops the timer and adds an entry, making the auxfile empty (writing 0 to it)
void stopTimer();

//copies to an aux file the contents of the willing to delete file without the unwanted line
std::string rewriteToAuxFile(int line, std::string filename);

//copies back the contents of the aux file to the main one 
void copyToMainFile(int line, std::string filename);

//deletes a chosen line from the file
void deleteLine(int line, std::string filename);


#endif