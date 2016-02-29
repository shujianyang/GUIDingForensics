/** \file
  * Header file of GUID.
  */

#ifndef GUID_H
#define GUID_H

#include <stdio.h>
#include <string>
#include <stdint.h>
#include <tsk/vs/tsk_gpt.h>


class GUID{
public:
    uint32_t data_1;
    uint16_t data_2;
    uint16_t data_3;
    uint8_t data_4[8];
public:
    GUID(gpt_entry &entry);

    static const int BYTES_OF_GUID = 16;
    static const int LENGTH_OF_GUID_STRING = 36;
};


/*Read GUID from file*/
int read_guid_from_file(GUID *g, FILE *pf);

/*Encode GUID as a string*/
int guid_encode(char *s, GUID *g);


/*Check if GUID matches a given value.*/
int guid_match(GUID *, uint32_t, uint16_t, uint16_t, uint64_t);


/*Get partition type based on GUID value.*/
char * get_guid_type(GUID *);

#endif
