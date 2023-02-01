#include <fstream>
#include <iostream>
#include <chrono>

#include "printing.h"
#include "fileWriting.h"


void startTimer(std::string title){
    std::ifstream checkFile("timeData.txt");
    time_t check = 0;
    checkFile >> check;
    if(check != 0){
        std::cout << "the timer needs to stop before it can start again\n";
        usage();
        exit(EXIT_FAILURE);
    }    
    
    std::ofstream f ("timeData.txt");
    std::time_t now =  (std::chrono::system_clock::to_time_t( std::chrono::system_clock::now()));
    f << now;
    f << '\n' << title;
    printWarning();
    f.close();
}

void addEntry(time_t start, time_t stop, std::string title){
    time_t seconds = 0, minutes = 0, hours = 0;
    seconds = difftime(stop, start);

    normalizeTheTime(hours, minutes, seconds);

    std::string filename = generateFilename(stop);

    if(!existsFile(filename)){
        std::ofstream f(filename);
        f.close();
    }    
        
    std::ofstream g(filename, std::ofstream::out | std::ofstream::app);
    g << getHourAndMinute(start) << " - " << getHourAndMinute(stop);
    g << "\t" << hours << "h "<< minutes << "m " << seconds << "s";
    g << '\t' << title << std::endl;
    g.close();
}

void stopTimer(){
    std::ifstream f("timeData.txt");
    std::time_t stop = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::time_t start;
    std::string title;
    std::string auxs;

    f >> start;
    if(start == 0){
        std::cout << "the timer needs to start before it can stop.\n";
        usage();
        f.close();
        exit(EXIT_FAILURE);
    }
    
    while (true){
        if(!(f >> auxs)) break;
        title += auxs;
        title += " ";
    }

    addEntry(start, stop, title);

    f.close();

    std::ofstream g("timeData.txt"); 
    //for every entry added, the aux file needs to be updated with a 0, to avoid consecutive -e timing errors
    g << 0;
    g.close();
}