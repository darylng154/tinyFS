#include "libTinyFS.h"
#include "libDisk.h"
#include "safeutil.h"

int openDisk(char *filename, int nBytes){
    if(safeOpen(filename);

    return 0; /* 0 on Success*/
}

// bNum = block index
// seek to bNum in disk & read BLOCKSIZE_ bytes
int readBlock(int disk, int bNum, void *block){
    ssize_t count;
    int offset;

    offset = bNum*BLOCKSIZE_;
    lseek(fwrite, offset, SEEK_SET);
    count = read(disk, block, BLOCKSIZE_);
    if(count == -1)
        errorout("#ERROR: readBlock -1");
    else if(count == 0)
        errorout("#ERROR: readBlock EOF - not a valid block number");
    else if(count > 0)
    {
        
    }
    else
        errorout("#ERROR: readBlock failed all cases");
        

    return 0; /* 0 on Success*/
}

int writeBlock(int disk, int bNum, void *block){

    return 0; /* 0 on Success*/
}

void closeDisk(int disk){


}