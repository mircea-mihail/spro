#include <iostream>

#include <unistd.h>

#include <cstring>
#include <string>

#include <fstream>

#include <chrono>
#include <ratio>


void printArgs(int argc, char* argv[]){
    std::cout << "input args \n";
    for(int i = 1; i < argc; i++){
        std::cout << argv[i] << ' ';   
    }
    std::cout << std::endl;
}

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

//for every entry added, the aux file needs to be updated with a 0, to avoid consecutive -e timing errors
void addEntry(time_t start, time_t stop){
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
    
    //std::cout << hours << " h " << minutes << " min " << seconds << " sec \n";  

}

void stopTimer(){
    std::ifstream f("timeData.txt");
    std::time_t stop = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::time_t start;

    f >> start;
    if(start == 0){
        std::cout << "the timer needs to start before it can stop.\n";
        usage();
        f.close();
        exit(EXIT_FAILURE);
    }
    addEntry(start, stop);

    f.close();

    std::ofstream g("timeData.txt");
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