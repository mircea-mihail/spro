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
}


void startTimer(std::string title){
    std::ofstream f ("timeData.txt");
    std::time_t now =  (std::chrono::system_clock::to_time_t( std::chrono::system_clock::now()));
    f << now;
    f << '\n' << title;
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

void addEntry(time_t start, time_t stop, std::string title){
    std::time_t seconds = 0, minutes = 0, hours = 0;
    seconds = difftime(stop, start);

    if(seconds > 60){
        minutes = seconds / 60;
        seconds -= minutes * 60;
    }
    if(minutes > 60){
        hours = minutes / 60;
        minutes -= hours * 60;
    }
    std::string filename = getDate(start);
    std::cout << filename << std::endl << filename.size()<< std::endl << filename[filename.size()] << std::endl;

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

void printTable(){
    
}

void options(int argc, char* argv[]){
    int i;
    int sflag = 0, eflag = 0, tflag = 0, errflag = 0;
    //s expects an argument, e does not
    while((i = getopt(argc, argv, "tes:")) != -1){
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