#include "libTinyFS.h"
#include "libDisk.h"
#include "safeutil.h"
#include <fcntl.h>



int openDisk(char *filename, int nBytes){
  char blockBuffer[10];
  int flags = 0;
  int modes = 0;
  if(!(nBytes % BLOCKSIZE_)){
    sprintf(blockBuffer, "Number of Bytes is not divisible by BLOCKSIZE (%d)",BLOCKSIZE_);
    errorout(blockBuffer);
  }

  if(nBytes > 0){ /* File may or may not be created. Open/create for read/write*/
    flags = O_RDWR | O_CREAT;  // Open for read/write, create if it doesnt't exist
    modes = S_IRUSR | S_IWUSR;
    return safeOpen(filename, flags, modes);
  }
  else if(nBytes == 0){ /* Assumed file is open*/
    flags = O_RDONLY; // Open for Read only
    modes = 0;        // Don't need modes when not creating a file
    return safeOpen(filename, flags, modes);
  }
  else if(nBytes < 0)
    errorout("Number of bytes must be positive.\n");

  /* This function opens a regular UNIX file and designates the first nBytes
        of it as space for the emulated disk. 
      //  nBytes should be a number that is evenly divisible by the block size.
      If nBytes > 0 and there is already a file by the given filename, 
        that disk is resized to nBytes, and that file’s contents may be overwritten. 
      If nBytes is 0, an existing disk is opened, and should not be overwritten. 
      There is no requirement to maintain integrity of any content beyond nBytes. 
      Errors must be returned for any other failures, 
      as defined by your own error code system.  */

  
  return -1; /* Souldn't get here*/
}

// bNum = block index
// seek to bNum in disk & read BLOCKSIZE_ bytes
int readBlock(int disk, int bNum, void *block){
    ssize_t count;
    int offset;

    offset = bNum * BLOCKSIZE_;
    lseek(disk, offset, SEEK_SET);
    count = read(disk, block, BLOCKSIZE_);
    if(count > 0)
    {
        return 0; /* 0 on Success*/
    }
    else if(count == -1)
        errorout("#ERROR: readBlock -1");
    else if(count == 0)
        errorout("#ERROR: readBlock EOF - not a valid block number");
    else
        errorout("#ERROR: readBlock failed all cases");
}

int writeBlock(int disk, int bNum, void *block){

    return 0; /* 0 on Success*/
}

void closeDisk(int disk){


}