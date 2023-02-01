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

//BUG:
//ongoing is added to older files when doing -t

//things to do (in particular order):

//-d --delete
//delete a line 

//-m --manual
//manual input

//-w --week
//total progress during last week

//make -b take -c into account? are -b and -c even useful anymore?

//install and uninstall script

//create the progress files in a separate folder