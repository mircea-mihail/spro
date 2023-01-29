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


//things to do (in no particular order):

//add an "ongoing when calling -t" with the functionality of -c
//and also make it add up to the total

//-d --delete
//delete a line 

//-m --manual
//manual input

//-w --week
//total progress during last week

//install and uninstall script

//create the progress files in a separate folder