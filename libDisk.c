#include "libTinyFS.h"
#include "libDisk.h"
#include "safeutil.h"

int openDisk(char *filename, int nBytes){

    if(nBytes % )

    /* This function opens a regular UNIX file and designates the first nBytes
         of it as space for the emulated disk. 
         nBytes should be a number that is evenly divisible by the block size.
       If nBytes > 0 and there is already a file by the given filename, 
         that disk is resized to nBytes, and that file’s contents may be overwritten. 
       If nBytes is 0, an existing disk is opened, and should not be overwritten. 
       There is no requirement to maintain integrity of any content beyond nBytes. 
       Errors must be returned for any other failures, 
       as defined by your own error code system.  */

    safeOpen(filename)
    
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