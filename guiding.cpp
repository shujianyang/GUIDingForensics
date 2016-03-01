/** \file read_guid.cpp
  * Main function.
  */

#include <iostream>
#include <fstream>
#include <iomanip>
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

    cout << "Partition type is: " << tsk_vs_type_toname(vs->vstype) << '\n' << endl;

    if(vs->vstype != TSK_VS_TYPE_GPT){
        cerr << "The partition type of the image is not GPT." << endl;
        exit(1);
    }


    char diskArr[GUID::BYTES_OF_GUID];
    tsk_img_read(img, 0x238, diskArr, GUID::BYTES_OF_GUID);
    GUID diskGUID(vs->endian, (uint8_t*)diskArr);

    cout << "[Disk GUID] " << diskGUID.encode() << '\n' << endl;

    cout << "Partition List:" << endl;

    const TSK_VS_PART_INFO * partition = tsk_vs_part_get(vs, 3);

    int emptyEntries = 0;

    for(TSK_OFF_T count = 0; count < 128; ++count){
        char byteArr[GUID::BYTES_OF_GUID]; 
        tsk_vs_part_read(partition, count * 128, byteArr, GUID::BYTES_OF_GUID);

        GUID typeGUID(vs->endian, (uint8_t*)byteArr); 

        if(!typeGUID.isUnused()){
            cout << setw(3) << count;
            if(emptyEntries > 0){
                cout << string(16, '-') << emptyEntries
                    << " Unused Entries" << string(10, '-') << endl;
                emptyEntries = 0;
            }
            cout << setw(19) << "[Type GUID]" << " "
                << typeGUID.encode() << "  "
                << typeGUID. getGuidType() << endl;

            tsk_vs_part_read(partition, count * 128 + 16, byteArr, GUID::BYTES_OF_GUID);
            GUID partGUID(vs->endian, (uint8_t*)byteArr);
            cout << setw(22) << "[Partition GUID]" << " "
                << partGUID.encode() << "\n" <<  endl;
        }
        else
            emptyEntries++;
    }
    if(emptyEntries > 0)
        cout << string(16, '-') << emptyEntries
            << " Unused Entries" << string(10, '-') << endl;



    tsk_vs_close(vs);
    tsk_img_close(img);

    
    return 0;
}

