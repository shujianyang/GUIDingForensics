/** \file
  * Header file of GUID.
  */

#ifndef GUID_H
#define GUID_H

#include <string>
#include <tsk/libtsk.h>
#include <tsk/vs/tsk_gpt.h>


class GUID{
private:
    uint32_t data_1;
    uint16_t data_2;
    uint16_t data_3;
    uint8_t data_4[8];
private:
    uint16_t read16Bit(TSK_ENDIAN_ENUM endian, uint8_t *arr);
    uint32_t read32Bit(TSK_ENDIAN_ENUM endian, uint8_t *arr);
public:
    GUID(TSK_ENDIAN_ENUM endian, uint8_t arr[]);
    GUID(TSK_ENDIAN_ENUM endian, gpt_entry &entry);

    bool isUnused();
    std::string encode();
    bool match(uint32_t, uint16_t, uint16_t, uint64_t);
    std::string getGuidType();

    static const int BYTES_OF_GUID = 16;
    static const int LENGTH_OF_GUID_STRING = 36;
};


#endif
