#ifndef SPRO_OPTIONS_H_
#define SPRO_OPTIONS_H_

#include <iostream>
#include <chrono>
#include <unistd.h>

#include "printing.h"
#include "generalUtility.h" 
#include "fileWriting.h"

//reads the input from the user and calls the appropriate function to honor the request
void options(int argc, char* argv[]);

#endif