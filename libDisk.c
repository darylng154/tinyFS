#include "libTinyFS.h"
#include "libDisk.h"
#include "safeutil.h"

int openDisk(char *filename, int nBytes){
    safeOpen();
    return 0; /* 0 on Success*/
}

// bNum = block index
int readBlock(int disk, int bNum, void *block){

    ssize_t count = read(disk, block, BLOCKSIZE_);
    if(count == -1)
    {

    }

    return 0; /* 0 on Success*/
}

int writeBlock(int disk, int bNum, void *block){

    return 0; /* 0 on Success*/
}

void closeDisk(int disk){


}