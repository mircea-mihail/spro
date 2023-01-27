#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string>
#include <fstream>
#include <chrono>
#include <ratio>

void usage(){
    std::cout << "Usage: spro [OPTION]...\n";
    std::cout << "Bash tool to track your progress while studying\n\n";

    std::cout << "Options:\n";
    std::cout << "    -s, --start <TITLE>    starts the timer and sets the session title as TITLE\n";
    std::cout << "    -e, --end              stops the timer\n";
    std::cout << "    -t, --table            prints the progress table for the day\n";
    std::cout << "    -b, --balance <DAY>    prints the total progress of a given day (format: 11Jan2022)\n";

}

void printWarning(){
    std::cout << "\nDON'T FORGET TO STOP THE TIMER!\n\n";
}

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

bool existsFile(std::string fileName){
    std::ifstream f(fileName);
    if(f.good()){
        f.close();
        return true;
    }
    f.close();
    return false;
    
}

std::string getDate(time_t start){
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
        filename += aux[pos];
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

std::string getHourAndMinute(time_t time){
    //format: Mon Oct 11 17:10:55 2021
    std::string hourAndMinute, aux = ctime(&time);
    std::size_t pos;
    int colonflag = 0;
    pos = aux.find_first_of(" ");
    pos = aux.find_first_of(" ", pos + 1);
    pos = aux.find_first_of(" ", pos + 1) + 1;
    //hours
    while(colonflag < 2){
        hourAndMinute += aux[pos];
        pos ++;
        if(aux[pos] == ':')
            colonflag ++;    
    }
    return hourAndMinute;
}

void normalizeTheTime(int &hours, int &minutes, int &seconds){
    int maux = 0;
    int haux = 0;
    if(seconds > 60){
        maux = seconds / 60;
        seconds -= maux * 60;
    }
    minutes += maux;
    if(minutes > 60){
        haux = minutes / 60;
        minutes -= haux * 60;
    }
    hours += haux;
}


void addEntry(time_t start, time_t stop, std::string title){
    int seconds = 0, minutes = 0, hours = 0;
    seconds = difftime(stop, start);

    normalizeTheTime(hours, minutes, seconds);

    std::string filename = getDate(start);

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

std::string getStringFromDate(time_t day){
    if(!existsFile(getDate(day))){
        std::cout << "no file for the given date";
        exit(EXIT_FAILURE);
    }
    return getDate(day);
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

//anime cool watamote
void addItUp(std::string filename){
    int nrows = numberOfRows(filename);

    std::ifstream f(filename);
    std::string buffer;
    char auxc;
    int hours, minutes, seconds;
    int totalHours = 0, totalMinutes = 0, totalSeconds = 0;
    
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
    
    normalizeTheTime(totalHours, totalMinutes, totalSeconds);
    std::cout << totalHours << "h " << totalMinutes << "m " << totalSeconds << "s\n";

    f.close();
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

void printTable(){
    time_t now = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now());
    if(!existsFile(getDate(now))){
        std::cout << "no data recorded for today\n\n";
    }
    else{
        char c;
        std::ifstream f(getDate(now));
        while(f>>std::noskipws>>c){
            std::cout << c;
        }
        f.close();
    }
    std::cout << std::endl << "total: ";
    addItUp(getStringFromDate(now));
}

void options(int argc, char* argv[]){
    int i;
    int sflag = 0, eflag = 0, tflag = 0, bflag = 0, errflag = 0;
    //s expects an argument, e does not
    while((i = getopt(argc, argv, "s:etb")) != -1){
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
        printTable();
    }

    if(bflag == 1){
        std::string title;
        //use with no arguments:
        if(argc == 2){
            time_t today = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now());
            addItUp(getStringFromDate(today));
        }
        else if(argc > 3){
            std::cout << "Only one date at a time!\n\n";
            usage();
            exit(EXIT_FAILURE);
        }
        else{
            std::string inputDate = argv[2];
            if(existsFile(inputDate)){
                addItUp(inputDate);
            }
            else{
                std::cout << "No data for the given date (" << inputDate << ")\n";
            }
        }
    }
}

int main(int argc, char* argv[]){
    if(argc <= 1){
        usage();
    }
    else{
        options(argc, argv);
    }
    return 0;
}

//-c --current progress
//add a current progress option (how long has it been since you started)
//but without losing the current progressm

//-d --delete
//delete a line 

//-m --manual
//manual input

//-w --week
//total progress during last week

//install and uninstall script