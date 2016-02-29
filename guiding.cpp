/** \file read_guid.cpp
  * Main function.
  */

#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <tsk/libtsk.h>
#include "guid.h"

using namespace std;

int main(int argc, char *argv[])
{
    //int option = getopt(argc, argv, "o");

    if(argc < 2) {
        cerr << "Please provide the image name" << endl;
        exit(1);
    }

    string img_name(argv[1]);
    

    TSK_IMG_INFO *img = tsk_img_open(1, &argv[1], TSK_IMG_TYPE_DETECT, 0);
    if(img == NULL){
        tsk_error_print(stderr);
        cerr << "Cannot open image " << img_name << "." << endl;
        exit(1);
    }
    
    TSK_VS_INFO *vs = tsk_vs_open(img, 0, TSK_VS_TYPE_DETECT);
    if( vs == NULL){
        tsk_error_print(stderr);
        exit(1);
    }

    cout << "Partition type is: " << tsk_vs_type_toname(vs->vstype) << endl;

    if(vs->vstype != TSK_VS_TYPE_GPT){
        cerr << "The partition type of the image is not GPT." << endl;
        exit(1);
    }

    cout << "Is GPT" << endl;

    tsk_vs_close(vs);
    tsk_img_close(img);
    
    return 0;
}

