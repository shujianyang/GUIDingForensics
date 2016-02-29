/** \file read_guid.cpp
  * Main function.
  */

#include <iostream>
#include <fstream>
#include <string>
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

    cout << "Partition List:" << endl;

    const TSK_VS_PART_INFO * partition;
    for(TSK_PNUM_T i=0; i < vs->part_count; i++){
        partition = tsk_vs_part_get(vs, i);
        if(partition->flags == TSK_VS_PART_FLAG_ALLOC){

            char *byteArr = new char[GUID::BYTES_OF_GUID]; 
            tsk_vs_part_read(partition, 0, byteArr,
                    GUID::BYTES_OF_GUID);

            GUID g(vs->endian, (uint8_t*)byteArr);

            cout << (int)partition-> slot_num << " "
                << g.encode() << "  "
                << g. getGuidType() << endl;

            delete []byteArr;
        }
    }


    tsk_vs_close(vs);
    tsk_img_close(img);

    /*ifstream filein(img_name.c_str(), ifstream::binary);

    uint8_t ar[16];
    for(int i=0; i<16; i++){
        filein >> ar[i];
    }
    filein.close();

    GUID g(TSK_LIT_ENDIAN, ar);
    cout << g.encode() << endl;*/
    
    return 0;
}

