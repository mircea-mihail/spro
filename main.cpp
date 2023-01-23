#include <iostream>

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
    std::cout << "Usage: sprod [OPTION]...\n";
    std::cout << "Bash tool to track your progress while studying\n\n";

    std::cout << "Options:\n";
    std::cout << "    -s, --start <TITLE>    starts the timer setting the table title as\n";
    std::cout << "    -e, --end              stops the timer\n";
}


void startTimer(std::string title){
    std::ofstream f ("timeData.txt");
    std::time_t now =  (std::chrono::system_clock::to_time_t( std::chrono::system_clock::now()));
    f << now;
    f.close();
}

void stopTimer(){
    std::ifstream f("timeData.txt");
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::time_t before, seconds = 0, minutes = 0, hours = 0;

    f >> before;
    
    seconds = difftime(now, before);

    if(seconds > 60){
        minutes = seconds / 60;
        seconds -= minutes * 60;
    }
    if(minutes > 60){
        hours = minutes / 60;
        minutes -= hours * 60;
    }
    
    f.close();
}

void options(int argc, char* argv[]){
//start the timer
    if(strcmp(argv[1], "-s") == 0){
        std::cout << "-s\ntitle: ";
        std::string title;
        for(int j = 2; j < argc; j++){
            title += argv[j];
        }
        std::cout << title << std::endl; 

        startTimer(title);
    }
//stop the timer
    else if(strcmp(argv[1], "-e") == 0){
        std::cout << "-e\nthe timer stopped\n";

        stopTimer();
    }
//bad input
    else
        usage();

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