#include <iostream>

#include "printing.h"
#include "generalUtility.h"

const time_t SECONDS_IN_A_DAY =  86400;

void usage(){
    std::cout << "Usage: spro [OPTION]...\n";
    std::cout << "Bash tool to track your progress while studying\n";
    std::cout << "\n";
    std::cout << "Options:\n";
    std::cout << "    -s, --start <TITLE>   starts the timer and sets the session title as TITLE\n";
    std::cout << "    -e, --end             stops the timer\n";
    std::cout << "    -t, --table <DAY>     prints the progress table for the day <DAY> is optional\n";
    std::cout << "                          if no <DAY> is given, the current day is implied\n";
    std::cout << "    -b, --balance <DAY>   prints the total progress of a given day (format: 11Jan2022)\n";
    std::cout << "                          if no <DAY> is given, the current day is implied\n";
    std::cout << "    -c, --current         prints the current progress (how long has it been since -s without using -e)\n";
    std::cout << "    -w, --week            does a -t on every file within the past 7 days\n";
    std::cout << "                          and displays a total amount of hours worked during that time\n";

}

void printWarning(){
    std::cout << "\nDON'T FORGET TO STOP THE TIMER!\n\n";
}

time_t addItUp(std::string filename, time_t extraSeconds){
    int nrows = numberOfRows(filename);
    std::ifstream f(filename);
    std::string buffer;
    char auxc;
    time_t hours, minutes, seconds;
    time_t totalHours = 0, totalMinutes = 0, totalSeconds = 0;
    
    for(int i = 0; i < nrows; i++){
        for(int i = 0; i < 14; i++){
            f >>std::noskipws>> auxc;
        }
        f >> hours; f >> auxc; f >> auxc;
        f >> minutes; f >> auxc; f >> auxc; 
        f >> seconds; f >> auxc; f >> auxc; 
        totalHours += hours; totalMinutes += minutes; totalSeconds += seconds;
        
        while(auxc != '\n'){
           f >>std::noskipws>> auxc;
        } 
    }

    totalSeconds += extraSeconds;

    normalizeTheTime(totalHours, totalMinutes, totalSeconds);
    std::cout << totalHours << "h " << totalMinutes << "m " << totalSeconds << "s\n";

    f.close();

    return totalHours * 3600 + totalMinutes * 60 + totalSeconds;
}

time_t showCurrentProgress(){
    std::ifstream f("timeData.txt");
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::time_t start;

    f >> start;
    if(start == 0){
        std::cout << "the timer needs to start in order to display the current progress\n";
        usage();
        f.close();
        return 0;
    }

    time_t seconds = 0, minutes = 0, hours = 0;
    seconds = difftime(now, start);
    time_t auxseconds = seconds;

    normalizeTheTime(hours, minutes, seconds);
    std::cout << hours << "h " << minutes << "m " << seconds << "s\n";

    f.close();
    return auxseconds;
}

void dealWith0h(char c, char &tabNl, int &twoSpaces, bool &hflag){
    if(twoSpaces != 0){
        if(twoSpaces == 2 && (c != '0')){
            std::cout << c;
            hflag = true;
        }
        else if(hflag == true){
            hflag = false;
            std::cout << 'h';
        }
        else{
            std::cout << ' ';
        }
        twoSpaces--;
    }
    else{
        std::cout << c;
    }
    if(tabNl == '\n' && c == '\t'){
        twoSpaces = 2;
    }
    if(c == '\n')
        tabNl = c;
    if(c == '\t')
        tabNl = c;
}

time_t printTable(std::string filename){
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char tabNl = '\n';
    int twoSpaces = 0; 
    bool hflag = false;
    time_t finalSeconds = 0;

    if(!existsFile(filename)){
        std::cout << "no data recorded for today\n";
        return -1;
    }
    else{
        char c; 
        std::ifstream f(filename);
        while(f>>std::noskipws>>c){
            dealWith0h(c, tabNl, twoSpaces, hflag);
        }
        f.close();
    }
    time_t extraSeconds = 0;
    if(!zeroAuxFile() && (filename == generateFilename(now))){
        std::cout << "ongoing:\t";
        extraSeconds = showCurrentProgress();
    }
    std::cout << "\ntotal: \t\t";
    finalSeconds = addItUp(filename, extraSeconds);
    
    return finalSeconds;
}

void lastWeek(){
    time_t today = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now());
    time_t finalSeconds = 0, finalHours = 0, finalMinutes = 0;
    for(int i = 0; i < 7; i++){
        if(existsFile(generateFilename(today))){
            //std::cout << std::endl << generateFilename(today) << ':' << std::endl;
            finalSeconds += printTable(generateFilename(today));
        }
        today -= SECONDS_IN_A_DAY;
    }
    normalizeTheTime(finalHours, finalMinutes, finalSeconds);
    std::cout << "\nabsolute total:\t" << finalHours << "h " << finalMinutes << "m " << finalSeconds << "s \n";
}