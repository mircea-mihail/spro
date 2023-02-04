#include <iostream>
#include <chrono>
#include <unistd.h>

#include "options.h"
#include "printing.h"
#include "generalUtility.h" 
#include "fileWriting.h"

void options(int argc, char* argv[]){
    int i;
    int sflag = 0, eflag = 0, tflag = 0, errflag = 0; 
    int bflag = 0, cflag = 0, wflag = 0, dflag = 0;
    //s expects an argument, e does not
    while((i = getopt(argc, argv, "s:etbcwd")) != -1){
        switch(i){
            case 's':
                sflag++;
                break;

            case 'e':
                eflag++;
                break;

            case 't':
                tflag++;
                break;

            case 'b':
                bflag++;
                break;

            case 'c':
                cflag++;
                break;

            case 'w':
                wflag++;
                break;

            case 'd':
                dflag++;
                break;

            default:
                errflag ++; 
        }
    }

    if(errflag != 0){
        usage();
        exit(EXIT_FAILURE);
    }

    if(sflag == 1){
        std::string title;
        if(argc == 2){
            usage();
            exit(EXIT_FAILURE);
        }
        for(int i = optind-1; i < argc; i++)
            title = title + argv[i] + ' ';
        startTimer(title);
    }

    if(eflag == 1){
        stopTimer();
    }

    if(tflag == 1){
        if(argc == 2){
            time_t now = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now());
            printTable(generateFilename(now));
        }
        else if(argc > 3){
            std::cout << "Only one date at a time!\n\n";
            usage();
            exit(EXIT_FAILURE);
        }
        else{
            std::string inputDate = argv[2];
            if(existsFile(inputDate)){
                printTable(inputDate);
            }
            else{
                std::cout << "No data for the given date (" << inputDate << ")\n";
            }
        }
    }

    if(bflag == 1){
        //use with no arguments:
        if(argc == 2){
            time_t today = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now());
            addItUp(getExistingFilename(today), 0);
        }
        else if(argc > 3){
            std::cout << "Only one date at a time!\n\n";
            usage();
            exit(EXIT_FAILURE);
        }
        else{
            std::string inputDate = argv[2];
            if(existsFile(inputDate)){
                addItUp(inputDate, 0);
            }
            else{
                std::cout << "No data for the given date (" << inputDate << ")\n";
            }
        }
    }

    if(cflag == 1){
        showCurrentProgress();
    }
    
    if(wflag == 1){
        lastWeek();
    }

    if(dflag == 1){
        if(argc <= 2){
            std::cout << "no line given to be deleted\n";
            usage();
        }
        else{
            int line;
            line = atoi(argv[2]);
            time_t today = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now());
            deleteLine(line, generateFilename(today));
        }

    }
}