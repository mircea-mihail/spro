#include "options.h"

int main(int argc, char* argv[]){
    if(argc <= 1){
        usage();
    }
    else{
        options(argc, argv);
    }
    return 0;
}
//things to do (in particular order):

//make it so that when working from 23:30 to 12:20
//it adds 30 minutes to the first day and
//from 23:30 to 00:00
//it also creates a new file where it adds 20 minutes 
//from 12:00 to 00:20

//make -b take -c into account? are -b and -c even useful anymore?

//install and uninstall script

//create the progress files in a separate folder