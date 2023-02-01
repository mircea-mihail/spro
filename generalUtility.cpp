#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

#include "generalUtility.h"

void normalizeTheTime(time_t &hours, time_t &minutes, time_t &seconds){
    time_t maux = 0;
    time_t haux = 0;
    if(seconds >= 60){
        maux = seconds / 60;
        seconds -= maux * 60;
    }
    minutes += maux;
    if(minutes >= 60){
        haux = minutes / 60;
        minutes -= haux * 60;
    }
    hours += haux;
}

int numberOfRows(std::string filename){
    char auxc;
    int rows = 0;
    std::ifstream f(filename);
    while(f>>std::noskipws>>auxc){
        if(auxc == '\n'){
            rows ++;
        }
    }
    f.close();
    return rows;
}

bool existsFile(std::string fileName){
    std::ifstream f(fileName);
    if(f.good()){
        f.close();
        return true;
    }
    f.close();
    return false;
    
}

std::string getHourAndMinute(time_t time){
    //ctime format: Mon Oct 11 17:10:55 2021
    std::string hourAndMinute, aux = ctime(&time);
    std::size_t pos;
    int colonflag = 0;
    pos = 11;
    //hours
    while(colonflag < 2){
        hourAndMinute += aux[pos];
        pos ++;
        if(aux[pos] == ':')
            colonflag ++;    
    }
    return hourAndMinute;
}

std::string generateFilename(time_t start){
    std::string filename, month;
    std::size_t pos;
    std::string aux = ctime(&start);
        
    //month
    pos = aux.find_first_of(" ") + 1;
    do{
        month += aux[pos];
        pos ++;
    }while(aux[pos] != ' ');
    pos ++;

    //day
    do{
        if(aux[pos] != ' '){
            filename += aux[pos];
        }   
        pos ++;
    }while(aux[pos] != ' ');

    filename += month;

    //year
    pos = aux.find_first_of(" ", pos + 1) + 1;
    do{
        filename += aux[pos];
        pos ++;
    }while(pos < aux.size() - 1);
    
    return filename;
}

std::string getExistingFilename(time_t day){
    if(!existsFile(generateFilename(day))){
        std::cout << "no file for the given date\n";
        exit(EXIT_FAILURE);
    }
    return generateFilename(day);
} 

bool zeroAuxFile(){
    std::ifstream f("timeData.txt");
    std::time_t start;

    f >> start;
    f.close();

    if(start == 0)
        return true;
    return false;
}