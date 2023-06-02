#include "libTinyFS.h"
#include "libDisk.h"
#include "safeutil.h"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


int openDisk(char *filename, int nBytes){
  char blockBuffer[10];
  int flags = 0;
  int modes = 0;
  if(nBytes % BLOCKSIZE_){
    sprintf(blockBuffer, "Number of Bytes is not divisible by BLOCKSIZE (%d)",BLOCKSIZE_);
    errorout(blockBuffer);
  }

  if(nBytes > 0 && access(filename, F_OK) != 0){ /* File does not exist*/
    flags = O_RDWR | O_CREAT;  // Open for read/write, create if it doesnt't exist
    modes = S_IRUSR | S_IWUSR;
    return safeOpen(filename, flags, modes);
  }
  else if(nBytes > 0){ /* File may or may not be created. Open/create for read/write*/
    flags = O_RDWR;  // Open for read/write, create if it doesnt't exist
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

    errorout("#ERROR: readBlock reached this and should not have");
    return -1;
}

int writeBlock(int disk, int bNum, void *block){
  ssize_t count;
  int offset;

  offset = bNum * BLOCKSIZE_;
  lseek(disk, offset, SEEK_SET);
  count = write(disk, block, BLOCKSIZE_);
  if(count > 0)
      return 0; /* 0 on Success*/
  else if(count == -1)
      errorout("#ERROR: writeBlock -1");
  else if(count == 0)
      errorout("#ERROR: writeBlock 0");
  else
      errorout("#ERROR: writeBlock failed all cases");

  errorout("#ERROR: writeBlock reached this and should not have");
  return -1;
}


/* closeDisk() takes a disk number ‘disk’ and makes the disk closed to further I/O; 
i.e. any subsequent reads or writes to a closed disk should return an error. 
Closing a disk should also close the underlying file, 
committing any writes being buffered by the real OS. */

/* Still need to figure out what he means by committing writes. Is there a global
   buffer we need to flush?*/
void closeDisk(int disk){

  errno = 0;
  close(disk);
  
  if(errno)
    errorout(closeDisk);

  return;
}