/** \file read_guid.cpp
  * Main function.
  */

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <tsk/libtsk.h>
#include "guid.h"

void process_guid(FILE *pf);


int main(int argc, char *argv[])
{
    FILE * pfile;
    
    if(argc == 1){
        printf("Please enter file name: ");
        char filename[31];
        scanf("%30s", (char*)(&filename));
        pfile = fopen(filename, "r");
        printf("%s:\n", filename);
        if(pfile != NULL){
            process_guid(pfile);
            fclose(pfile);
        }
        else
            perror("File opening failed");
        printf("==============================================\n");
    }
    else if(argc > 1){
        int i;
        for(i = 1; i < argc; ++i){
            pfile = fopen(argv[i], "r");
            printf("%s:\n", argv[i]);
    
            if(pfile != NULL){
                process_guid(pfile);
                fclose(pfile);
            }
            else
                perror("File opening failed");
            printf("==============================================\n");
        }
    }

    /*TSK_IMG_INFO *img;
    
    char *name = "/dev/sda";
    printf("%s\n", name);

    img = tsk_img_open(1, &name, TSK_IMG_TYPE_DETECT, 0);
    
    TSK_VS_INFO *vs = tsk_vs_open(img, 0, TSK_VS_TYPE_DETECT);

    printf("Partition type is: %s\n", tsk_vs_type_toname(vs->vstype));
    */
    
    return 0;
}


/**
  * Read GUIDs from a file and print partition types.
  *
  * \param pfile Pointer to input file.
  *
  * \return None.
  */
void process_guid(FILE *pfile)
{
    int count = 0;
    int empty_entries = 0;
    int not_empty = 0;
    while(!feof(pfile)){
        GUID * g = (GUID*)malloc(sizeof(GUID));
        int err = read_guid_from_file(g, pfile);
        
        if(err == -1){
            printf("Extra bytes less than GUID length left in file.\n");
            break;
        }
        else if(err){
            break;
        }
                    
        char *s = (char*)malloc(LENGTH_OF_GUID_STRING + 1);
        if(guid_encode(s, g)){
            if(empty_entries){
                printf("------------------%d Unused Entries------------------\n", empty_entries);
            }
            printf("%03d. %s %s\n", count, s, get_guid_type(g));
            ++not_empty;
            empty_entries = 0;
        }
        else
            empty_entries++;

        ++count;
        
        free(s);
        free(g);
    }
    if(empty_entries){
        printf("------------------%d Unused Entries------------------\n", empty_entries);
    }
    printf("Total:%d  Not empty:%d\n", count, not_empty);
}
