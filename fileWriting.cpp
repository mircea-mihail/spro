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

std::string rewriteToAuxFile(int line, std::string filename){
    char auxc;
    std::string areYouSure;
    int rows = 1;
    std::ofstream af("auxFile.txt");
    std::ifstream mf(filename);
    while(mf>>std::noskipws>>auxc){
        if(auxc == '\n'){
            rows ++;
        }
        if(rows != 1 || (rows == 1 && rows != line))
            af << auxc;
        
        if(rows == line){
            if(auxc != '\n'){
                areYouSure += auxc;
            }
            mf>>std::noskipws>>auxc;
            areYouSure += auxc;
            while(auxc != '\n'){
                mf>>std::noskipws>>auxc;
                areYouSure += auxc;
            }
            rows ++;
        }
    }
    mf.close();
    af.close();
    return areYouSure;
}

void copyToMainFile(int line, std::string filename){
    char auxc;
    std::ofstream mf(filename);
    std::ifstream af("auxFile.txt");
    while(af>>std::noskipws>>auxc){
        mf << auxc;
    }
    mf.close();
    af.close();
}

void deleteLine(int line, std::string filename){
    if(line > numberOfRows(filename)){
        std::cout << "the file only has " << numberOfRows(filename) << ((numberOfRows(filename) == 1)?" line\n" : " lines\n");
        exit(EXIT_FAILURE);
    }    
    if(line <= 0){
        std::cout << "no rows below 0 in this file\n";
    }

    std::string areYouSure = rewriteToAuxFile(line, filename); 
    
    std::cout << "are you sure you want to delete this line:\n" << "\033[1;31m" << areYouSure << "\033[0m";
    std::cout << "enter for yes, any other key for no\n";
    char yesno = 'n';
    std::cin >>std::noskipws>> yesno;
    if(yesno == '\n'){
        copyToMainFile(line, filename);
    }
}